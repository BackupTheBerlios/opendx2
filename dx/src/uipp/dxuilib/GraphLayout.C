/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#define ONLY_IN_GRAPH_LAYOUT_CODE 1
#include "GraphLayout.h"
#include "EditorWindow.h"
#include "List.h"
#include "ListIterator.h"
#include "Network.h"
#include "EditorWorkSpace.h"
#include "Node.h"
#include "StandIn.h"
#include "Ark.h"
#include "ArkStandIn.h"
#include "ErrorDialogManager.h"
#include "Decorator.h"
#include "DecoratorStyle.h"
#include "Dictionary.h"

//
// How it works:
//    Basically, I just start at the bottom and walk up the graph, laying
//    out everything the way you lay out a tree.  I try to keep it balanced,
//    in other words, no tilting subtrees.  All trees should be more or
//    less even.  If the subtree is going to be too crowded, then I try to
//    move the root of a subtree over (left or right) more.
//
// 1) For each node, record the hops required to reach the node
//    from the top of the graph.  Optionally push nodes up or
//    down as aesthetics require.
// 3) Sort the list in descending order of hop counts.
//    Internal nodes are placed according to the order in which
//    they're wired to inputs. Caveat: when placing nodes we're going
//    to give preference to nodes that are 1 hop away. (Of course
//    everything is 1 hop away, but some things that are 1 hop
//    away are also 2 or more hops away.)
// 4) For the first node in the list, walk up the graph placing nodes
//    marking every node as it's placed.
// 5) For each subsequent unmarked node in the list, walk up the graph
//    until hitting a marked node, then begin walking back down the
//    graph placing nodes.  If no marked node is hit, then just walk
//    up the graph placing nodes outside the bounding box of nodes placed
//    in step (4).
// 6) post processing?
// 7) To apply placments, compute the bounding box of the nodes'
//    placments, then translate so that all nodes have positive x,y.
// 8) Rebuild all the arcs by fetching the workspace data structure,
//    destroying it and creating a new one.  The workspace lines can
//    be created and destroyed but never modified.
//
// Extras:
// 1) Before beginning, gather up all vpe annotations.  Place each
// one outside the bounding box of standins.  The user will have to
// rearrange them manually.
// 2) Get/Set nodes are special cased to ensure that they're lined
// up on their 'Link' parameter.
//
// What I wish I could do but can't:
//     I like the way computer chess programs work... They choose a move
//     by making one and then evaluating the board.  Evaluating the board
//     is defined as simulating the opponent's move and then evaluating
//     the board.  So it's recursive and the result gets better and better
//     as the user is willing to wait for the computer to examine more and
//     more outcomes.  I would like to do the same thing:  Move a node and evaluate
//     the layout.  etc.  Problem is, I have no way of evaluating a layout.
//     The proper measure is the amount of edge crossing and the amount
//     of bends in the edges, but I don't know
//     of any way of measuring this in a reasonable way.  I would have to
//     make an arrangement, then let the Workspace widget reroute and redraw,
//     since it's a widget and only does its work as part of updating the 
//     screen.  Unfortunately, there isn't any encapsulation of the line
//     routing algorithm that would allow me to submit a collection of node
//     placments and get a routing solution in return.  If I could, then I
//     could iterate over that result and add up all the line crossings.
//     ...and then recursively, I could examine more solutions.  The work
//     I've done so far works fairly well and keeps track of placments that
//     weren't what was really desired, so this exta programming - the
//     part that works like a chess program - wouldn't have to solve the
//     entire problem, it would have only to deal with the nodes that weren't
//     placed as desired.  I think users would be very willing to wait for
//     an additional 5 seconds for a really nice solution.
//

//
// How far should successive 'levels' of the graph be separated
// Should be a little more than 2x StandIn height so that we can
// achieve a sawtooth pattern when placing a row of Input nodes.
//
int GraphLayout::HeightPerLevel;
int GraphLayout::StandInHeight = -1;
// no way to know what this ought to be
// I got the value 42 just from observing the size of an Input tool
// with ordinary DX fonts
int GraphLayout::NarrowStandIn = 42; 

//
// No good basis for this value.  We use this when checking on a row
// of recievers to figure out if we should decrement a hop count.
// We consider only nodes whose standIn are as wide or wider than this.
//
int GraphLayout::WideStandIn = 65;

//
// When we want to scoot a node over to leave room for other nodes,
// how far should it go?
//
#define WIDTH 140


//
// When attempting to position nodes, we always check for collisions.
// If we find a collision we just start sliding it up/down/left/right
// until finding a free spot.  We also offset the y a little bit
// just to make it stick out.
//
// Currently unused
#define COLLISION_OFFSET 15

//
// Leave a little extra horizontal room between standins because
// crowded levels must still allow lines to pass.
// We'll allow REQUIRED_ if that will let us make straight arcs
// but if we can't make straight arcs, then we'll offset by 
// DESIRED_
//
//#define REQUIRED_FUDGE 6 
//#define DESIRED_FUDGE 20
// The commented out values work better for my personal copy of ~/DX
#define REQUIRED_FUDGE 5
#define DESIRED_FUDGE 10

//
// During node placment we check to see if were putting a node on
// top of another.  If so, we tweak the coords and retry.  After
// TOO_MANY_COLLISIONS we bail out.
//
#define TOO_MANY_COLLISIONS 500

//
// Starting coords for graph placement.  They have no meaning.  They
// just shouldn't get negative or greater than 64K since they might
// get stored into an unsigned short
//
#define INITIAL_X 5000 
#define INITIAL_Y 5000

//
// Comparator function used with qsort
//
int LayoutInfo::Comparator (const void* a, const void* b)
{
    Node** aptr = (Node**)a;
    Node** bptr = (Node**)b;
    Node* anode = (Node*)*aptr;
    Node* bnode = (Node*)*bptr;
    LayoutInfo* ainfo = (LayoutInfo*)anode->getLayoutInformation();
    LayoutInfo* binfo = (LayoutInfo*)bnode->getLayoutInformation();

    // descending order of hop count
    if (ainfo->hops > binfo->hops) return -1;
    if (ainfo->hops < binfo->hops) return 1;

    return 0;
}

void LayoutInfo::initialize(Node* n, int hops)
{
    n->setLayoutInformation(this);
    this->hops = hops;

    StandIn* si = n->getStandIn();
    ASSERT(si);

    si->getXYPosition(&this->x, &this->y);
    si->getXYSize(&this->w, &this->h);
}

boolean GraphLayout::entireGraph(WorkSpace* workSpace, const List& nodes, const List& decorators)
{
    List nodeList;

    ListIterator li;
    boolean retval = TRUE;
    Node* n;
    this->collisions = 0;

    // exclude the nodes that aren't in the current page
    li.setList((List&)nodes);
    while (n = (Node*)li.getNext()) {
	StandIn* si = n->getStandIn();
	if (!si) continue;
	if (si->getWorkSpace() != workSpace) continue;

	if (GraphLayout::StandInHeight == -1) {
	    int w,h;
	    si->getXYSize(&w,&h);
	    GraphLayout::StandInHeight = h;

	    // make heightperlevel be a power of 2 so that we can
	    // use bit masking to snap standins to a grid easily
	    GraphLayout::HeightPerLevel = h + h + 12;
	}
	nodeList.appendElement(n);
    }

    //
    // Must store the nodes to reflow in an array because later
    // we're going to use qsort.
    //
    Node** reflow;
    int reflow_count=0;
    int reflow_size=nodeList.getSize();
    reflow = (Node**)malloc(sizeof(Node*) * reflow_size);
    li.setList(nodeList);
    while (n = (Node*)li.getNext()) {
	reflow[reflow_count++] = n;
	n->clearMarked();
    }
    ASSERT (reflow_count == reflow_size);

    this->computeSawToothPermission(reflow, reflow_count);
    //
    // 1) For each node, record the hops required to reach the node
    //    from the top of the graph.  Optionally push nodes up or
    //    down as aesthetics require.
    //
    this->computeHopCounts(reflow, reflow_count);
    this->unmarkAllNodes(reflow, reflow_count);

    //
    // 3) Sort the list in descending order of hop,ancestor counts.
    //    Internal nodes are placed according to the order in which
    //    they're wired to inputs.  
    //
    qsort (reflow, reflow_count, sizeof(Node*), LayoutInfo::Comparator);
    this->unmarkAllNodes(reflow, reflow_count);

    //
    // 4) For the first node in the list, walk up the graph placing nodes
    //    marking every node as it's placed.
    //
    n = reflow[0];
    LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
    linfo->setProposedLocation(INITIAL_X,INITIAL_Y);
    this->doPlacements(n, linfo, reflow, reflow_count);

    int max_depth = linfo->getGraphDepth();

    //
    // 5) For each subsequent unmarked node in the list, walk up the graph
    //    until hitting a marked node, then begin walking back down the
    //    graph placing nodes.  If no marked node is hit, then just walk
    //    up the graph placing nodes outside the bounding box of nodes placed
    //    in step (4).
    //
    int xd,yd, minx, miny, maxx, maxy;
    int minx_p, miny_p, maxx_p, maxy_p;
    for (int next=1 ; next<reflow_count; next++) {
	if (this->collisions > TOO_MANY_COLLISIONS) break;
	Node* n = reflow[next];
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	if (linfo->isPositioned()) continue;
	int depth_difference = max_depth - linfo->getGraphDepth();

	Ark* one_input;
	boolean shares_output;
	if (one_input = this->isSingleInputNoOutputNode(n,&shares_output)) {
	    int output;
	    Node* source = one_input->getSourceNode(output);

	    //
	    // Caveat: If the node we're placing has 1 input and 0 connected outputs, 
	    // and it's the only destination node for its source node's output,
	    // then attempt to place it directly beneath its source node's output.
	    //
	    int x,y;
	    if (shares_output) {
		// here we want to scoot over so that we don't obstruct an arc.
		List positioned;
		this->collectPositioned(reflow, reflow_count, positioned);
		this->computeBoundingBox (positioned, minx_p,miny_p,maxx_p,maxy_p);
		int center_p = (minx_p+maxx_p)>>1;

		LayoutInfo* sinfo = (LayoutInfo*)source->getLayoutInformation();
		ASSERT (sinfo->isPositioned());
		int sx,sy;
		sinfo->getXYPosition(sx,sy);

		if (sx < center_p) {
		    int xd,yd;
		    if (!this->positionDestUnderSource (one_input, x,y, xd,yd,
			    reflow, reflow_count, 0, TRUE)) {
			linfo->setCollided(FALSE);
		    } else {
			linfo->setCollided(TRUE);
		    }
		} else {
		    if (!this->positionDestUnderSource (one_input, x,y, xd,yd,
			    reflow, reflow_count, 0, FALSE)) {
			linfo->setCollided(FALSE);
		    } else {
			linfo->setCollided(TRUE);
		    }
		}

	    } else {
		if (!this->positionDestUnderSource (one_input, x,y, xd,yd,
			reflow, reflow_count, 0, output==1)) {
		    linfo->setCollided(FALSE);
		} else {
		    linfo->setCollided(TRUE);
		}
	    }
	    linfo->setProposedLocation (x,y);
	} else {
	    List positioned;
	    this->collectPositioned(reflow, reflow_count, positioned);
	    this->computeBoundingBox (positioned, minx_p,miny_p,maxx_p,maxy_p);

	    // 
	    // Walk up the graph collecting ancestors of the
	    // unpositioned node.  Try to place the node to the left or
	    // right of the bounding box of the placed nodes based
	    // on the location of the center of gravity of the ancestors.  
	    // with respect to the center of gravity of the already-placed nodes.
	    //
	    List ancestors;
	    int y = INITIAL_Y - (depth_difference * this->height_per_level);
	    this->collectPositionedAncestorsOf(n, ancestors);
	    if (ancestors.getSize()) {
		// There was at least 1 positioned ancestor.
		this->computeBoundingBox (ancestors, minx, miny, maxx, maxy);
		int center = (minx + maxx) >> 1;
		int center_p = (minx_p + maxx_p) >> 1;
		if (center < center_p) {
		    linfo->setProposedLocation (minx_p - WIDTH, y);
		} else {
		    linfo->setProposedLocation (maxx_p + WIDTH, y);
		}
	    } else {
		// There was no positioned ancestor which means we could
		// be working on a disconnected subgraph.  Scoot over more.
		linfo->setProposedLocation (maxx_p + 250, y);
	    }

	}
	this->doPlacements (n, linfo, reflow, reflow_count);
    }

    if (this->collisions > TOO_MANY_COLLISIONS) {
	ErrorMessage (
	    "Bailed out of node placement because\n"
	    "the graph is too complicated to fix up.\n"
	);
	retval = FALSE;
	goto cleanup;
    }

    //
    // Error checking, to be removed when the code is stable.
    //
    //for (int l=0; l<reflow_count; l++) {
    //	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
    //	ASSERT (linfo->isPositioned());
    //}

    //
    // 6) apply arc straightening
    //
    this->postProcessing(reflow, reflow_count);

    //
    // 7) To apply placmenets, compute the bounding box of the nodes'
    //    placments, then translate so that all nodes have positive x,y
    //    and so that the center of the graph is near the center of the
    //    vpe if possible.
    //
    this->computeBoundingBox (reflow, reflow_count, minx, miny, maxx, maxy);

    workSpace->beginManyPlacements();
    //this->editor->beginMultipleCanvasMovements();

    // set the objects off from the edges a little bit
    minx-= 15;
    miny-= 15;

    int l;
    for (l=0; l<reflow_count; l++) {
	int x,y;
	Node* n = reflow[l];
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	linfo->getXYPosition (x, y);
	x-= minx;
	y-= miny;
	// By uncommenting this line, I'm able to see what worked
	// and what didn't.  I like this information but I don't
	// what it shown to users.
	//if (linfo->collided()) y+=COLLISION_OFFSET;
	this->editor->saveLocationForUndo(n->getStandIn(), FALSE, (boolean)l);
	n->setVpePosition (x,y);
    }

    this->repositionDecorators((List&)decorators, workSpace, minx, miny, maxx, maxy, (boolean)l);
    
    //
    // 8) Rebuild all the arcs by fetching the workspace data structure,
    //    destroying it and creating a new one.  The workspace lines can
    //    be created and destroyed but never modified.
    //
    for (int k=0; k<reflow_count; k++) {
	Node* n = reflow[k];
 	int input_count = n->getInputCount();
	StandIn* si = n->getStandIn();
	for (int j=1; j<=input_count; j++) {
	    if (!n->isInputVisible(j)) continue;
	    List* arcs = (List*)n->getInputArks(j);
	    Ark* arc;
	    ListIterator iter(*arcs);
	    while (arc = (Ark*)iter.getNext()) {
		ArkStandIn *asi = arc->getArkStandIn();
		delete asi;
		si->addArk (this->editor, arc);
	    }
	}
    }
    workSpace->endManyPlacements();
    //this->editor->endMultipleCanvasMovements();

cleanup:
    //
    // clean up
    //
    for (int i=0; i<reflow_count; i++) {
    	Node* n = reflow[i];
    	// deletes the layout information
    	n->setLayoutInformation(NULL);
    }
    free (reflow);
    return retval;
}

void GraphLayout::unmarkAllNodes(Node* reflow[], int reflow_count)
{
    for (int i=0; i<reflow_count; i++)
	reflow[i]->clearMarked();
}
boolean GraphLayout::hasConnectedInputs(Node *n)
{
    int input_count = n->getInputCount();
    for (int h=1; h<=input_count; h++) {
	if (!n->isInputVisible(h)) continue;
	List* inputs = (List*)n->getInputArks(h);
	if (!inputs) continue;
	if (!inputs->getSize()) continue;
	return TRUE;
    }
    return FALSE;
}

boolean GraphLayout::hasConnectedOutputs(Node *n, Node* other_than)
{
    int dummy;
    int output_count = n->getOutputCount();
    for (int h=1; h<=output_count; h++) {
	if (!n->isOutputVisible(h)) continue;
	List* outputs = (List*)n->getOutputArks(h);
	if (!outputs) continue;
	if (!outputs->getSize()) continue;
	if (other_than) {
	    boolean others_found = FALSE;
	    ListIterator iter(*outputs);
	    Ark* arc;
	    while (arc = (Ark*)iter.getNext()) {
		Node* destination = arc->getDestinationNode(dummy);
		if (destination != other_than) {
		    others_found = TRUE;
		}
	    }
	    if (others_found) 
		return TRUE;
	    else
		continue;
	}
	return TRUE;
    }
    return FALSE;
}

//
// Returns true if the destination location is empty.  We need this because
// placing one StandIn on top of another leads to bumper cars.
//
boolean GraphLayout::nodeCanMoveTo (Node* n, int x, int y, Node* reflow[], int count)
{
    LayoutInfo* n_info = (LayoutInfo*)n->getLayoutInformation();
    LayoutInfo* target_info;
    int tw, th, tx, ty;
    int width, height;
    n_info->getXYSize(width, height);

    for (int i=0; i<count; i++) {
	Node* target = reflow[i];
	if (n==target) continue;
	target_info = (LayoutInfo*)target->getLayoutInformation();
	if (!target_info->isPositioned()) continue;
	target_info->getXYPosition (tx, ty);
	target_info->getXYSize(tw,th);
	if ((x > (tx+tw)) || (y > (ty+th))) continue;
	if (((x+width) < tx) || ((y+height) < ty)) continue;
	return FALSE;
    }
    return TRUE;
}

boolean GraphLayout::arcStraightener(WorkSpace* workSpace, const List& nodeList)
{
    return TRUE;
}

void GraphLayout::postProcessing(Node* reflow[], int reflow_count)
{
}

//
// Make a list of all ancestors that are 1 hop up.  The list is
// sorted according to the input number to which the ancestor is
// wired.  
// We assume that n has already been placed, that the placement is
// stored in linfo.  We're going to position the immediate ancestors
// based on that information
//
void GraphLayout::doPlacements(Node* n, LayoutInfo* linfo, Node* reflow[], int reflow_count)
{
    Ark *left_arc, *arc, *right_arc;
    Node* left_node, *node, *right_node;
    int left_output, output, right_output;
    LayoutInfo *left_info, *info, *right_info;

    LayoutInfo* placement_node_info = (LayoutInfo*)n->getLayoutInformation();

    ListIterator iter;

    List one_hop_up;
    List one_hop_up_nodes;
    int input_count = n->getInputCount();
    int param = 1;
    int param_incr = 1;
    boolean get_set_flag = FALSE;

    //
    // Gets and Sets are handled in a special way because it looks better
    // for them to lined up with their 'link' parameter instead of being
    // lined up with their input/output #1.
    //
    const char* node_name = n->getLabelString();
    if (EqualString(node_name, "Set") ||
	EqualString(node_name, "SetLocal") ||
	EqualString(node_name, "SetGlobal")) {
	param = input_count;
	param_incr =-1;
	get_set_flag = TRUE;
    }

    for (int k=1; k<=input_count; k++,param+=param_incr) {
	if (!n->isInputVisible(param)) continue;
	List* inputs = (List*)n->getInputArks(param);
	if (!inputs) continue;
	iter.setList(*inputs);
	while (arc = (Ark*)iter.getNext()) {
	    Node* src = arc->getSourceNode(output);
	    LayoutInfo* linfo = (LayoutInfo*)src->getLayoutInformation();
	    if (linfo->isPositioned()) continue;
	    if (one_hop_up_nodes.isMember(src) == FALSE) {
		const char* name = src->getLabelString();
		if (EqualString("Get",name)||
		    EqualString("GetGlobal",name)||
		    EqualString("GetLocal",name)) {
		    if (output != 2) continue;
		    one_hop_up.appendElement(arc);
		    one_hop_up_nodes.appendElement(src);
		//} else if (linfo->getGraphDepth() == (placement_node_info->getGraphDepth()-1)) {
		} else if (this->hasNoCloserDescendant(src, n)) {
		    // only handle distant ancestor nodes if those node don't
		    // have a more closely related descendant.
		    one_hop_up.appendElement(arc);
		    one_hop_up_nodes.appendElement(src);
		}
	    }
	}
    }
    //
    // Y-coords for the nodes are given by the hop count.
    // To compute x-coords we have to see how many there are
    // and try to space them accordingly.
    //

    //
    // ToDo:
    // 2) In moveNoInputOneOutputNodesEarlier() try to push things up 
    //    past level 1.  This is needed when you
    //    have a really wide row of receivers and the top of the graph.
    // 8) Look at: (in this order)
    //    InterfaceControl3.net
    //    LightingColorSelectyor.net (needs what's in (2))
    //
    int x,y,offset,input;
    int size = one_hop_up.getSize();
    int left_crowding, right_crowding, crowding, tabs;
    boolean collided;
    int xd,yd;
    switch (size) {
	case 0:
	    break;

	case 1:
	    // with a single ancestor we'll line up the 
	    // tabs in order to make a straight line
	    arc = (Ark*)one_hop_up.getElement(1);
	    node = arc->getSourceNode(output);
	    arc->getDestinationNode(input);
	    info = (LayoutInfo*)node->getLayoutInformation();
	    int x2,y2;
	    boolean left_right;
	    left_right = (input==1);
	    const char* name;
	    name = node->getLabelString();
	    if (!this->positionSourceOverDest (arc,x,y,xd,yd,reflow,
			reflow_count,0,FALSE,left_right)) {
		info->setProposedLocation (x,y);
		info->setCollided(FALSE);
	    } else if (!this->positionSourceOverDest (arc,x2,y2,xd,yd,
			reflow,reflow_count,0,FALSE,!left_right)) {
		info->setProposedLocation (x2,y2);
		info->setCollided(FALSE);
	    } else {
		info->setCollided(TRUE);
		int diff1 = (yd-y) * (yd-y) + (xd-x) * (xd-x);
		int diff2 = (yd-y2) * (yd-y2) + (xd-x2) * (xd-x2);
		if (diff1 < diff2)
		    info->setProposedLocation (x,y);
	    	else
		    info->setProposedLocation (x2,y2);
	    }
	    break;
	case 2:
	    // with a pair of ancestors we'll try for straight
	    // lines only if the standIns won't obstruct lines
	    // for each other.  If they do, then we could make
	    // 1 straight line and offset the other, or we could
	    // offset them both.  Give preference to the node
	    // with no other output arc.
	    left_arc = (Ark*)one_hop_up.getElement(1);
	    right_arc = (Ark*)one_hop_up.getElement(2);
	    left_node = left_arc->getSourceNode(left_output);
	    right_node = right_arc->getSourceNode(right_output);
	    left_info = (LayoutInfo*)left_node->getLayoutInformation();
	    if (!this->positionSourceOverDest (left_arc, x,y, xd,yd,reflow, 
		    reflow_count,0,FALSE,get_set_flag==FALSE)) {
		left_info->setCollided(FALSE);
	    } else {
		left_info->setCollided();
	    }
	    left_info->setProposedLocation (x,y);

	    //
	    // The purpose of passing the offset is to avoid positioning
	    // the 2nd ancestor so that it obstructs the arc of the 1st ancestor.
	    // But if the inputs that the 2 ancestors are connected to are really
	    // far apart, then this offset isn't needed.  So, we need to test
	    // the tabX positions of the input tabs on these arcs to see how
	    // far apart they are.
	    //
	    if (this->isSingleOutputNoInputNode (right_node)) {
		crowding = 0;
	    } else {
		crowding = this->countAncestorsWithinHops (n, 2);
	    }
	    if (get_set_flag) {
		offset = (crowding <= 5 ?  this->computeLeftOffset (right_arc, left_arc)
		    : offset = (130 + (crowding-5) * 40) );
	    } else {
		offset = (crowding <= 5 ?  this->computeRightOffset (left_arc, right_arc)
		    : offset = (130 + (crowding-5) * 40) );
	    }

	    right_info = (LayoutInfo*)right_node->getLayoutInformation();
	    if (!this->positionSourceOverDest (right_arc, x,y, xd,yd,reflow, 
			reflow_count, offset)) {
		right_info->setCollided(FALSE);
	    } else {
		right_info->setCollided();
	    }
	    right_info->setProposedLocation (x,y);
	    break;
	case 3:
	    // with 3, we'll try for 1 straight line for the
	    // 2nd of the 3, and we'll offset the first to the left
	    // and the third to the right.  The offset is calculated by
	    // computing the "crowdedness".  If the graph isn't crowded, then
	    // we use the minimum offset required.
	    arc = (Ark*)one_hop_up.getElement(2);
	    node = arc->getSourceNode(left_output);
	    info = (LayoutInfo*)node->getLayoutInformation();
	    info->setCollided(
		!this->positionSourceOverDest(arc, x,y, xd,yd,reflow, reflow_count)==FALSE
	    );
	    left_arc = (Ark*)one_hop_up.getElement(1);
	    left_node = left_arc->getSourceNode(output);
	    left_info = (LayoutInfo*)left_node->getLayoutInformation();
	    crowding = this->countAncestorsWithinHops (n, 3);
	    if (this->isSingleOutputNoInputNode (left_node)) {
		left_crowding = 0;
	    } else {
		left_crowding = crowding;
	    }
	    offset = (left_crowding <= 5 ?  this->computeLeftOffset (left_arc, arc)
		: -(100 + (left_crowding-6) * 20) );
	    left_info->setCollided(
		!this->positionSourceOverDest(left_arc,x,y,xd,yd,reflow,reflow_count,offset)
	    );
	    right_arc = (Ark*)one_hop_up.getElement(3);
	    right_node = right_arc->getSourceNode(right_output);
	    right_info = (LayoutInfo*)right_node->getLayoutInformation();
	    if (this->isSingleOutputNoInputNode (right_node)) {
		right_crowding = 0;
	    } else {
		right_crowding = crowding;
	    }
	    offset = (right_crowding <= 5 ?  this->computeRightOffset (arc, right_arc)
		: 100 + (right_crowding-6) * 20 );
	    right_info->setCollided(
		!this->positionSourceOverDest(right_arc,x,y,xd,yd,reflow,reflow_count,offset)
	    );
	    break;
	default:
	    // The middle one will have a straight line, the others will be offset.
	    Ark* middle_arc;
	    boolean saw_tooth = FALSE;
	    right_arc = arc = (Ark*)one_hop_up.getElement((size>>1)+1);
	    Ark* saw_tooth_arc=NULL;
	    middle_arc = arc;
	    node = arc->getSourceNode(output);
	    info = (LayoutInfo*)node->getLayoutInformation();
	    boolean was_narrow_node = this->isNarrow(node);
	    if (was_narrow_node) {
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd,reflow,reflow_count,0,TRUE)
		);
	    } else {
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd,reflow, reflow_count)
		);
	    }
	    saw_tooth_arc = NULL;
	    int actual_crowding = this->countAncestorsWithinHops (n, 2);
	    tabs = 0;
	    for (int i=size>>1; i>=1; i--) {
		arc = (Ark*)one_hop_up.getElement(i);
		node = arc->getSourceNode(output);
		info = (LayoutInfo*)node->getLayoutInformation();
		if (info->isPositioned()) continue;
		if (this->isSingleOutputNoInputNode(node)) {
		    crowding = 0;
		    saw_tooth = (this->permits_saw_tooth && 
				 saw_tooth_arc && this->isNarrow(node));
		} else {
		    crowding = actual_crowding;
		    saw_tooth = FALSE;
		}
		switch (crowding) {
		    case 0:
		    case 1:
		    case 2:
		    case 3:
		    case 4:
			if (saw_tooth)
			    offset = this->computeLeftOffset (arc, saw_tooth_arc);
			else if (was_narrow_node && this->isNarrow(node)) {
			    offset = 0;
			    saw_tooth = TRUE;
			} else
			    offset = this->computeLeftOffset (arc, right_arc);
			break;
		    default:
			offset = -((tabs+1)*100);
			break;
		}
		tabs++;
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd,reflow, 
			reflow_count, offset, saw_tooth)
		);
		saw_tooth_arc = right_arc;
		right_arc = arc;
	    }
	    saw_tooth_arc = (Ark*)one_hop_up.getElement(size>>1);
	    left_arc = middle_arc;
	    tabs = 0;
	    for (int i=(size>>1)+2; i<=size; i++) {
		arc = (Ark*)one_hop_up.getElement(i);
		node = arc->getSourceNode(output);
		info = (LayoutInfo*)node->getLayoutInformation();
		if (info->isPositioned()) continue;
		if (this->isSingleOutputNoInputNode(node)) {
		    crowding = 0;
		    saw_tooth = (this->permits_saw_tooth && 
				 saw_tooth_arc && this->isNarrow(node));
		} else {
		    crowding = actual_crowding;
		    saw_tooth = FALSE;
		}
		switch (crowding) {
		    case 0:
		    case 1:
		    case 2:
		    case 3:
		    case 4:
			if (saw_tooth)
			    offset = this->computeRightOffset (saw_tooth_arc, arc);
			else
			    offset = this->computeRightOffset (left_arc, arc);
			break;
		    default:
			offset =  ((tabs+1)*100);
			break;
		}
		tabs++;
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd,reflow, 
			reflow_count, offset, saw_tooth)
		);
		saw_tooth_arc = left_arc;
		left_arc = arc;
	    }
	    break;
    }

    //
    // Tailor Get/Set placment. Only place Gets when hitting the get on its
    // #2 output because Get needs to be lined up over output 2.  Ordinarily,
    // the Get and Set are wired together on #2.   First visit all ancestors
    // that are one hop away AND are 1 level in the graph higher.
    //
    iter.setList(one_hop_up);
    while (arc = (Ark*)iter.getNext()) {
	node = arc->getSourceNode(output);
	LayoutInfo* info = (LayoutInfo*)node->getLayoutInformation();
	const char* name = node->getLabelString();
	if (EqualString("Get",name)||
	    EqualString("GetGlobal",name)||
	    EqualString("GetLocal",name)) {
	    if (output != 2) continue;
	}
	this->doPlacements (node, info, reflow, reflow_count);
    }
}

boolean GraphLayout::positionSourceOverDest (Ark* arc, int& x, int& y, int& best_x, int& best_y, Node* reflow[], int reflow_count, int offset, boolean saw_tooth, boolean prefer_left)
{
    boolean collided = FALSE;
    int input, output;
    int dx,dy, sx, sy;
    int xincr,yincr;
    Node* destination = arc->getDestinationNode(input);
    Node* source = arc->getSourceNode(output);
    LayoutInfo* src_info = (LayoutInfo*)source->getLayoutInformation();
    LayoutInfo* dst_info = (LayoutInfo*)destination->getLayoutInformation();
    StandIn* src_si = source->getStandIn();
    StandIn* dst_si = destination->getStandIn();
    ASSERT (dst_info->isPositioned());
    dst_info->getXYPosition (dx,dy);
    int dst_tab_x = dst_si->getInputParameterTabX(input);
    int src_tab_x = src_si->getOutputParameterTabX(output);
    sx = offset + dx + (dst_tab_x - src_tab_x);
    sy = dy + (src_info->getGraphDepth()-dst_info->getGraphDepth()) * 
	      this->height_per_level;

    int src_w, src_h;
    src_info->getXYSize(src_w, src_h);

    //
    // Compute increments to move the standIn if the desired location is
    // already taken.  If we have small nodes - tiny receivers or Inputs -
    // then we can try moving them up or down otherwise we spread them
    // out horizontally.  We know they're small if the width allows them to
    // be positioned shoulder-to-shoulder without obstructing straight lines.
    //
    if (saw_tooth) {
	xincr = 0;
	sy+= GraphLayout::StandInHeight+6;
	yincr = -(GraphLayout::StandInHeight+9); // should be == StandInHeight
    } else {
	if (offset == 0) xincr = (prefer_left?-20:20);
	else if (offset < 0) xincr = -20;
	else xincr = 20;
	yincr = 0;
    }
    best_x = sx;
    best_y = sy;
    while (!this->nodeCanMoveTo(source, sx,sy,reflow, reflow_count)) {
	sx+= xincr;
	sy+= yincr;
	collided = TRUE;
	if (this->collisions++ > TOO_MANY_COLLISIONS) break;
    }

    src_info->setProposedLocation (sx,sy);
    x = sx;
    y = sy;
    return collided;
}

void GraphLayout::computeBoundingBox (Node* reflow[], int reflow_count,
	int& minx, int& miny, int& maxx, int& maxy)
{
    minx =  miny = 99999999;
    maxx = maxy = -99999999;
    for (int i=0; i<reflow_count; i++) {
	int x,y,w,h;
	Node* n = reflow[i];
	LayoutInfo *li = (LayoutInfo*)n->getLayoutInformation();
	li->getXYPosition (x,y);
	li->getXYSize(w,h);
	if (x < minx) minx = x;
	if (y < miny) miny = y;
	if ((x+w) > maxx) maxx = x+w;
	if ((y+h) > maxy) maxy = y+h;
    }
}

void GraphLayout::computeBoundingBox (List& nodes, 
	int& minx, int& miny, int& maxx, int& maxy)
{
    minx =  miny = 99999999;
    maxx = maxy = -99999999;
    ListIterator li(nodes);
    Node* n;
    while (n = (Node*)li.getNext()) {
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	ASSERT (linfo->isPositioned());
	int x,y,w,h;
	linfo->getXYPosition(x,y);
	linfo->getXYSize(w,h);
	if (x < minx) minx = x;
	if (y < miny) miny = y;
	if ((x+w) > maxx) maxx = x+w;
	if ((y+h) > maxy) maxy = y+h;
    }
}

void GraphLayout::collectPositioned(Node* reflow[], int reflow_count, List& positioned)
{
    for (int i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	if (linfo->isPositioned())
	    positioned.appendElement(n);
    }
}

void GraphLayout::collectPositionedAncestorsOf (Node* n, List& ancestors)
{
    Ark* arc;
    int dummy;
    int input_count = n->getInputCount();
    for (int i=1; i<=input_count; i++) {
	if (!n->isInputVisible(i)) continue;
	List* inputs = (List*)n->getInputArks(i);
	if (!inputs) continue;
	ListIterator iter(*inputs);
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(dummy);
	    LayoutInfo* sli = (LayoutInfo*)source->getLayoutInformation();
	    if (sli->isPositioned()) {
		ancestors.appendElement(source);
	    } else {
		this->collectPositionedAncestorsOf(source, ancestors);
	    }
	}
    }
}

void GraphLayout::repositionDecorators(List& all_decorators, WorkSpace* workSpace, int minx, int miny, int maxx, int maxy, boolean same_event_flag)
{
    //
    // exclude the nodes that aren't in the current page
    //
    List decorators;
    ListIterator decs;
    Decorator* dec;
    decs.setList((List&)all_decorators);
    while (dec = (Decorator*)decs.getNext()) {
	if (dec->getWorkSpace() != workSpace) continue;
	decorators.appendElement(dec);
    }

#if 0
    //
    // Set all the decorators to "Marker" style.  They were probably arranged
    // somewhat and won't fit into the new arrangement.  So to avoid bumper
    // cars.  We'll make them tiny.
    //
    Dictionary* dict = DecoratorStyle::GetDecoratorStyleDictionary("Annotate");
    ASSERT (dict);
    DecoratorStyle* marker_style = (DecoratorStyle*)dict->findDefinition("Marker");
    ASSERT (marker_style);
    this->editor->setDecoratorStyle (&decorators, marker_style);

    //
    // For each decorator, find the closest Node.  After the movement, we'll
    // try to position the decorator so that it's close to the same node.
    //
#endif

    //
    // Update the locations of the decorators.  They'll go around the edges
    // of the bounding box.
    //
    decs.setList(decorators);
    int decx, decy, cum_height=0;
    // put all of them along the right side
    while (dec=(Decorator*)decs.getNext()) {
	this->editor->saveLocationForUndo(dec, FALSE, same_event_flag);
	dec->setXYPosition (maxx + 4 - minx, cum_height);
	dec->getXYSize(&decx, &decy);
	cum_height+= decy+4;
    }
}

boolean GraphLayout::isSingleOutputNoInputNode (Node* n)
{
    int output_count = n->getOutputCount();
    int voc=0; // visible output count
    for (int i=1; i<=output_count; i++) {
	if (n->isOutputVisible(i)) {
	    voc++;
	    if (voc > 1) return FALSE;
	}
    }
    int input_count = n->getInputCount();
    Ark* arc;
    for (int i=1; i<=input_count; i++) {
	if (!n->isInputVisible(i)) continue;
	List* arcs = (List*)n->getInputArks(i);
	if (!arcs) continue;
	if (arcs->getSize()) return FALSE;
    }
    return TRUE;
}
Ark* GraphLayout::isSingleInputNoOutputNode (Node* n, boolean* shares_an_output)
{
    int output_count = n->getOutputCount();
    for (int output=1; output<=output_count; output++) {
	if (!n->isOutputVisible(output)) continue;
	List* outputs = (List*)n->getOutputArks(output);
	if (!outputs) continue;
	if (!outputs->getSize()) continue;
	return NULL;
    }

    int input_count = n->getInputCount();
    Ark* input_arc = NULL;
    Ark* arc;
    for (int input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* inputs = (List*)n->getInputArks(input);
	if (!inputs) continue;
	if (!inputs->getSize()) continue;
	ListIterator arcs(*inputs);
	while (arc = (Ark*)arcs.getNext()) {
	    if (!input_arc) {
		// test for the output has only 1 destination node
		int output;
		Node* source = arc->getSourceNode(output);
		List* outputs = (List*)source->getOutputArks(output);
		ASSERT(outputs);
		if (outputs->getSize() != 1) {
		    *shares_an_output = TRUE;
		} else {
		    *shares_an_output = FALSE;
		}
		LayoutInfo* linfo = (LayoutInfo*)source->getLayoutInformation();
		if (!linfo->isPositioned()) break;
		input_arc = arc;
	    } else {
		return NULL;
	    }
	}
    }
    return input_arc;
}

boolean GraphLayout::positionDestUnderSource (Ark* arc, int& x, int& y, int& best_x, int& best_y, Node* reflow[], int reflow_count, int offset, boolean prefer_left)
{
    boolean collided = FALSE;
    int input, output;
    int dx,dy, sx,sy;
    int xincr,yincr;
    Node* destination = arc->getDestinationNode(input);
    Node* source = arc->getSourceNode(output);
    LayoutInfo* src_info = (LayoutInfo*)source->getLayoutInformation();
    LayoutInfo* dst_info = (LayoutInfo*)destination->getLayoutInformation();
    StandIn* src_si = source->getStandIn();
    StandIn* dst_si = destination->getStandIn();
    ASSERT (src_info->isPositioned());
    src_info->getXYPosition (sx,sy);
    int dst_tab_x = dst_si->getInputParameterTabX(input);
    int src_tab_x = src_si->getOutputParameterTabX(output);
    dx = offset + sx + (-dst_tab_x + src_tab_x);
    dy = sy + ( (dst_info->getGraphDepth()-src_info->getGraphDepth()) * 
	   this->height_per_level
	 );
    if (offset == 0) xincr = (prefer_left?-20:20);
    else if (offset < 0) xincr = -20;
    else xincr = 20;
    yincr = 0;
    best_x = dx;
    best_y = dy;
    while (!this->nodeCanMoveTo(destination, dx,dy,reflow, reflow_count)) {
	dx+= xincr;
	dy+= yincr;
	collided = TRUE;
	if (this->collisions++ > TOO_MANY_COLLISIONS) break;
    }

    dst_info->setProposedLocation (dx,dy);
    x = dx;
    y = dy;
    return collided;
}

//
// The nodes for right_arc have been placed already.  We're preparing to
// place the standIn for the source node of left_arc.  We don't want the
// placement to obstruct the right_arc.  Assume the right_arc is straight.
//
int GraphLayout::computeLeftOffset (Ark* left_arc, Ark* right_arc)
{
    int left_output, right_output;
    int left_input, right_input;
    Node* destination = left_arc->getDestinationNode(left_input);
    LayoutInfo* dest_info = (LayoutInfo*)destination->getLayoutInformation();
    ASSERT (dest_info->isPositioned());
    ASSERT (destination == right_arc->getDestinationNode(right_input));
    Node* left_src = left_arc->getSourceNode(left_output);
    Node* right_src = right_arc->getSourceNode(right_output);
    StandIn* left_si = left_src->getStandIn();
    StandIn* right_si = right_src->getStandIn();
    StandIn* dest_si = destination->getStandIn();

    LayoutInfo* right_info = (LayoutInfo*)right_src->getLayoutInformation();
    LayoutInfo* left_info = (LayoutInfo*)left_src->getLayoutInformation();
    ASSERT (right_info->isPositioned());

    //
    // If the 2 source nodes are at different levels of the graph, then
    // they have to be separated by enough to avoid ark obstruction.
    // If they're at the same level of the graph, then they have to be
    // separated by enough to avoid bumper cars.
    //
    int left_depth = left_info->getGraphDepth();
    int right_depth = right_info->getGraphDepth();

    int right_x, right_y;
    right_info->getXYPosition (right_x, right_y);

    int dx,dy;
    // compute the desired location of the left standin.
    dest_info->getXYPosition (dx,dy);
    int src_tab_x = left_si->getOutputParameterTabX(left_output);
    int dst_tab_x = dx + dest_si->getInputParameterTabX(left_input);
    int desired_left_x = dst_tab_x - src_tab_x;
    int sw,sh;
    left_info->getXYSize(sw,sh);
    if (left_depth == right_depth) {
	// ...and make sure to leave 5 extra pixels because it looks goofy to
	// have standIns really be exactly adjacent
	//
	// the right edge of the left standIn has to clear the
	// left edge of the right standIn.
	if ((desired_left_x+sw+REQUIRED_FUDGE) < right_x) {
	    return 0;
	} else {
	    return right_x - (desired_left_x+sw+DESIRED_FUDGE);
	}
    } else if (left_depth < right_depth) {
	int scoot = ((right_depth-left_depth)*sw);
	scoot = MIN(scoot, 300);
	return scoot;
    } else {
	// the right edge of the left  standIn has to clear the
	// left edge of the right tab instead of the left edge
	// of the right standIn.
	int right_tab_x = dx+dest_si->getInputParameterTabX(right_input);
	if ((desired_left_x+sw) <  right_x) {
	    return 0;
	} else {
	    return right_x - (desired_left_x+sw);
	}
    }
}

//
// The nodes for left_arc have been placed already.  We're preparing to
// place the standIn for the source node of right_arc.  We don't want the
// placement to obstruct the left_arc.  Assume the left_arc is straight.
//
int GraphLayout::computeRightOffset (Ark* left_arc, Ark* right_arc)
{
    int left_output, right_output;
    int left_input, right_input;
    Node* destination = left_arc->getDestinationNode(left_input);
    LayoutInfo* dest_info = (LayoutInfo*)destination->getLayoutInformation();
    ASSERT (dest_info->isPositioned());
    ASSERT (destination == right_arc->getDestinationNode(right_input));
    Node* left_src = left_arc->getSourceNode(left_output);
    Node* right_src = right_arc->getSourceNode(right_output);
    StandIn* left_si = left_src->getStandIn();
    StandIn* right_si = right_src->getStandIn();
    StandIn* dest_si = destination->getStandIn();

    LayoutInfo* left_info = (LayoutInfo*)left_src->getLayoutInformation();
    ASSERT (left_info->isPositioned());
    LayoutInfo* right_info = (LayoutInfo*)right_src->getLayoutInformation();

    //
    // If the 2 source nodes are at different levels of the graph, then
    // they have to be separated by enough to avoid ark obstruction.
    // If they're at the same level of the graph, then they have to be
    // separated by enough to avoid bumper cars.
    //
    int left_depth = left_info->getGraphDepth();
    int right_depth = right_info->getGraphDepth();


    // compute the desired location of the right standin.
    int dx,dy;
    dest_info->getXYPosition (dx,dy);
    int src_tab_x = right_si->getOutputParameterTabX(right_output);
    int dst_tab_x = dx + dest_si->getInputParameterTabX(right_input);
    int desired_right_x = dst_tab_x - src_tab_x;
    int sx,sy;
    int sw,sh;
    left_info->getXYSize(sw,sh);
    left_info->getXYPosition(sx,sy);
    // ...and make sure to leave 5 extra pixels because it looks goofy to
    // have standIns really be exactly adjacent
    if (left_depth == right_depth) {
	// the left edge of the right standIn has to clear the
	// right edge of the left standIn.
	if ((sx+sw+REQUIRED_FUDGE) < desired_right_x) {
	    return 0;
	} else {
	    return (sx+sw+DESIRED_FUDGE) - desired_right_x;
	}
    } else if (right_depth < left_depth) {
	// the node is higher up the tree so we need to
	// scoot it over extra far.  This part is a real
	// hack.  I want to fix this by making a list
	// of all the nodes on a level sorted on increasing expected
	// x coord.
	int rw,rh;
	right_info->getXYSize(rw,rh);
	int scoot = ((left_depth-right_depth)*rw);
	scoot = MIN(scoot, 300);
	return scoot;
    } else {
	// the left edge of the right standIn has to clear the
	// right edge of the left tab instead of the right edge of
	// the left standIn. This is less restrictive.  We can't 
	// compute the size of a tab, so we just guess at it.
	int left_tab_x = dx + dest_si->getInputParameterTabX(left_input);
	int tab_width = 12; // From StandIn.C, tabs are 16 wide;
	if ((left_tab_x + tab_width) < desired_right_x) {
	    return 0;
	} else {
	    return (left_tab_x + tab_width) - desired_right_x;
	}
    }
}

//
//
int GraphLayout::countAncestorsWithinHops (Node* n, int hops)
{
    List ancestors;
    this->listAncestorsWithinHops(n, hops, ancestors);
    return ancestors.getSize();
}

void GraphLayout::listAncestorsWithinHops (Node* n, int hops, List& ancestors)
{
    if (hops <= 0) return ;
    int dummy;
    int input_count = n->getInputCount();
    Ark* arc;
    LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
    for (int i=1; i<=input_count; i++) {
	if (!n->isInputVisible(i)) continue;
	List* arcs = (List*)n->getInputArks(i);
	ListIterator iter(*arcs);
	while (arc = (Ark*)iter.getNext()) {
	    Node* src = arc->getSourceNode(dummy);
	    LayoutInfo* src_info = (LayoutInfo*)src->getLayoutInformation();
	    int distance = linfo->getGraphDepth()-src_info->getGraphDepth();
	    if (distance <= hops) {
		if (ancestors.isMember(src) == FALSE) {
		    ancestors.appendElement(src);
		    this->listAncestorsWithinHops (src, hops-distance, ancestors);
		}
	    }
	}
    }
}

boolean GraphLayout::isNarrow(Node* n)
{
    int width,height;
    LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
    linfo->getXYSize(width,height);
    return (width <= GraphLayout::NarrowStandIn);
}

void GraphLayout::bottomUpTraversal (Node* visit_parents_of, int current_depth, int& min)
{
    int input_count = visit_parents_of->getInputCount();
    LayoutInfo* linfo = (LayoutInfo*)visit_parents_of->getLayoutInformation();
    int next_depth = current_depth - 1;

    linfo->setGraphDepth(current_depth);
    for (int input=1; input<=input_count; input++) {
	if (!visit_parents_of->isInputVisible(input)) continue;

	List* inputs = (List*)visit_parents_of->getInputArks(input);
	ListIterator iter(*inputs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    int output;
	    Node* source = arc->getSourceNode(output);
	    LayoutInfo* sinfo = (LayoutInfo*)source->getLayoutInformation();
	    if (next_depth < min)
		min = next_depth;
	    int cd;
	    if (!sinfo) {
		sinfo = new LayoutInfo();
		sinfo->initialize(source, next_depth);
		cd = next_depth;
	    } else {
		cd = sinfo->getGraphDepth();
	    }
	    if (next_depth < cd) {
		sinfo->setGraphDepth(next_depth);
		this->bottomUpTraversal(source, next_depth, min);
	    } else {
		this->bottomUpTraversal(source, cd, min);
	    }
	}
    }
}

//
// For any node that has an immediate ancestor with a hop count that
// is more than 1 away, we'll try to decrease the hop count so that the
// 2 nodes are adjacent.  This is necessary because we numbered the
// graph starting at the bottom.  We look only at leaf nodes.
// We also examine siblings of the node because that prevents us from
// increasing arc length between our ancestor and our sibling.
//
boolean GraphLayout::adjustHopCounts (Node* reflow[], int reflow_count)
{
    boolean changes_made = FALSE;
    for (int i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	if (this->hasConnectedOutputs(n)) continue;
	const char* cp = n->getLabelString();
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	int required_hops = this->computeRequiredHopsTo(n);
	int sibling_hops = this->computeRequiredHopsToSiblingsOf (n);
	required_hops = MAX(required_hops, sibling_hops);
	if (required_hops < linfo->getGraphDepth()) {
	    int gd = required_hops;
	    this->adjustAncestorHops (n,gd-1);
	    linfo->setGraphDepth(gd);
	    changes_made = TRUE;
	}
    }

    return changes_made;
}

void GraphLayout::adjustAncestorHops (Node* parent, int new_hop_count)
{
    int input_count = parent->getInputCount();
    int output;
    for (int input=1; input<=input_count; input++) {
	if (!parent->isInputVisible(input)) continue;
	List* arcs = (List*)parent->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(output);
	    LayoutInfo* linfo = (LayoutInfo*)source->getLayoutInformation();
	    if (new_hop_count < linfo->getGraphDepth()) {
		linfo->setGraphDepth(new_hop_count);
		this->adjustAncestorHops (source, new_hop_count-1);
	    }
	}
    }
}

int GraphLayout::computeRequiredHopsTo(Node* n)
{
    int output;
    int max_count = 1;
    int input_count = n->getInputCount();
    for (int input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* arcs = (List*)n->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    int count = this->computeRequiredHopsTo(arc->getSourceNode(output));
	    max_count = MAX(count+1, max_count);
	}
    }
    return max_count;
}

int GraphLayout::computeRequiredHopsToSiblingsOf (Node* n)
{
    int dummy;
    int input_count = n->getInputCount();
    int max_hop_count = 1;
    for (int input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* arcs = (List*)n->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(dummy);

	    int output_count = source->getOutputCount();
	    // for each output, fetch connected nodes.
	    for (int output=1; output<=output_count; output++) {
		if (!source->isOutputVisible(output)) continue;
		List* oarcs = (List*)source->getOutputArks(output);
		if (!oarcs) continue;
		ListIterator it(*oarcs);
		Ark* oarc;
		// for each of those nodes fetch required hops
		while (oarc = (Ark*)it.getNext()) {
		    Node* dest = oarc->getDestinationNode(dummy);
		    max_hop_count = MAX(max_hop_count, this->computeRequiredHopsTo(dest));
		}
	    }

	}
    }
    return max_hop_count;
}

//
// compute hops by starting at every leaf node and walking up the graph.
// Initialize the hop counter with a huge number and decrement by 1 at
// each hop.  Then translate all hop counts so that the smallest is set
// to 1.  Then adjust all hop counters so that there is no unneeded
// distance between connected nodes.  We get unneeded space because
// we default leaf nodes to the largest hop count even though that isn't
// accurate.
//
void GraphLayout::computeHopCounts (Node* reflow[], int reflow_count)
{
    //
    // The starting hop counter has no units.  After we finish, we'll
    // translate all hop counters so that the smallest one in the graph
    // is set to 1.
    //
    int smallest_hop_count=99999;
    for (int h=0; h<reflow_count; h++) {
	Node* n = reflow[h];
	if (!this->hasConnectedOutputs(n)) {
	    LayoutInfo* linfo = new LayoutInfo();
	    linfo->initialize (n, 99999);
	    this->bottomUpTraversal(n,99999,smallest_hop_count);
	}
    }

    //
    // We might want to make some adjustments to hop counts.  Sounds like
    // nonsense, but the problem is that there are some nodes that could
    // really have several different hop counts.  Think about a receiver
    // wired directly to an (and only to an output).  Should the receiver
    // be marked 1 and the output be marked 2?  ...or should the output be
    // (max hops) and the receiver be 1-max?  Usually I've tried to keep
    // things pushed down towards the bottom of the graph.  Here we want
    // to push things back towards the top of the graph i.e. reduce the
    // hop count if that will have the effect of shorting the arcs.
    //
    boolean changes_made = TRUE;
    while (changes_made) changes_made = this->adjustHopCounts(reflow, reflow_count);

    //
    // Before we raise the curtain, just one more tweak.  Sometimes
    // (usually at the top of a graph) we get some nodes that have a slew of
    // recievers providing inputs.  It's difficult to place all of these
    // in a pleasing way, so  we'll do a final check for this.  If the
    // situation exists, then we'll artificially decrement the hop count
    // for every other reciever so that the pattern is a little garbagey
    // looking.  
    //
    for (int i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	this->fixForTooManyReceivers(n);
    }

    //
    // Translate to the origin
    //
    for (int h=0; h<reflow_count; h++) {
	Node* n = reflow[h];
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	ASSERT (linfo);
	int gd = linfo->getGraphDepth();
	gd = (gd-smallest_hop_count) + 1;
	linfo->setGraphDepth(gd);
    }

}

//
// Usually this is just a test to see if we're working on a macro or not.
// If there's a node that has lots of tiny inputs, then those inputs will
// get a special arrangement.  We decide at runtime to apply this special
// treatment by finding adjacent inputs whose standIns are really narrow.
// Usually this is only the case when there are a bunch of Input tools wired
// to a single destination node.  We want to know in advance if this is
// the case because using the 'saw tooth' pattern require everything else in
// the graph to be spaced out far enough vertically to squeeze the double
// row on Inputs into place.  Otherwise - for non macro nets - we use a 
// smaller vertical separation.
//
void GraphLayout::computeSawToothPermission(Node* reflow[], int reflow_count)
{
    //
    // Search the graph for nodes that have 2 or more narrow nodes.  If any is
    // found then we'll have to spread things out vertically a little bit more.
    //
    int dummy;
    this->permits_saw_tooth = FALSE;
    for (int i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	int input_count = n->getInputCount();
	int narrow_node_count = 0;
	for (int input=1; input<=input_count; input++) {
	    if (!n->isInputVisible(input)) continue;
	    List* arcs = (List*)n->getInputArks(input);
	    if (!arcs) continue;
	    ListIterator iter(*arcs);
	    Ark* arc;
	    while (arc = (Ark*)iter.getNext()) {
		Node* source = arc->getSourceNode(dummy);
		StandIn* si = source->getStandIn();
		int w,h;
		si->getXYSize(&w,&h);
		if (w <= GraphLayout::NarrowStandIn)
		    narrow_node_count++;
	    }
	}
	if (narrow_node_count >= 2) {
	    this->permits_saw_tooth = TRUE;
	    break;
	}
    }
    if (this->permits_saw_tooth)
	this->height_per_level = GraphLayout::HeightPerLevel;
    else
	this->height_per_level = 
	    GraphLayout::HeightPerLevel - (GraphLayout::HeightPerLevel>>2);
} 

//
// If a node has wide recievers (a.k.a no input-1 output node)
// connected to adjacent input tabs then
// we'll decrement the hop count of 1 receiver so that things aren't
// bunched up too much.  In general this is bad because anything that
// increases arc length is likely to increase the wire crossings.
//
void GraphLayout::fixForTooManyReceivers(Node* n)
{
    boolean previous = FALSE;
    int dummy;
    int input_count = n->getInputCount();
    for (int input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* arcs = (List*)n->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(dummy);
	    if (this->hasConnectedInputs(source)) continue;
	    if (this->hasConnectedOutputs(source, n)) {
		previous = FALSE;
		continue;
	    }
	    LayoutInfo* linfo = (LayoutInfo*)source->getLayoutInformation();
	    int w,h;
	    linfo->getXYSize(w,h);
	    if (w >= GraphLayout::WideStandIn) {
		if (previous) {
		    linfo->setGraphDepth(linfo->getGraphDepth()-1);
		    previous = FALSE;
		} else {
		    previous = TRUE;
		}
	    } else {
		previous = FALSE;
	    }
	}
    }
}

//
// return TRUE if dest has the hop count that is closest to the hop
// count of source.  return FALSE if there is some other node that's connected
// to source that has a shorter arcs.  We use this information in order to
// cause source to be placed with its closest living relative.
//
boolean GraphLayout::hasNoCloserDescendant (Node* source, Node* dest)
{
    int dummy;
    LayoutInfo* src_info = (LayoutInfo*)source->getLayoutInformation();
    LayoutInfo* dst_info = (LayoutInfo*)dest->getLayoutInformation();

    int min_depth = dst_info->getGraphDepth();
    int output_count = source->getOutputCount();
    for (int output=1; output<=output_count; output++) {
	if (!source->isOutputVisible(output)) continue;
	List* arcs = (List*)source->getOutputArks(output);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* destination = arc->getDestinationNode(dummy);
	    if (destination == dest) continue;
	    LayoutInfo* info = (LayoutInfo*)destination->getLayoutInformation();
	    if (info->getGraphDepth() < min_depth) {
		// a closer relative was found
		return FALSE;
	    }
	}
    }

    return TRUE;
}
