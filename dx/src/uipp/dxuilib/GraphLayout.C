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
#include "ListIterator.h"
#include "Network.h"
#include "EditorWorkSpace.h"
#include "Node.h"
#include "StandIn.h"
#include "Ark.h"
#include "ArkStandIn.h"
#include "ErrorDialogManager.h"
#include "VPEAnnotator.h"
#include "DecoratorStyle.h"
#include "Dictionary.h"
#include <math.h>
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
// 2) Set up associations between annotations and nodes by finding
//    each annotation's nearest node.  This happens after computeHopCounts()
//    because we need to use the LayoutInfo that computeHopCounts() sets
//    up.
// 3) Sort the list in descending order of hop counts.
//    Internal nodes are placed according to the order in which
//    they're wired to inputs. Caveat: when placing nodes we're going
//    to give preference to nodes that are 1 hop away. (Of course
//    everything a node is connected to is 1 hop away.  But a nodes
//    that's 5 hops from the top might be connected to a node that's
//    just 2 hops from the top.)
// 4) For the first node in the list, walk up the graph placing nodes.
// 5) For each subsequent node in the list, walk the graph from that node
//    until hitting a placed node.  If no placed node is hit, then just walk
//    up the graph placing nodes outside the bounding box of nodes placed
//    in step (4).
// 7) To apply placments, compute the bounding box of the nodes'
//    placments, then translate so that all nodes have positive x,y.
// 8) Rebuild all the arcs by fetching the workspace data structure,
//    destroying it and creating a new one.  The workspace lines can
//    be created and destroyed but never modified.
//
// Extras:
// 1) Before beginning, gather up all vpe annotations.  Compute distances
// to standIns, then sort in ascending order.  At end placment, try to 
// put each decorator close to its nearest standIn.
// 2) Get/Set nodes are special cased to ensure that they're lined
// up on their 'Link' parameter.
// 3) Special handling for any node that has 3 or more connections to a single
// ancestor. Make sure that source gets placed first.
// ToDo:
// 1) A common thing is Switch(Inquire(foo,"is null+1"),foo,...);
// This should get special handling
// 2) I count upstream nodes in order to determine how much to spread things
// out horizontally but I should really count up the upstream standIns' widths.
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
int GraphLayout::HeightPerLevel = 90;
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
// Identify original location of a decorator with respect to its
// closes node.
//
#define DECORATOR_ABOVE 1
#define DECORATOR_BELOW 2
#define DECORATOR_LEFT  4
#define DECORATOR_RIGHT 8

//
// x distance to separate disconnected groups of nodes from each other
//
#define HORIZONTAL_GROUP_SPACING 30

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
// get stored into an unsigned short.  I used lots of different values
// in these constants as a way of testing.
//
#define INITIAL_X 0//5000 
#define INITIAL_Y 0//5000

static boolean debug = FALSE;

//
// Comparator function used with qsort.  It says we're going to sort things
// by decreasing hop count. So the things early in the list are at the bottom
// of the graph.
//
int NodeInfo::Comparator (const void* a, const void* b)
{
    Node** aptr = (Node**)a;
    Node** bptr = (Node**)b;
    Node* anode = (Node*)*aptr;
    Node* bnode = (Node*)*bptr;
    NodeInfo* ainfo = (NodeInfo*)anode->getLayoutInformation();
    NodeInfo* binfo = (NodeInfo*)bnode->getLayoutInformation();

    // descending order of hop count
    if (ainfo->hops > binfo->hops) return -1;
    if (ainfo->hops < binfo->hops) return 1;

    //
    // If the 2 nodes connect to different outputs of the same parent,
    // then sort by that.  Different strategies to try:
    // 1) output 1 1st, output 2 2nd, etc...
    // 2) middle output 1st, 1 left 2nd, 1 right 3rd, 2 left 4th, etc...
    // 3) odd numbered outputs first, then even numbered outputs.  This
    //    might produce a few straight lines.
    //
    boolean shares_output1;
    Ark* ark1 = GraphLayout::IsSingleInputNoOutputNode(anode, &shares_output1, FALSE);
    if (ark1) {
	boolean shares_output2;
	Ark* ark2 = GraphLayout::IsSingleInputNoOutputNode(bnode, &shares_output2, FALSE);
	const char* cp1 = anode->getLabelString();
	const char* cp2 = bnode->getLabelString();

	if (ark2) {
	    Node *parent1, *parent2;
	    int input1, input2;
	    parent1 = ark1->getSourceNode(input1);
	    parent2 = ark2->getSourceNode(input2);
	    if (parent1 == parent2) {
		if (input1 != input2) {
		    int output_count = parent1->getOutputCount();
		    int middle = (output_count>>1)+1;
		    int diff1 = middle - input1;
		    int diff2 = middle - input2;
		    if (diff1<0) diff1=-diff1;
		    if (diff2<0) diff2=-diff2;
		    if (diff1 < diff2) return -1;
		    if (diff2 < diff1) return 1;
		}
	    }
	}
    }

    return 0;
}

void LayoutInfo::initialize (UIComponent* uic)
{
    ASSERT(uic);
    uic->getXYPosition(&this->orig_x, &this->orig_y);
    this->x = this->y = -1;
    uic->getXYSize(&this->w, &this->h);
    this->initialized = TRUE;
}

void NodeInfo::initialize(Node* n, int hops)
{
    n->setLayoutInformation(this);
    this->hops = hops;
    this->LayoutInfo::initialize(n->getStandIn());
}

void AnnotationInfo::initialize (VPEAnnotator* dec)
{
    dec->setLayoutInformation(this);
    this->LayoutInfo::initialize(dec);
}

boolean GraphLayout::entireGraph(WorkSpace* workSpace, const List& nodes, const List& decorators)
{
    int offset;
    List nodeList;

    debug = (getenv("DEBUG_PLACEMENT") ? TRUE : FALSE);

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
    }
    ASSERT (reflow_count == reflow_size);

    //
    // 1) For each node, record the hops required to reach the node
    //    from the top of the graph.  Optionally push nodes up or
    //    down as aesthetics require.
    //
    this->computeHopCounts(reflow, reflow_count);
    this->computeSawToothPermission(reflow, reflow_count);

    //
    // 2) Set up associations between annotations and nodes by finding
    // each annotation's nearest node.  This happens after computeHopCounts()
    // because we need to use the LayoutInfo that computeHopCounts() sets
    // up.
    //
    List decorators_in_current_page;
    int widest_decorator = 0;
    int tallest_decorator = 0;
    this->prepareAnnotationPlacement(decorators_in_current_page, 
	    reflow, reflow_count, decorators, workSpace, widest_decorator,
	    tallest_decorator);

    //
    // 3) Sort the list in descending order of hop,ancestor counts.
    //    Internal nodes are placed according to the order in which
    //    they're wired to inputs.  
    //
    qsort (reflow, reflow_count, sizeof(Node*), NodeInfo::Comparator);

    //
    // 3.5) Group the nodes.  Any 2 nodes that have a path between them
    //      go into the same group.
    //
    int next;
    for (next=0; next<reflow_count; next++) {
	Node* n = reflow[next];
	NodeInfo* ni = (NodeInfo*)n->getLayoutInformation();
	List* connected = ni->getConnectedNodes(n);
	ListIterator iter(*connected);
	if (ni->getLayoutGroup()) continue;
	LayoutGroup* group = new LayoutGroup(this->layout_groups.getSize());
	this->layout_groups.appendElement(group);
	while (n=(Node*)iter.getNext()) {
	    NodeInfo* info = (NodeInfo*)n->getLayoutInformation();
	    info->setLayoutGroup(group);
	}
    }
    if (debug) {
	for (next=0; next<reflow_count; next++) {
	    Node* n = reflow[next];
	    NodeInfo* ni = (NodeInfo*)n->getLayoutInformation();
	    LayoutGroup* group = ni->getLayoutGroup();
	    ASSERT (group);
	    fprintf (stdout, "%s[%d] %s hops=%d in group %d\n",
		__FILE__,__LINE__,n->getLabelString(), ni->getGraphDepth(), 
		group->getId());
	}
    }

    //
    // 4) For the first node in the list, walk up the graph placing nodes.
    //
    n = reflow[0];

    if (debug)
	fprintf (stdout, "%s[%d] %s placing\n", __FILE__,__LINE__,n->getLabelString());

    NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
    linfo->setProposedLocation(INITIAL_X,INITIAL_Y);
    List positioned;
    this->doPlacements(n, linfo, reflow, reflow_count, positioned);
    this->repositionNewPlacements (n, TRUE, positioned);

    //
    // 5) For each subsequent unmarked node in the list, walk up the graph
    //    until hitting a marked node, then begin walking back down the
    //    graph placing nodes.  If no marked node is hit, then just walk
    //    up the graph placing nodes outside the bounding box of nodes placed
    //    in step (4).
    //
    for (next=1 ; next<reflow_count; next++) {
	if (this->collisions > TOO_MANY_COLLISIONS) break;
	n = reflow[next];
	NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
	if (linfo->isPositioned()) continue;

	if (debug)
	    fprintf (stdout, "%s[%d] %s placing...", 
		__FILE__,__LINE__,n->getLabelString());

	List* connected = linfo->getConnectedNodes(n);
	ListIterator iter(*connected);
	Node* node;
	boolean separated = TRUE;
	int y;
	while (node=(Node*)iter.getNext()) {
	    NodeInfo* ninfo = (NodeInfo*)node->getLayoutInformation();
	    if (!ninfo->isPositioned()) continue;
	    int dummy;
	    ninfo->getXYPosition (dummy, y);
	    separated = FALSE;
	    int dd = ninfo->getGraphDepth() - linfo->getGraphDepth();
	    y-= (dd*this->height_per_level);
	    break;
	}

	if (!separated) {
	    if (debug) fprintf (stdout, " [%d] connected\n", __LINE__);
	    linfo->setProposedLocation (20000, y);
	} else {
	    if (debug) fprintf (stdout, " [%d] disconnected", __LINE__);
	    // There was no positioned connected node. We are
	    // be working on a disconnected subgraph.  
	    linfo->setProposedLocation (INITIAL_X, INITIAL_Y);
	}
	positioned.clear();
	this->doPlacements (n, linfo, reflow, reflow_count, positioned);
	this->repositionNewPlacements(n, separated, positioned);
	if (debug) fprintf (stdout, "\n");
    }

    if (this->collisions > TOO_MANY_COLLISIONS) {
	ErrorMessage (
	    "Bailed out of automatic layout because\n"
	    "too many nodes' placements conflicted."
	);
	retval = FALSE;
	goto cleanup;
    }

    //
    // 5.5) All nodes have now been divied up into groups.  Within groups,
    // the nodes have been positioned.  Each group is a set of nodes with
    // connections internal to the group.  Now it's time to position each
    // group.  This should be accomplished with respect shown to the arrangement
    // of the groups within the canvas before automatic layout was kicked
    // off.  This is what gives authors a measure of control over the 
    // appearance of the result.
    // 
    this->repositionGroups(reflow, reflow_count);

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
    int minx, miny, maxx, maxy;
    this->computeBoundingBox (reflow, reflow_count, minx, miny, maxx, maxy);

    workSpace->beginManyPlacements();

    //
    // The curtain is almost ready to go up.  We must adjust the location of all
    // nodes to be close to the upper left corner of the canvas.  The vpe annotation
    // still hasn't been placed, so we'll allow some extra room so that the annotation
    // can be placed conveniently.
    //
    offset = MIN(widest_decorator, 200);
    offset = MAX(offset, 10);
    minx-= offset;
    offset = MIN(tallest_decorator, 200);
    offset = MAX(offset, 10);
    miny-= offset;

    int l;
    for (l=0; l<reflow_count; l++) {
	int x,y;
	Node* n = reflow[l];
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	linfo->getXYPosition (x, y);
	x-= minx;
	y-= miny;
	linfo->setProposedLocation (x, y);
	// By uncommenting this line, I'm able to see what worked
	// and what didn't.  I like this information but I don't
	// what it shown to users.
	//if (linfo->collided()) y+=COLLISION_OFFSET;
	this->editor->saveLocationForUndo(n->getStandIn(), FALSE, (boolean)l);
	n->setVpePosition (x,y);
    }

    this->repositionDecorators(decorators_in_current_page, (boolean)l, reflow, reflow_count);
    
    //
    // 8) Rebuild all the arcs by fetching the workspace data structure,
    //    destroying it and creating a new one.  The workspace lines can
    //    be created and destroyed but never modified.
    //
    int k;
    for (k=0; k<reflow_count; k++) {
	Node* n = reflow[k];
 	int input_count = n->getInputCount();
	StandIn* si = n->getStandIn();
	int j;
	for (j=1; j<=input_count; j++) {
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

cleanup:
    //
    // Each node will delete its NodeInfo
    //
    int i;
    for (i=0; i<reflow_count; i++) {
    	Node* n = reflow[i];
    	// deletes the layout information
    	n->setLayoutInformation(NULL);
    }
    free (reflow);

    //
    // erase all the group records
    //
    ListIterator iter(this->layout_groups);
    LayoutGroup* g;
    while (g = (LayoutGroup*)iter.getNext()) delete g;
    this->layout_groups.clear();

    //
    // each decorator will deletes its AnnotationInfo
    //
    VPEAnnotator* dec;
    iter.setList(decorators_in_current_page);
    while (dec = (VPEAnnotator*)iter.getNext()) {
	dec->setLayoutInformation(NUL(AnnotationInfo*));
    }
    return retval;
}

void GraphLayout::unmarkAllNodes(Node* reflow[], int reflow_count)
{
    int i;
    for (i=0; i<reflow_count; i++)
	reflow[i]->clearMarked();
}
boolean GraphLayout::hasConnectedInputs(Node *n)
{
    int input_count = n->getInputCount();
    int h;
    for (h=1; h<=input_count; h++) {
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
    int h;
    for (h=1; h<=output_count; h++) {
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
boolean GraphLayout::nodeCanMoveTo (Node* n, int x, int y)
{
    NodeInfo* info = (NodeInfo*)n->getLayoutInformation();
    List* connected_nodes = info->getConnectedNodes(n);

    int width, height;
    info->getXYSize(width, height);

    ListIterator iter(*connected_nodes);
    Node* target;
    int tw, th, tx, ty;
    while (target = (Node*)iter.getNext()) {
	NodeInfo* target_info = (NodeInfo*)target->getLayoutInformation();
	if (target_info == info) continue;
	if (!target_info->isPositioned()) continue;
	target_info->getXYPosition (tx, ty);
	target_info->getXYSize(tw,th);
	if ((x > (tx+tw)) || (y > (ty+th))) continue;
	if (((x+width) < tx) || ((y+height) < ty)) continue;
	if (debug) {
	    fprintf (stdout, "%s[%d] %s movement to %d,%d conflicted with %s\n",
		    __FILE__,__LINE__,n->getLabelString(), x,y,target->getLabelString());
	}
	return FALSE;
    }
    return TRUE;
}

boolean GraphLayout::CanMoveTo (LayoutInfo* info, int x, int y, Node* reflow[], int count, List* decorators)
{
    int width, height;
    info->getXYSize(width, height);

    int tw, th, tx, ty;
    int i;
    for (i=0; i<count; i++) {
	Node* target = reflow[i];
	NodeInfo* target_info = (NodeInfo*)target->getLayoutInformation();
	if (target_info == info) continue;
	if (!target_info->isPositioned()) continue;
	target_info->getXYPosition (tx, ty);
	target_info->getXYSize(tw,th);
	if ((x > (tx+tw)) || (y > (ty+th))) continue;
	if (((x+width) < tx) || ((y+height) < ty)) continue;
	return FALSE;
    }
    if (decorators) {
	ListIterator iter(*decorators);
	LayoutInfo* target_info;
	VPEAnnotator* dec;
	while (dec = (VPEAnnotator*)iter.getNext()) {
	    target_info = (LayoutInfo*)dec->getLayoutInformation();
	    if (target_info == info) continue;
	    if (!target_info->isPositioned()) continue;
	    target_info->getXYPosition (tx, ty);
	    target_info->getXYSize(tw,th);
	    if ((x > (tx+tw)) || (y > (ty+th))) continue;
	    if (((x+width) < tx) || ((y+height) < ty)) continue;
	    return FALSE;
	}
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
void GraphLayout::doPlacements(Node* n, LayoutInfo* linfo, Node* reflow[], int reflow_count, List& positioned)
{
    Ark *left_arc, *arc, *right_arc;
    Node* left_node, *node, *right_node;
    int left_output, output, right_output;
    NodeInfo *left_info, *info, *right_info;

    ListIterator iter;

    List one_hop_up; // a list of arks
    List one_hop_up_nodes;
    int input_count = n->getInputCount();
    int param = 1;
    int param_incr = 1;
    boolean get_set_flag = FALSE;

    //
    // Gets and Sets are handled in a special way because it looks better
    // for them to be lined up with their 'link' parameter instead of being
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

    //
    // Inspired by Supervise{Window,State} we'll watch out for pairs of 
    // nodes that have 3 or more connections between them.  For any such
    // pair, we'll mark the first arc as being a priority arc and we'll
    // try to position the source directly over the dest before working
    // on any of the other sources.  Really the idea is we should sort
    // the input nodes on the basis of the number of connections but
    // for almost all cases the number of connections is 1.
    // 
    Ark* priority_arc;
    Node* priority_node = this->hasPriorityAncestor(n, &priority_arc, 3);
    if (priority_node) {
	info = (NodeInfo*)priority_node->getLayoutInformation();
	if (info->isPositioned())
	    priority_node = NUL(Node*);
    }

    int k;
    for (k=1; k<=input_count; k++,param+=param_incr) {
	if (!n->isInputVisible(param)) continue;
	List* inputs = (List*)n->getInputArks(param);
	if (!inputs) continue;
	iter.setList(*inputs);
	while (arc = (Ark*)iter.getNext()) {
	    Node* src = arc->getSourceNode(output);
	    LayoutInfo* linfo = (LayoutInfo*)src->getLayoutInformation();
	    if (src == priority_node) continue;
	    if (linfo->isPositioned()) continue;
	    if (one_hop_up_nodes.isMember(src) == FALSE) {
		const char* name = src->getLabelString();
		if (EqualString("Get",name)||
		    EqualString("GetGlobal",name)||
		    EqualString("GetLocal",name)) {
		    if (output != 2) continue;
		    one_hop_up.appendElement(arc);
		    one_hop_up_nodes.appendElement(src);
		} else if (this->hasNoCloserDescendant(src, n)) {
		    // only handle distant ancestor nodes if those node don't
		    // have a more closely related descendant.
		    one_hop_up.appendElement(arc);
		    one_hop_up_nodes.appendElement(src);
		}
	    }
	}
    }

    int x,y,offset,input;
    int size = one_hop_up.getSize();
    int left_crowding, right_crowding, crowding, tabs;
    int xd,yd;

    //
    // We found a special case so we'll position it first so that it
    // isn't shoved around by other placements that share a level in
    // the graph and a destination.
    //
    if (priority_node) {
	arc = priority_arc;
	info = (NodeInfo*)priority_node->getLayoutInformation();
	int x2,y2;
	if (!this->positionSourceOverDest (arc,x,y,xd,yd, 0,FALSE,TRUE)) {
	    info->setCollided(FALSE);
	} else if (!this->positionSourceOverDest (arc,x2,y2,xd,yd, 0,FALSE,FALSE)) {
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
	positioned.appendElement(priority_node);
    }

    switch (size) {
	case 0:
	    break;

	case 1:
	    // with a single ancestor we'll line up the 
	    // tabs in order to make a straight line
	    arc = (Ark*)one_hop_up.getElement(1);
	    node = arc->getSourceNode(output);
	    arc->getDestinationNode(input);
	    info = (NodeInfo*)node->getLayoutInformation();
	    int x2,y2, nth_tab;
	    boolean left_right;
	    this->countConnectedInputs (node, input, nth_tab);
	    left_right = (nth_tab==1);
	    if (!this->positionSourceOverDest (arc,x,y,xd,yd ,0,FALSE,left_right)) {
		info->setCollided(FALSE);
	    } else if (!this->positionSourceOverDest (arc,x2,y2,xd,yd,
			0,FALSE,!left_right)) {
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
	    positioned.appendElement(node);
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
	    left_info = (NodeInfo*)left_node->getLayoutInformation();
	    if (!this->positionSourceOverDest (left_arc, x,y, xd,yd,
		    0,FALSE,get_set_flag==FALSE)) {
		left_info->setCollided(FALSE);
	    } else {
		left_info->setCollided();
	    }
	    positioned.appendElement(left_node);

	    //
	    // The purpose of passing the offset is to avoid positioning
	    // the 2nd ancestor so that it obstructs the arc of the 1st ancestor.
	    // But if the inputs that the 2 ancestors are connected to are really
	    // far apart, then this offset isn't needed.  So, we need to test
	    // the tabX positions of the input tabs on these arcs to see how
	    // far apart they are.
	    //
	    right_info = (NodeInfo*)right_node->getLayoutInformation();
	    if ((right_info->getGraphDepth() < left_info->getGraphDepth()) && 
		(GraphLayout::IsSingleOutputNoInputNode(right_node))) {
		int w,h;
		left_info->getXYSize(w,h);
		offset = w>>1;
	    } else {
		if (GraphLayout::IsSingleOutputNoInputNode(right_node)) {
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

	    }
	    if (!this->positionSourceOverDest (right_arc, x,y, xd,yd, offset)) {
		right_info->setCollided(FALSE);
	    } else {
		right_info->setCollided();
	    }
	    positioned.appendElement(right_node);
	    break;
	default:
	    // The middle one will have a straight line, the others will be offset.
	    Ark* middle_arc;
	    boolean saw_tooth = FALSE;
	    right_arc = arc = (Ark*)one_hop_up.getElement((size>>1)+1);
	    Ark* saw_tooth_arc=NULL;
	    middle_arc = arc;
	    node = arc->getSourceNode(output);
	    info = (NodeInfo*)node->getLayoutInformation();
	    int prev_depth = info->getGraphDepth();
	    int middle_depth = prev_depth;
	    boolean was_narrow_node = this->isNarrow(node);
	    if (was_narrow_node) {
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd,0,TRUE)
		);
	    } else {
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd)
		);
	    }
	    positioned.appendElement(node);
	    saw_tooth_arc = NULL;
	    int actual_crowding = this->countAncestorsWithinHops (n, 2);
	    tabs = 0;
	    int i;
	    for (i=size>>1; i>=1; i--) {
		arc = (Ark*)one_hop_up.getElement(i);
		node = arc->getSourceNode(output);
		info = (NodeInfo*)node->getLayoutInformation();
		if (info->isPositioned()) continue;
		if (GraphLayout::IsSingleOutputNoInputNode(node)) {
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
			if (saw_tooth) {
			    offset = this->computeLeftOffset (arc, saw_tooth_arc);
			} else if (was_narrow_node && this->isNarrow(node)) {
			    offset = 0;
			    saw_tooth = TRUE;
			} else if (info->getGraphDepth() != prev_depth) {
			    // compute the left edge of the previous node to
			    // avoid an ugly bend.
			    offset = 0;
			    if (right_arc) {
				int dummy;
				Node* to_avoid = right_arc->getSourceNode(dummy);
				LayoutInfo* tainfo = (LayoutInfo*)
				    to_avoid->getLayoutInformation();
				int w,h;
				tainfo->getXYSize(w,h);
				offset = -(w>>1);
				if (info->getGraphDepth() < prev_depth) {
				    offset+= 10;
				}
			    }
			} else {
			    offset = this->computeLeftOffset (arc, right_arc);
			}
			break;
		    default:
			offset = -((tabs+1)*100);
			break;
		}
		tabs++;
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd,offset, saw_tooth, TRUE)
		);
		positioned.appendElement(node);
		saw_tooth_arc = right_arc;
		right_arc = arc;
		prev_depth = info->getGraphDepth();
	    }
	    saw_tooth_arc = (Ark*)one_hop_up.getElement(size>>1);
	    left_arc = middle_arc;
	    prev_depth = middle_depth;
	    tabs = 0;
	    for (i=(size>>1)+2; i<=size; i++) {
		arc = (Ark*)one_hop_up.getElement(i);
		node = arc->getSourceNode(output);
		info = (NodeInfo*)node->getLayoutInformation();
		if (info->isPositioned()) continue;
		if (GraphLayout::IsSingleOutputNoInputNode(node)) {
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
			else if (info->getGraphDepth() != prev_depth) {
			    offset = 0;
			    // compute the right edge of the previous node to
			    // avoid an ugly bend.
			    offset = 0;
			    if (left_arc) {
				int dummy;
				Node* to_avoid = right_arc->getSourceNode(dummy);
				LayoutInfo* tainfo = (LayoutInfo*)
				    to_avoid->getLayoutInformation();
				int w,h;
				tainfo->getXYSize(w,h);
				offset = w>>1;
				if (info->getGraphDepth() < prev_depth) {
				    offset-= 10;
				}
			    }
			} else
			    offset = this->computeRightOffset (left_arc, arc);
			break;
		    default:
			offset =  ((tabs+1)*100);
			break;
		}
		tabs++;
		info->setCollided(
		    !this->positionSourceOverDest(arc, x,y, xd,yd, offset, saw_tooth)
		);
		positioned.appendElement(node);
		saw_tooth_arc = left_arc;
		left_arc = arc;
		prev_depth = info->getGraphDepth();
	    }
	    break;
    }

    //
    // Tailor Get/Set placment. Only place Gets when hitting the get on its
    // #2 output because Get needs to be lined up over output 2.  Ordinarily,
    // the Get and Set are wired together on #2.   First visit all ancestors
    // that are one hop away AND are 1 level in the graph higher.
    //
    if (priority_node) {
	LayoutInfo* info = (LayoutInfo*)priority_node->getLayoutInformation();
	this->doPlacements (priority_node, info, reflow, reflow_count, positioned);
    }
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
	this->doPlacements (node, info, reflow, reflow_count, positioned);
    }
}

boolean GraphLayout::positionSourceOverDest (Ark* arc, int& x, int& y, int& best_x, int& best_y, int offset, boolean saw_tooth, boolean prefer_left, boolean place_the_node)
{
    boolean collided = FALSE;
    int input, output;
    int dx,dy, sx, sy;
    int xincr,yincr;
    Node* destination = arc->getDestinationNode(input);
    Node* source = arc->getSourceNode(output);
    NodeInfo* src_info = (NodeInfo*)source->getLayoutInformation();
    NodeInfo* dst_info = (NodeInfo*)destination->getLayoutInformation();
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
    while (!this->nodeCanMoveTo(source, sx,sy)) {
	collided = TRUE;
	if (!place_the_node) break;
	sx+= xincr;
	sy+= yincr;
	if (this->collisions++ > TOO_MANY_COLLISIONS) break;
    }

    if (place_the_node) src_info->setProposedLocation (sx,sy);
    x = sx;
    y = sy;
    return collided;
}

boolean GraphLayout::computeBoundingBox (Node* reflow[], int reflow_count,
	int& minx, int& miny, int& maxx, int& maxy, List* decorators)
{
    boolean valid_information = FALSE;
    minx =  miny = 99999999;
    maxx = maxy = -99999999;
    int x,y,w,h;
    int i;
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	LayoutInfo *li = (LayoutInfo*)n->getLayoutInformation();
	ASSERT (li->isPositioned());
	li->getXYPosition (x,y);
	li->getXYSize(w,h);
	if (x < minx) minx = x;
	if (y < miny) miny = y;
	if ((x+w) > maxx) maxx = x+w;
	if ((y+h) > maxy) maxy = y+h;
	valid_information = TRUE;
    }
    if (decorators) {
	ListIterator iter(*decorators);
	VPEAnnotator* dec;
	while (dec=(VPEAnnotator*)iter.getNext()) {
	    LayoutInfo* info = (LayoutInfo*)dec->getLayoutInformation();
	    info->getXYPosition (x,y);
	    info->getXYSize(w,h);
	    if (x < minx) minx = x;
	    if (y < miny) miny = y;
	    if ((x+w) > maxx) maxx = x+w;
	    if ((y+h) > maxy) maxy = y+h;
	}
    }
    return valid_information;
}

boolean GraphLayout::computeBoundingBox (List& nodes, 
	int& minx, int& miny, int& maxx, int& maxy)
{
    boolean valid_information = FALSE;
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
	valid_information = TRUE;
    }
    return valid_information;
}

void GraphLayout::repositionDecorators(List& decorators, boolean sef, Node* reflow[], int reflow_count)
{
    int minx, miny, maxx, maxy;
    this->computeBoundingBox (reflow, reflow_count, minx, miny, maxx, maxy);
    AnnotationInfo::NextX = maxx+4;
    AnnotationInfo::NextY = 10;
    ListIterator decs(decorators);
    boolean same_event_flag = sef;
    int decx, decy; 
    VPEAnnotator* dec;
    while (dec=(VPEAnnotator*)decs.getNext()) {
	this->editor->saveLocationForUndo(dec, FALSE, same_event_flag);
	same_event_flag = TRUE;
	AnnotationInfo* ainfo = (AnnotationInfo*)dec->getLayoutInformation();
	ainfo->reposition(reflow, reflow_count, decorators);
	ainfo->getXYPosition (decx, decy);
	dec->setXYPosition (decx, decy);
    }
}

boolean GraphLayout::IsSingleOutputNoInputNode (Node* n)
{
    int i;
    int output_count = n->getOutputCount();
    int voc=0; // visible output count
    for (i=1; i<=output_count; i++) {
	if (n->isOutputVisible(i)) {
	    voc++;
	    if (voc > 1) return FALSE;
	}
    }
    int input_count = n->getInputCount();
    Ark* arc;
    for (i=1; i<=input_count; i++) {
	if (!n->isInputVisible(i)) continue;
	List* arcs = (List*)n->getInputArks(i);
	if (!arcs) continue;
	if (arcs->getSize()) return FALSE;
    }
    return TRUE;
}
Ark* GraphLayout::IsSingleInputNoOutputNode (Node* n, boolean* shares_an_output, boolean positioned)
{
    int output_count = n->getOutputCount();
    int output;
    for (output=1; output<=output_count; output++) {
	if (!n->isOutputVisible(output)) continue;
	List* outputs = (List*)n->getOutputArks(output);
	if (!outputs) continue;
	if (!outputs->getSize()) continue;
	return NULL;
    }

    int input_count = n->getInputCount();
    Ark* input_arc = NULL;
    Ark* arc;
    int input;
    for (input=1; input<=input_count; input++) {
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
		if (positioned) {
		    LayoutInfo* linfo = (LayoutInfo*)source->getLayoutInformation();
		    if (!linfo->isPositioned()) break;
		}
		input_arc = arc;
	    } else {
		return NULL;
	    }
	}
    }
    return input_arc;
}

boolean GraphLayout::positionDestUnderSource (Ark* arc, int& x, int& y, int& best_x, int& best_y, int offset, boolean prefer_left, boolean place_the_node)
{
    boolean collided = FALSE;
    int input, output;
    int dx,dy, sx,sy;
    int xincr,yincr;
    Node* destination = arc->getDestinationNode(input);
    Node* source = arc->getSourceNode(output);
    NodeInfo* src_info = (NodeInfo*)source->getLayoutInformation();
    NodeInfo* dst_info = (NodeInfo*)destination->getLayoutInformation();
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
    while (!this->nodeCanMoveTo(destination, dx,dy)) {
	collided = TRUE;
	if (!place_the_node) break;
	dx+= xincr;
	dy+= yincr;
	if (this->collisions++ > TOO_MANY_COLLISIONS) break;
    }

    if (place_the_node) dst_info->setProposedLocation (dx,dy);
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
    NodeInfo* dest_info = (NodeInfo*)destination->getLayoutInformation();
    ASSERT (dest_info->isPositioned());
    ASSERT (destination == right_arc->getDestinationNode(right_input));
    Node* left_src = left_arc->getSourceNode(left_output);
    Node* right_src = right_arc->getSourceNode(right_output);
    StandIn* left_si = left_src->getStandIn();
    StandIn* right_si = right_src->getStandIn();
    StandIn* dest_si = destination->getStandIn();

    NodeInfo* right_info = (NodeInfo*)right_src->getLayoutInformation();
    NodeInfo* left_info = (NodeInfo*)left_src->getLayoutInformation();
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
    NodeInfo* dest_info = (NodeInfo*)destination->getLayoutInformation();
    ASSERT (dest_info->isPositioned());
    ASSERT (destination == right_arc->getDestinationNode(right_input));
    Node* left_src = left_arc->getSourceNode(left_output);
    Node* right_src = right_arc->getSourceNode(right_output);
    StandIn* left_si = left_src->getStandIn();
    StandIn* right_si = right_src->getStandIn();
    StandIn* dest_si = destination->getStandIn();

    NodeInfo* left_info = (NodeInfo*)left_src->getLayoutInformation();
    ASSERT (left_info->isPositioned());
    NodeInfo* right_info = (NodeInfo*)right_src->getLayoutInformation();

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
    NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
    int i;
    for (i=1; i<=input_count; i++) {
	if (!n->isInputVisible(i)) continue;
	List* arcs = (List*)n->getInputArks(i);
	ListIterator iter(*arcs);
	while (arc = (Ark*)iter.getNext()) {
	    Node* src = arc->getSourceNode(dummy);
	    NodeInfo* src_info = (NodeInfo*)src->getLayoutInformation();
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
    NodeInfo* linfo = (NodeInfo*)visit_parents_of->getLayoutInformation();
    int next_depth = current_depth - 1;

    linfo->setGraphDepth(current_depth);
    int input;
    for (input=1; input<=input_count; input++) {
	if (!visit_parents_of->isInputVisible(input)) continue;

	List* inputs = (List*)visit_parents_of->getInputArks(input);
	ListIterator iter(*inputs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    int output;
	    Node* source = arc->getSourceNode(output);
	    NodeInfo* sinfo = (NodeInfo*)source->getLayoutInformation();
	    if (next_depth < min)
		min = next_depth;
	    int cd;
	    if (!sinfo) {
		sinfo = new NodeInfo();
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
boolean GraphLayout::adjustHopCounts (Node* reflow[], int reflow_count, int& min)
{
    int i;
    boolean changes_made = FALSE;
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	if (this->hasConnectedOutputs(n)) continue;
	const char* cp = n->getLabelString();
	NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
	int required_hops = this->computeRequiredHopsTo(n);
	int sibling_hops = this->computeRequiredHopsToSiblingsOf (n);
	required_hops = MAX(required_hops, sibling_hops);
	if (required_hops < linfo->getGraphDepth()) {
	    int gd = required_hops;
	    this->adjustAncestorHops (n,gd-1,min);
	    linfo->setGraphDepth(gd);
	    if (gd < min)
		min = gd;
	    changes_made = TRUE;
	}
    }

    return changes_made;
}

void GraphLayout::adjustAncestorHops (Node* parent, int new_hop_count, int& min)
{
    int input_count = parent->getInputCount();
    int output;
    int input;
    for (input=1; input<=input_count; input++) {
	if (!parent->isInputVisible(input)) continue;
	List* arcs = (List*)parent->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(output);
	    NodeInfo* linfo = (NodeInfo*)source->getLayoutInformation();
	    if (new_hop_count < linfo->getGraphDepth()) {
		linfo->setGraphDepth(new_hop_count);
		if (new_hop_count < min) min = new_hop_count;
		this->adjustAncestorHops (source, new_hop_count-1, min);
	    }
	}
    }
}

int GraphLayout::computeRequiredHopsTo(Node* n)
{
    int output;
    int max_count = 1;
    int input_count = n->getInputCount();
    int input;
    for (input=1; input<=input_count; input++) {
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
    int input;
    for (input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* arcs = (List*)n->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(dummy);

	    int output_count = source->getOutputCount();
	    // for each output, fetch connected nodes.
	    int output;
	    for (output=1; output<=output_count; output++) {
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
    int i;
    //
    // The starting hop counter has no units.  After we finish, we'll
    // translate all hop counters so that the smallest one in the graph
    // is set to 1.
    //
    int smallest_hop_count=99999;
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	if (!this->hasConnectedOutputs(n)) {
	    NodeInfo* linfo = new NodeInfo();
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
    while (changes_made) changes_made = this->adjustHopCounts(reflow, reflow_count, smallest_hop_count);

    //
    // Before we raise the curtain, just one more tweak.  Sometimes
    // (usually at the top of a graph) we get some nodes that have a slew of
    // recievers providing inputs.  It's difficult to place all of these
    // in a pleasing way, so  we'll do a final check for this.  If the
    // situation exists, then we'll artificially decrement the hop count
    // for every other reciever so that the pattern is a little garbagey
    // looking.  
    //
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	this->fixForTooManyReceivers(n, smallest_hop_count);
    }

    //
    // Translate to the origin
    //
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
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
// row on Inputs in to place.  Otherwise - for non macro nets - we use a 
// smaller vertical separation.
//
void GraphLayout::computeSawToothPermission(Node* reflow[], int reflow_count)
{
    //
    // Search the graph for nodes that have 2 or more narrow nodes.  If any is
    // found then we'll have to spread things out vertically a little bit more.
    //
    int dummy;
    int w,h,i;
    this->permits_saw_tooth = FALSE;
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
	int input_count = n->getInputCount();
	int narrow_node_count = 0;
	int input;
	for (input=1; input<=input_count; input++) {
	    if (!n->isInputVisible(input)) continue;
	    List* arcs = (List*)n->getInputArks(input);
	    if (!arcs) continue;
	    ListIterator iter(*arcs);
	    Ark* arc;
	    while (arc = (Ark*)iter.getNext()) {
		Node* source = arc->getSourceNode(dummy);
		NodeInfo* info = (NodeInfo*)source->getLayoutInformation();
		if (info->getGraphDepth() != (linfo->getGraphDepth()-1)) continue;
		StandIn* si = source->getStandIn();
		si->getXYSize(&w,&h);
		if (w <= GraphLayout::NarrowStandIn)
		    narrow_node_count++;
	    }
	}
	if (narrow_node_count > 3) {
	    this->permits_saw_tooth = TRUE;
	    break;
	}
    }
    if (this->permits_saw_tooth)
	this->height_per_level = (2*GraphLayout::StandInHeight) + 12;
    else
	this->height_per_level = GraphLayout::HeightPerLevel;
} 

//
// If a node has wide recievers (a.k.a no input-1 output node)
// connected to adjacent input tabs then
// we'll decrement the hop count of 1 receiver so that things aren't
// bunched up too much.  In general this is bad because anything that
// increases arc length is likely to increase the wire crossings.
//
void GraphLayout::fixForTooManyReceivers(Node* n, int& min)
{
    boolean previous = FALSE;
    int dummy;
    int input;
    int input_count = n->getInputCount();
    List wide_nodes;
    for (input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* arcs = (List*)n->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(dummy);
	    LayoutInfo* linfo = (LayoutInfo*)source->getLayoutInformation();
	    int w,h;
	    linfo->getXYSize(w,h);
	    if (w >= GraphLayout::WideStandIn) {
		if (wide_nodes.isMember(source)==FALSE)
		    wide_nodes.insertElement(source,1);
	    }
	}
    }
    if (wide_nodes.getSize() <= 2) return ;
    for (input=1; input<=input_count; input++) {
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
	    NodeInfo* linfo = (NodeInfo*)source->getLayoutInformation();
	    int w,h;
	    linfo->getXYSize(w,h);
	    if (w >= GraphLayout::WideStandIn) {
		if (previous) {
		    int gd = linfo->getGraphDepth()-1;
		    linfo->setGraphDepth(gd);
		    if (gd < min) min = gd;
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
    int output;
    NodeInfo* src_info = (NodeInfo*)source->getLayoutInformation();
    NodeInfo* dst_info = (NodeInfo*)dest->getLayoutInformation();

    int min_depth = dst_info->getGraphDepth();
    int output_count = source->getOutputCount();
    for (output=1; output<=output_count; output++) {
	if (!source->isOutputVisible(output)) continue;
	List* arcs = (List*)source->getOutputArks(output);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* destination = arc->getDestinationNode(dummy);
	    if (destination == dest) continue;
	    NodeInfo* info = (NodeInfo*)destination->getLayoutInformation();
	    if (info->getGraphDepth() < min_depth) {
		// a closer relative was found
		return FALSE;
	    }
	}
    }

    return TRUE;
}

//
// This sucks.  I added this as a way of dealing with SuperviseWindow and
// SuperviseState.  This pair of nodes shares 3 arcs which makes the graph
// ugly.  I dislike it because it's not general enough to deal with other
// nets.  At the time I wrote the code, I didn't know how this pair of
// nodes ought to look and why.
//
Node* GraphLayout::hasPriorityAncestor (Node* destination, Ark** arcPtr, int at_least)
{
    int input, i;
    // won't be able to deal with nodes that more than 'max' connections.
    // hmmm, wonder how many inputs Image has?
    int max = 64;
    int counts[64];
    Node* ancestors[64];
    Ark* arcs[64];
    for (i=0; i<max; i++) {
	ancestors[i] = NUL(Node*);
	counts[i] = 0;
	arcs[i] = NUL(Ark*);
    }
    int input_count = destination->getInputCount();

    for (input=1; input<=input_count; input++) {
	if (!destination->isInputVisible(input)) continue;
	List* arcList = (List*)destination->getInputArks(input);
	if (!arcList) continue;
	ListIterator iter(*arcList);
	Ark* arc;
	int output;
	while (arc=(Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(output);
	    for (i=0; i<max; i++) {
		if (ancestors[i] == source) {
		    counts[i]++;
		    break;
		} else if (ancestors[i] == NUL(Node*)) {
		    ancestors[i] = source;
		    arcs[i] = arc;
		    counts[i] = 1;
		    break;
		}
	    }
	}
    }
    int max_count = 0;
    Node* max_node = NUL(Node*);
    Ark* max_arc;
    for (i=0; i<max; i++) {
	if (ancestors[i] == NUL(Node*)) break;
	if (counts[i] > max_count) {
	    max_node = ancestors[i];
	    max_count = counts[i];
	    max_arc = arcs[i];
	}
    }
    if (max_count >= at_least) {
	*arcPtr = max_arc;
	return max_node;
    }
    return NUL(Node*);
}

//
// Compute the location of the new placements relative to the old
// placements and adjust the new placements' locations so that the
// 2 bounding boxes don't intersect.
// If known_disjoint is TRUE, then that means we can move the new set
// anywhere we want it.  Otherwise we have to maintain any left-of
// right-of relationships.
//
void GraphLayout::repositionNewPlacements (Node* root, boolean disjoint, List& placed)
{
    Node* n;
    NodeInfo* ninfo = (NodeInfo*)root->getLayoutInformation();
    LayoutGroup* group = ninfo->getLayoutGroup();
    placed.appendElement(root);

    if (debug) {
	ListIterator li(placed);
	Node* node;
	fprintf (stdout, "%s[%d] placing in group %d...\n", 
		__FILE__,__LINE__, group->getId());
	while (node=(Node*)li.getNext()) {
	    fprintf (stdout, "\t%s\n", node->getLabelString());
	}
    }

    int minx2, miny2, maxx2, maxy2;
    this->computeBoundingBox (placed, minx2, miny2, maxx2,maxy2);

    boolean group_had_placements=TRUE;
    int minx1, miny1, maxx1, maxy1;
    List* connected = ninfo->getConnectedNodes(n);

    if (!disjoint) {
	// Form the bounding box of the starting condition 
	List original;
	Node* node;
	ListIterator iter(*connected);
	while (node = (Node*)iter.getNext()) {
	    LayoutInfo* info = (LayoutInfo*)node->getLayoutInformation();
	    if (info->isPositioned()) {
		if (!placed.isMember(node)) original.appendElement(node);
	    }
	}
	group_had_placements = 
	    this->computeBoundingBox (original, minx1, miny1, maxx1,maxy1);
    }

    int ydelta, xdelta;
    if ((disjoint) || (!group_had_placements)) {
	xdelta = -minx2;
	ydelta = -miny2;
	ListIterator iter(placed);
	while (n = (Node*)iter.getNext()) {
	    NodeInfo* info = (NodeInfo*)n->getLayoutInformation();
	    int x,y;
	    info->getXYPosition(x,y);
	    info->setProposedLocation(x+xdelta, y+ydelta);
	}
	group->initialize(&placed);
	return ;
    }

    ASSERT (group_had_placements);
    //
    // Now we have 2 bounding boxes, 1 for the nodes that were
    // already placed and 1 for the batch of additional placements.
    // We know we can scoot the new comers over so that the 2 bounding
    // boxes butt up against each other, but we might be able to do
    // better.  How to figure out how much we can scoot over without
    // having overlapping?  
    //
    // The goal is to scoot over far enough so that a wire that joins
    // 2 nodes - 1 in the new placments and 1 in the old placements -
    // becomes a straight line.
    //
    // Collect all the arcs that cross from 1 set to the other set.
    // Then sort those arcs by decreasing length.  Then for each 
    // arc, try to line things up without any collisions.  If none
    // works, then just butt the bounding boxes up against eachother.
    //
    List crossing_arcs;
    ListIterator iter(placed);
    while (n=(Node*)iter.getNext()) {
	int input_count = n->getInputCount();
	int output_count = n->getOutputCount();
	int input, output;
	for (input=1; input<=input_count; input++) {
	    if (!n->isInputVisible(input)) continue;
	    List* arks = (List*)n->getInputArks(input);
	    if (!arks) continue;
	    ListIterator li(*arks);
	    Ark* arc;
	    while (arc=(Ark*)li.getNext()) {
		Node* source = arc->getSourceNode(output);
		NodeInfo* sinfo = (NodeInfo*)source->getLayoutInformation();
		if (!sinfo->isPositioned()) continue;
		if (!placed.isMember(source)) {
		    if (crossing_arcs.isMember(arc) == FALSE)
			crossing_arcs.appendElement(arc);
		}
	    }
	}
	for (output=1; output<=output_count; output++) {
	    if (!n->isOutputVisible(output)) continue;
	    List* arks = (List*)n->getOutputArks(output);
	    if (!arks) continue;
	    ListIterator li(*arks);
	    Ark* arc;
	    while (arc=(Ark*)li.getNext()) {
		Node* dest = arc->getDestinationNode(input);
		NodeInfo* dinfo = (NodeInfo*)dest->getLayoutInformation();
		if (!dinfo->isPositioned()) continue;
		if (!placed.isMember(dest)) {
		    if (crossing_arcs.isMember(arc) == FALSE)
			crossing_arcs.appendElement(arc);
		}
	    }
	}
    }
    int maxarcs = 128;
    int arc_count = crossing_arcs.getSize();
    // this assert says that we should have detected a disconnected
    // subgraph in an earlier test.
    ASSERT(arc_count);
    arc_count = MIN(maxarcs, arc_count);
    Ark* aa[128];
    int i,j;
    for (i=0,j=1; i<arc_count; i++,j++) {
	aa[i] = (Ark*)crossing_arcs.getElement(j);
    }
    qsort (aa, arc_count, sizeof(Ark*), GraphLayout::ArcComparator);


    // for each arc, compute the x location that will make the wire
    // straight and test each node in placed to see if the entire
    // set can move.
    boolean arc_found = FALSE;
    for (i=0; i<arc_count; i++) {
	Ark* arc = aa[i];
	int input, output;
	Node* source = arc->getSourceNode(output);
	Node* dest = arc->getDestinationNode(input);
	NodeInfo* sinfo = (NodeInfo*)source->getLayoutInformation();
	NodeInfo* dinfo = (NodeInfo*)dest->getLayoutInformation();
	boolean node_can_move = FALSE;
	int prevx, prevy;

	int x,y,dummy;
	if (placed.isMember(source)) {
	    if (!this->positionSourceOverDest(arc, dummy,dummy,x,y,0,FALSE,FALSE,FALSE)) {
		// before going ahead with this placement, we should check to 
		// see if there's already an arc here that we would obstruct.
		node_can_move = TRUE;
		sinfo->getXYPosition (prevx, prevy);
		xdelta = x-prevx;
		ydelta = y-prevy;
	    }
	} else {
	    if (!this->positionDestUnderSource(arc, dummy,dummy,x,y,0,FALSE,FALSE)) {
		// before going ahead with this placement, we should check to 
		// see if there's already an arc here that we would obstruct.
		node_can_move = TRUE;
		dinfo->getXYPosition (prevx, prevy);
		xdelta = x-prevx;
		ydelta = y-prevy;
	    }
	}

	// now check all other nodes.
	if (node_can_move) {
	    arc_found = TRUE;
	    ListIterator iter(*connected);
	    Node* n;
	    while (n=(Node*)iter.getNext()) {
		NodeInfo* info = (NodeInfo*)n->getLayoutInformation();
		int nx,ny;
		info->getXYPosition(nx,ny);
		if (!this->nodeCanMoveTo (n, nx+xdelta, ny+ydelta)) {
		    arc_found = FALSE;
		    break;
		}
	    }
	}
    }

    // If no arc is found, then compute the xdelta so that the
    // two bounding boxes butt up against eachother.  The only
    // missing information is which bounding box should be on
    // the left and which on the right.  This is difficult to 
    // figure out.  Possible clues are the positioning of the
    // input and output tabs in use.  A high-numbered input
    // wants to be on the left of its source.  A low-numbered
    // output wants to be on the right of its destination.
    if (!arc_found) {
	boolean prefer_left;
	//
	// The choice of arc has an influence of the way we lay out the
	// graph especially when Gets and Sets are involved.  I don't
	// know of a 'proper' way to pick one arc. So, loop over all arcs
	// involved, give each 1 vote which it can cast in 1 of 3 ways...
	// go left, go right, don't care.
	//
	int center = 0;
	int j;
	if (debug)
	    fprintf (stdout, "%s[%d] %d arcs will vote on placement\n", 
		__FILE__,__LINE__,arc_count);
	for (j=0; j<arc_count; j++) {
	    prefer_left = FALSE;
	    Ark* arc = aa[j];

	    int input, output;
	    Node* src = arc->getSourceNode(output);
	    Node* dst = arc->getDestinationNode(input);
	    int nth_input_tab, nth_output_tab;
	    int vi = this->countConnectedInputs(dst, input, nth_input_tab);
	    // destination node casts his vote...
	    if ((vi==1)||((nth_input_tab==(vi>>1))&&((vi&1)==1))) {
		// don't care
		if (debug)
		    fprintf (stdout, "\t%s destination didn't vote\n",
			dst->getLabelString());
	    } else if (nth_input_tab<=(vi>>1)) {
		prefer_left = (placed.isMember(dst)==FALSE);
		center+= (prefer_left?-1:1);
		if (debug)
		    fprintf (stdout, "\t%s destination voted %s\n",
			dst->getLabelString(), (prefer_left?"LEFT":"RIGHT"));
	    } else if (nth_input_tab>(vi>>1)) {
		prefer_left = placed.isMember(dst);
		center+= (prefer_left?-1:1);
		if (debug)
		    fprintf (stdout, "\t%s destination voted %s\n",
			dst->getLabelString(), (prefer_left?"LEFT":"RIGHT"));
	    }

	    // source node casts his vote..
	    int vo = this->countConnectedOutputs(src, output, nth_output_tab);
	    if ((vo==1)||((nth_output_tab==(vo>>1))&&((vo&1)==1))) {
		//don't care
		if (debug)
		    fprintf (stdout, "\t%s source didn't vote\n",
			src->getLabelString());
	    } else if (nth_output_tab <= (vo>>1)) {
		prefer_left = (placed.isMember(src)==FALSE);
		center+= (prefer_left?-1:1);
		if (debug)
		    fprintf (stdout, "\t%s source voted %s\n",
			src->getLabelString(), (prefer_left?"LEFT":"RIGHT"));
	    } else if (nth_output_tab > (vo>>1)) {
		prefer_left = placed.isMember(src);
		center+= (prefer_left?-1:1);
		if (debug)
		    fprintf (stdout, "\t%s source voted %s\n",
			src->getLabelString(), (prefer_left?"LEFT":"RIGHT"));
	    }
	}
	prefer_left = (center<=0);

	if (prefer_left) {
	    xdelta = -(maxx2 + DESIRED_FUDGE - minx1);
	} else {
	    xdelta =  (maxx1  + DESIRED_FUDGE - minx2);
	}
	ydelta = 0;
    }

    //
    // perform the translation
    //
    iter.setList(placed);
    while (n=(Node*)iter.getNext()) {
	NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
	int x,y;
	ASSERT (linfo->isPositioned());
	linfo->getXYPosition(x,y);
	if (debug)
	    fprintf (stdout, "%s[%d] moving %s from %d,%d to %d,%d\n",
		    __FILE__,__LINE__,n->getLabelString(),x,y,x+xdelta,y+ydelta);
	linfo->setProposedLocation(x+xdelta, y+ydelta);
    }
    group->initialize(&placed);
}

void GraphLayout::prepareAnnotationPlacement(List& decorators, Node* reflow[], int reflow_count, const List& all_decorators, WorkSpace* workSpace, int& widest, int& tallest)
{
    //
    // exclude the nodes that aren't in the current page
    //
    ListIterator decs;
    VPEAnnotator* dec;
    decs.setList((List&)all_decorators);
    while (dec = (VPEAnnotator*)decs.getNext()) {
	if (dec->getWorkSpace() != workSpace) continue;
	decorators.appendElement(dec);
	AnnotationInfo* ai = new AnnotationInfo();
	ai->initialize(dec);
	ai->findNearestNode(reflow, reflow_count);

	int w,h;
	ai->getXYSize(w,h);
	NodeDistance* nd = ai->nearby[0];
	if (nd->getLocation() & DECORATOR_LEFT) {
	    if (w > widest) widest = w;
	}
	if (nd->getLocation() & DECORATOR_ABOVE) {
	    if (h > tallest) tallest = h;
	}
    }
}

AnnotationInfo::~AnnotationInfo()
{
    if (this->nearby) {
	int i;
	for (i=0; i<this->nearbyCnt; i++)
	    delete this->nearby[i];
	free(this->nearby);
    }
}
//
// Distance between 2 rectangles is the vertical distance between 2 horizontal
// line segments or horizontal distance between 2 vertical line segments
// if they overlap.  If the line segments don't overlap, then the distance
// is the smallest of the 4 distances between the the endpoints of the line
// segments.
//
void AnnotationInfo::findNearestNode(Node* reflow[], int reflow_count)
{
    int i;
    ASSERT (this->isInitialized());

    int x1 = this->orig_x;
    int x2 = this->orig_x + (this->w-1);
    int y1 = this->orig_y;
    int y2 = this->orig_y + (this->h-1);

    this->nearby = (NodeDistance**)malloc(sizeof(NodeDistance*) * reflow_count);;
    this->nearbyCnt = reflow_count;

    int min_dist = 999999;
    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	int nx1,ny1,nw,nh;
	linfo->getOriginalXYPosition(nx1,ny1);
	linfo->getXYSize(nw,nh);
	int nx2 = nx1+(nw-1);
	int ny2 = ny1+(nh-1);

	int vdist = 999999;
	int hdist = 999999;

	// vertical edges
	int hloc=0;
	if (x1 > nx2) {
	    hloc = DECORATOR_RIGHT;
	    if ((y1>=ny1) && (y1<=ny2)) {
		hdist = x1-nx2;
	    } else if ((y2>=ny1) && (y2<=ny2)) {
		hdist = x1-nx2;
	    } else if ((y1<=ny1) && (y2>=ny2)) {
		hdist = x1-nx2;
	    } else if (y1>ny2) {
		hdist = (int)sqrt((x1-nx2)*(x1-nx2) + (y1-ny2)*(y1-ny2));
		hloc|= DECORATOR_BELOW;
	    } else {
		hdist = (int)sqrt((x1-nx2)*(x1-nx2) + (y2-ny1)*(y2-ny1));
		hloc|= DECORATOR_ABOVE;
	    }
	} else if (x2 < nx1) {
	    hloc = DECORATOR_LEFT;
	    if ((y1>=ny1) && (y1<=ny2)) {
		hdist = nx1-x2;
	    } else if ((y2>=ny1) && (y2<=ny2)) {
		hdist = nx1-x2;
	    } else if ((y1<=ny1) && (y2>=ny2)) {
		hdist = nx1-x2;
	    } else if (y1>ny2) {
		hdist = (int)sqrt((x2-nx1)*(x2-nx1) + (y1-ny2)*(y1-ny2));
		hloc|= DECORATOR_BELOW;
	    } else {
		hdist = (int)sqrt((x2-nx1)*(x2-nx1) + (y2-ny1)*(y2-ny1));
		hloc|= DECORATOR_ABOVE;
	    }
	}

	// horizontal edges
	int vloc=0;
	if (y1 > ny2) {
	    vloc = DECORATOR_BELOW;
	    if ((x1>=nx1) && (x1<=nx2)) {
		vdist = y1-ny2;
	    } else if ((x2>=nx1) && (x2<=nx2)) {
		vdist = y1-ny2;
	    } else if ((x1<=nx1) && (x2>=nx2)) {
		vdist = y1-ny2;
	    } else if (x1 > nx2) {
		vdist = (int)sqrt((x1-nx2)*(x1-nx2) + (y1-ny2)*(y1-ny2));
		vloc|= DECORATOR_RIGHT;
	    } else {
		vdist = (int)sqrt((x2-nx1)*(x2-nx1) + (y1-ny2)*(y1-ny2));
		vloc|= DECORATOR_LEFT;
	    }
	} else if (y2 < ny1) {
	    vloc = DECORATOR_ABOVE;
	    if ((x1>=nx1) && (x1<=nx2)) {
		vdist = ny1-y2;
	    } else if ((x2>=nx1) && (x2<=nx2)) {
		vdist = ny1-y2;
	    } else if ((x1<=nx1) && (x2>=nx2)) {
		vdist = ny1-y2;
	    } else if (x1 > nx2) {
		vdist = (int)sqrt((x1-nx2)*(x1-nx2) + (y2-ny1)*(y2-ny1));
		vloc|= DECORATOR_RIGHT;
	    } else {
		vdist = (int)sqrt((x2-nx1)*(x2-nx1) + (y2-ny1)*(y2-ny1));
		vloc|= DECORATOR_LEFT;
	    }
	}

	if (hdist < vdist) this->nearby[i] = new NodeDistance (n, hdist, hloc);
	else this->nearby[i] = new NodeDistance (n, vdist, vloc);
    }
    qsort (this->nearby, this->nearbyCnt, sizeof(NodeDistance*), AnnotationInfo::Comparator);
}

int GraphLayout::ArcComparator(const void *a, const void* b)
{
    Ark** aptr = (Ark**)a;
    Ark** bptr = (Ark**)b;
    Ark* aarc = *aptr;
    Ark* barc = *bptr;

    int ahops,bhops;
    Node *src, *dst;
    int dummy;

    src = aarc->getSourceNode(dummy);
    dst = aarc->getDestinationNode(dummy);
    NodeInfo* sinfo = (NodeInfo*)src->getLayoutInformation();
    NodeInfo* dinfo = (NodeInfo*)dst->getLayoutInformation();
    ahops = dinfo->getGraphDepth() - sinfo->getGraphDepth();

    src = barc->getSourceNode(dummy);
    dst = barc->getDestinationNode(dummy);
    sinfo = (NodeInfo*)src->getLayoutInformation();
    dinfo = (NodeInfo*)dst->getLayoutInformation();
    bhops = dinfo->getGraphDepth() - sinfo->getGraphDepth();

    if (ahops < bhops) return -1;
    if (ahops > bhops) return -1;
    return 0;
}

int AnnotationInfo::Comparator(const void *a, const void* b)
{
    NodeDistance** aptr = (NodeDistance**)a;
    NodeDistance** bptr = (NodeDistance**)b;
    NodeDistance* aNd = (NodeDistance*)*aptr;
    NodeDistance* bNd = (NodeDistance*)*bptr;
    if (aNd->getDistance() < bNd->getDistance()) return -1;
    if (aNd->getDistance() > bNd->getDistance()) return  1;
    return 0;
}

int AnnotationInfo::NextX;
int AnnotationInfo::NextY;

void AnnotationInfo::reposition(Node* reflow[], int reflow_count, List& others)
{
    // spot sequence
    int spots[] = {
	DECORATOR_RIGHT,
	DECORATOR_RIGHT | DECORATOR_ABOVE,
	DECORATOR_RIGHT | DECORATOR_BELOW,
	DECORATOR_LEFT,
	DECORATOR_LEFT | DECORATOR_ABOVE,
	DECORATOR_LEFT | DECORATOR_BELOW,
	DECORATOR_ABOVE,
	DECORATOR_BELOW
    };
    int spot_cnt = sizeof(spots) / sizeof(int);

    boolean did_it = FALSE;

    int node_to_try = 0;
    while ((!did_it) && (node_to_try < this->nearbyCnt)) {

	NodeDistance* nd = this->nearby[node_to_try];
	Node* n = nd->getNode();
	const char* cp = n->getLabelString();
	int loc = nd->getLocation();
	LayoutInfo* linfo = (LayoutInfo*)n->getLayoutInformation();
	int nodex, nodey;
	int nodew, nodeh;
	linfo->getXYPosition(nodex,nodey);
	linfo->getXYSize(nodew,nodeh);

	int spot_index = 0;
	while (spots[spot_index] != loc) spot_index++;

	int tries = 0;
	while (tries < spot_cnt) {
	    int location = spots[spot_index];
	    int x = nodex + ((nodew-this->w)/2);
	    int y = nodey + ((nodeh-this->h)/2);
	    if (location & DECORATOR_ABOVE) {
		y = nodey - (1+this->h);
	    } else if (location & DECORATOR_BELOW) {
		y = nodey + nodeh + 1;
	    }
	    if (location & DECORATOR_LEFT) {
		x = nodex - (1+this->w);
	    } else if (location & DECORATOR_RIGHT) {
		x = nodex + 1 + nodew;
	    }

	    if ((x>0) && (y>0) && 
		    (GraphLayout::CanMoveTo(this, x, y, reflow, reflow_count, &others))) {
		this->setProposedLocation (x, y);
		did_it = TRUE;
		break;
	    } 
	    tries++;
	    spot_index++;
	    if (spot_index==spot_cnt) spot_index = 0;
	}
	node_to_try++;
    }

    if (!did_it) {
	this->setProposedLocation (AnnotationInfo::NextX, AnnotationInfo::NextY);
	AnnotationInfo::NextY+= this->h+1;
    }
}

void LayoutGroup::initialize(List* nodes)
{
    ListIterator iter(*nodes);
    Node* n;
    while (n = (Node*)iter.getNext()) {
	NodeInfo* linfo = (NodeInfo*)n->getLayoutInformation();
	int x,y,w,h;
	linfo->getOriginalXYPosition(x,y);
	linfo->getXYSize(w,h);
	if (x < this->orig_x1) this->orig_x1 = x;
	if (y < this->orig_y1) this->orig_y1 = y;
	if ((x+w) > this->orig_x2) this->orig_x2 = x+w;
	if ((y+h) > this->orig_y2) this->orig_y2 = y+h;
	linfo->getXYPosition(x,y);
	if (x < this->x1) this->x1 = x;
	if (y < this->y1) this->y1 = y;
	if ((x+w) > this->x2) this->x2 = x+w;
	if ((y+h) > this->y2) this->y2 = y+h;
	linfo->setLayoutGroup(this);
    }
    this->initialized = TRUE;
}

int LayoutGroup::Comparator (const void* a, const void* b)
{
    LayoutGroup** aptr = (LayoutGroup**)a;
    LayoutGroup** bptr = (LayoutGroup**)b;
    LayoutGroup* agroup = *aptr;
    LayoutGroup* bgroup = *bptr;

    //
    // If  the height ranges don't overlap then return the one with
    // the lower y.
    //
    if ((agroup->orig_y1 < bgroup->orig_y1) && (agroup->orig_y2 < bgroup->orig_y2))
	return -1;
    if ((bgroup->orig_y1 < agroup->orig_y1) && (bgroup->orig_y2 < agroup->orig_y2))
	return 1;
    
    //
    // If the height ranges overlap, then return the one with the
    // large x.
    //
    if ((agroup->orig_x1 < bgroup->orig_x1) && (agroup->orig_x2 < bgroup->orig_x2))
	return -1;
    if ((bgroup->orig_x1 < agroup->orig_x1) && (bgroup->orig_x2 < agroup->orig_x2))
	return 1;

    if (((agroup->orig_y1 + agroup->orig_y2)>>1) < 
	((bgroup->orig_y1 + bgroup->orig_y2)>>1))  
	return -1;
    if (((agroup->orig_y1 + agroup->orig_y2)>>1) >
	((bgroup->orig_y1 + bgroup->orig_y2)>>1))  
	return 1;
    if (((agroup->orig_x1 + agroup->orig_x2)>>1) < 
	((bgroup->orig_x1 + bgroup->orig_x2)>>1))  
	return -1;
    if (((agroup->orig_x1 + agroup->orig_x2)>>1) >
	((bgroup->orig_x1 + bgroup->orig_x2)>>1))  
	return 1;
    return 0;
}

void GraphLayout::repositionGroups(Node* reflow[], int reflow_count)
{
    int i;
    LayoutGroup** groups = (LayoutGroup**)malloc(sizeof(LayoutGroup*) * 
	    this->layout_groups.getSize());
    ListIterator gi(this->layout_groups);
    LayoutGroup* group;
    int gcnt = 0;
    while  (group = (LayoutGroup*)gi.getNext()) groups[gcnt++] = group;
    qsort (groups, gcnt, sizeof(LayoutGroup*), LayoutGroup::Comparator);
    int gx=0,gy=0;
    int prevy2 = 0;
    int dummy;
    int w=0,h=0;
    int max_height_in_line = 0;

    groups[0]->getOriginalXYPosition(dummy, prevy2);
    groups[0]->getOriginalXYSize(dummy, h);
    prevy2+= h;

    w=h=0;
    boolean isNewLine = FALSE;
    for (i=0; i<gcnt; i++) {
	group = groups[i];
	int x1,y1;
	int ow,oh;
	group->getOriginalXYPosition(x1,y1);
	group->getOriginalXYSize(ow,oh);
	int w,h;
	group->getXYSize(w,h);
	isNewLine = (y1 > prevy2);
	if (isNewLine) {
	    gx = 0;
	    gy+=max_height_in_line + this->height_per_level;
	    max_height_in_line = h;
	} else if (h>max_height_in_line) {
	    max_height_in_line = h;
	}
	group->setProposedLocation(gx,gy);
	//printf ("%s[%d] group %d at %d,%d\n", __FILE__,__LINE__,group->getId(), gx, gy);
	gx+= w + HORIZONTAL_GROUP_SPACING;
	prevy2 = y1+oh;
    }

    for (i=0; i<reflow_count; i++) {
	Node* n = reflow[i];
	const char* cp = n->getLabelString();
	NodeInfo* ninfo = (NodeInfo*)n->getLayoutInformation();
	LayoutGroup* group = ninfo->getLayoutGroup();
	int x,y;
	group->getProposedLocation (x,y);
	int x1,y1;
	group->getXYPosition (x1,y1);
	int nx,ny;
	ninfo->getXYPosition (nx, ny);
	ninfo->setProposedLocation (nx+x-x1, ny+y-y1);
    }
}

NodeInfo::~NodeInfo() 
{
    if (this->connected_nodes) {
	if (this->owns_list)
	    delete this->connected_nodes;
    }
}

void NodeInfo::setConnectedNodes(List* list)
{
    if (this->owns_list) return ;
    this->connected_nodes = list;
}
List* NodeInfo::getConnectedNodes(Node* n)
{
    if (this->connected_nodes) return this->connected_nodes;

    this->connected_nodes = new List();
    this->owns_list = TRUE;
    NodeInfo::BuildList (n, this->connected_nodes);
    return this->connected_nodes;
}

void NodeInfo::BuildList(Node* n, List* nodes)
{
    if (nodes->isMember(n)) return ;
    nodes->appendElement(n);

    NodeInfo* info = (NodeInfo*)n->getLayoutInformation();
    if (info) info->setConnectedNodes(nodes);

    int input_count = n->getInputCount();
    int input;
    int dummy;
    for (input=1; input<=input_count; input++) {
	if (!n->isInputVisible(input)) continue;
	List* arcs = (List*)n->getInputArks(input);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* source = arc->getSourceNode(dummy);
	    NodeInfo::BuildList(source, nodes);
	}
    }
    int output_count = n->getOutputCount();
    int output;
    for (output=1; output<=output_count; output++) {
	if (!n->isOutputVisible(output)) continue;
	List* arcs = (List*)n->getOutputArks(output);
	if (!arcs) continue;
	ListIterator iter(*arcs);
	Ark* arc;
	while (arc = (Ark*)iter.getNext()) {
	    Node* destination = arc->getDestinationNode(dummy);
	    NodeInfo::BuildList(destination, nodes);
	}
    }
}

int GraphLayout::countConnectedInputs(Node* n, int input, int& nth_tab)
{
    int input_count = n->getInputCount();
    int i, connected=0;
    nth_tab = 1;
    for (i=1; i<=input_count; i++) {
	if (!n->isInputVisible(i)) continue;
	if (n->isInputConnected(i)) connected++;
	if (i<input) nth_tab++;
    }
    return connected;
}

int GraphLayout::countConnectedOutputs (Node* n, int output, int& nth_tab)
{
    int output_count = n->getOutputCount();
    int i, connected=0;
    nth_tab = 1;
    for (i=1; i<=output_count; i++) {
	if (!n->isOutputVisible(i)) continue;
	if (n->isOutputConnected(i)) connected++;
	if (i<output) nth_tab++;
    }
    return connected;
}
