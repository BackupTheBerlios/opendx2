/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _GraphLayout_h
#define _GraphLayout_h
#include "../base/defines.h"


#include "Base.h"

//
// referenced classes
//
class EditorWindow;
class WorkSpace;
class Node;
class List;
class Ark;
class LayoutInfo;


//
// Class name definition:
//
#define ClassGraphLayout "GraphLayout"

#if ONLY_IN_GRAPH_LAYOUT_CODE
//
// No class outside of GraphLayout needs to know anything
// about LayoutInfo
//
#define ClassLayoutInfo "LayoutInfo"

//
// Store as a sort of extension record in Node.  
//
class LayoutInfo : public Base {
    protected:
	friend class GraphLayout;
	// proposed new location
	int x,y;

	// for qsort
	static int Comparator (const void* a, const void* b);

	// are the values in x,y set?
	boolean positioned_yet;

	// was the position of the node adjusted (in some
	// screwy way) because of a collision with another node.
	boolean collision;

	// fetched width and height stored redundantly but
	// avoids using XtGetValues over and over.
	int w,h;

	int hops;

	LayoutInfo () {
	    this->hops = 0;
	    this->x = this->y = this->w = this->h = -1;
	    this->positioned_yet = FALSE;
	    this->collision = FALSE;
	}
	void initialize (Node* n, int hops);

	void setGraphDepth(int d) { this->hops = d; }

    public:
	virtual ~LayoutInfo(){}
	void getXYPosition (int& x, int& y) {
	    x = this->x;
	    y = this->y;
	}
	void getXYSize (int& w, int& h) {
	    w = this->w;
	    h = this->h;
	}
	int getGraphDepth() { return this->hops; }
	boolean isPositioned() { return this->positioned_yet; }
	void reposition() { this->collision = this->positioned_yet = FALSE; }
	void setProposedLocation(int x, int y) {
	    this->x = x;
	    this->y = y;
	    this->positioned_yet = TRUE;
	}

	void setCollided(boolean c=TRUE) { this->collision = c; }
	boolean collided() { return this->collision; }

	//
	// Returns a pointer to the class name.
	//
	const char* getClassName()
	{
	    return ClassLayoutInfo;
	}
};
#endif

//
// GraphLayout class definition:
//				
class GraphLayout : public Base
{
  private:
    //
    // Private member data:
    //
    EditorWindow* editor;

    //
    // Bail out of node placement if we get too many overlaps
    //
    int collisions;

    boolean adjustHopCounts (Node* reflow[], int reflow_count);
    void adjustAncestorHops (Node* parent, int new_hop_count);
    int computeRequiredHopsTo (Node* n);
    int computeRequiredHopsToSiblingsOf (Node* n);
    void fixForTooManyReceivers(Node* n);

    //
    // Return TRUE if the node's standin can move to x,y without
    // causing overlap with any other node in the list.
    //
    boolean nodeCanMoveTo (Node* n, int x, int y, Node* reflow[], int count);

    //
    // return TRUE if the positioning was accomplished without collision
    //
    boolean positionSourceOverDest(Ark* arc, int& x, int& y, 
	    int& best_x, int& best_y,
	    Node* reflow[], int reflow_count, int offset=0, 
	    boolean saw_tooth=FALSE, boolean prefer_left=FALSE);

    //
    // return TRUE if the positioning was accomplished without collision
    //
    boolean positionDestUnderSource(Ark* arc, int& x, int& y, 
	    int& best_x, int& best_y,
	    Node* reflow[], int reflow_count, int offset=0, 
	    boolean prefer_left=FALSE);

  protected:
    //
    // Protected member data:
    //

    static int StandInHeight;
    static int HeightPerLevel;
    static int NarrowStandIn;
    static int WideStandIn;

    //
    // There are 2 different values for height per level.  The static version
    // works in any case especially the case in which we want to put Input
    // tools into a comb pattern.  We'll check the graph for the presence of
    // tools that have 2 or more narrow nodes.  If none is found, then
    // we can use a smaller value for height per level and compress the
    // graph vertically.
    //
    int height_per_level;

    boolean permits_saw_tooth;

    void computeSawToothPermission(Node* reflow[], int reflow_count);

    void bottomUpTraversal (Node* visit_kids_of, int current_depth, int& min);

    boolean hasConnectedInputs(Node* n);
    boolean hasConnectedOutputs(Node* n, Node* other_than=NUL(Node*));
    void unmarkAllNodes(Node* reflow[], int reflow_count);

    void doPlacements(Node* n, LayoutInfo* linfo, Node* reflow[], int reflow_count);

    boolean hasNoCloserDescendant (Node* source, Node* dest);

    //
    // An additional pass over the nodes to make whatever minor mods
    // might beautify the result.
    //
    void postProcessing(Node* reflow[], int reflow_count);

    //
    // Find ancestors of n that have already been positioned.  Each
    // Node put into the ancestor list is the first encountered on
    // the traversal, in other words, don't traverse beyond a positioned
    // ancestor. 
    //
    void collectPositionedAncestorsOf (Node* n, List& ancestors);

    //
    // Make a list of all nodes that have been positioned.
    //
    void collectPositioned(Node* reflow[], int reflow_count, List& positioned);

    void computeBoundingBox (List& nodes, int& minx, int& miny, int& maxx, int& maxy);
    void computeBoundingBox (Node* nodes[], int count, int& minx, int& miny, int& maxx, int& maxy);

    void repositionDecorators (List& decorators, WorkSpace* workSpace, int minx, int miny, int maxx, int maxy, boolean same_event_flag);

    Ark* isSingleInputNoOutputNode(Node* n, boolean *shares_an_output);
    boolean isSingleOutputNoInputNode(Node* n);

    //
    // Does the work of countAncestorsWithinHops avoiding double countting.
    //
    void listAncestorsWithinHops (Node* n, int hops, List& ancestors);

    //
    // TRUE if the StandIn width is small enough so that the nodes can be
    // positioned in a saw tooth pattern with straight arcs.  An Input tool
    // is an example of a narrow node.
    //
    boolean isNarrow(Node* n);

    void computeHopCounts (Node* reflow[], int reflow_count);

  public:
    //
    // Constructor:
    //
    GraphLayout(EditorWindow *editor) {
       this->editor = editor;
       this->collisions = 0;
    }

    boolean entireGraph(WorkSpace* workspace, const List& nodes, const List& decorators);

    boolean arcStraightener(WorkSpace* workspace, const List& nodeList);

    //
    // Destructor:
    //
    ~GraphLayout() { }

    //
    // Assuming the nodes for right_arc have been positioned
    // already, we want to compute how much we have to offset
    // the source node for the left arc so that we can place the
    // left node as near as we can to having a straight arc but
    // subject to the constraint that its placment can't obstruct
    // the right_arc.  The return value will probably be < 0.
    //
    int computeLeftOffset(Ark* left_arc, Ark* right_arc);

    //
    // Assuming the nodes for left_arc have been positioned
    // already, we want to compute how much we have to offset
    // the source node for the right arc so that we can place the
    // right node as near as we can to having a straight arc but
    // subject to the constraint that its placment can't obstruct
    // the left_arc.  The return value will probably be > 0.
    //
    int computeRightOffset(Ark* left_arc, Ark* right_arc);

    //
    // Count the kids within the specified number of hops.  The purpose
    // is to measure how crowded the graph is.  When the graph is crowded
    // we'll spread nodes out more so that ancestors don't crash into 
    // one another
    //
    int countAncestorsWithinHops (Node* n, int hops);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassGraphLayout;
    }
};


#endif // _GraphLayout_h
