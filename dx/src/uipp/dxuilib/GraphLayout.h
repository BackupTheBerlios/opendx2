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
#include "List.h"

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
class LayoutGroup;
class UIComponent;
class VPEAnnotator;
class NodeDistance;

//
// Class name definition:
//
#define ClassGraphLayout "GraphLayout"

#if ONLY_IN_GRAPH_LAYOUT_CODE
//
// There are several classes defined in this include file that ought
// to be invisible to all classes other than GraphLayout.
//
#define ClassLayoutInfo "LayoutInfo"

//
// Store as a sort of extension record in Node.  
//
class LayoutInfo : public Base {
    private:
	boolean initialized;

    protected:
	friend class GraphLayout;
	// proposed new location
	int x,y;

	// the original location is used to attempt to place
	// disconnected subgraphs relative to eachother the same
	// way as in the original layout.
	int orig_x, orig_y;

	// are the values in x,y set?
	boolean positioned_yet;

	// was the position of the node adjusted (in some
	// screwy way) because of a collision with another node.
	boolean collision;

	// fetched width and height stored redundantly but
	// avoids using XtGetValues over and over.
	int w,h;

	LayoutInfo () {
	    this->x = this->y = this->w = this->h = -1;
	    this->positioned_yet = FALSE;
	    this->collision = FALSE;
	    this->initialized = FALSE;
	}

	void initialize (UIComponent* uic);

	virtual boolean isInitialized() { return this->initialized; }

    public:
	virtual ~LayoutInfo(){}
	void getOriginalXYPosition (int& x, int& y) {
	    x = this->orig_x;
	    y = this->orig_y;
	}
	void getXYPosition (int& x, int& y) {
	    x = this->x;
	    y = this->y;
	}
	void getXYSize (int& w, int& h) {
	    w = this->w;
	    h = this->h;
	}
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
	virtual const char* getClassName()
	{
	    return ClassLayoutInfo;
	}
};

#define ClassNodeInfo "NodeInfo"
class NodeInfo : public LayoutInfo
{
    protected:
	friend class GraphLayout;
	int hops;

	LayoutGroup* group;

	List* connected_nodes;
	boolean owns_list;

	NodeInfo () {
	    this->hops = 0;
	    this->group = NUL(LayoutGroup*);
	    this->connected_nodes = NUL(List*);
	    this->owns_list = FALSE;
	}
	void initialize (Node* n, int hops);

	void setGraphDepth(int d) { this->hops = d; }

	// for qsort
	static int Comparator (const void* a, const void* b);

    public:
	int getGraphDepth() { return this->hops; }

	void setLayoutGroup(LayoutGroup* group) { this->group = group; }
	LayoutGroup* getLayoutGroup() { return this->group; }

	virtual ~NodeInfo();

	List* getConnectedNodes(Node* n);

	static void BuildList(Node* n, List* nodes);

	void setConnectedNodes(List* nodes);

	virtual const char* getClassName()
	{
	    return ClassNodeInfo;
	}
};

#define ClassAnnotationInfo "AnnotationInfo"
class AnnotationInfo: public LayoutInfo
{
    private:
	friend class GraphLayout;

    protected:
	AnnotationInfo() {
	    this->nearby = 0;
	    this->nearbyCnt = 0;
	}

	void initialize (VPEAnnotator* dec);

	NodeDistance** nearby;
	int nearbyCnt;

	static int Comparator(const void* a, const void* b);

	static int NextX;
	static int NextY;

    public:

	virtual ~AnnotationInfo();

	void findNearestNode(Node* reflow[], int reflow_count);

	void reposition(Node* reflow[], int reflow_count, List& other_decorators);

	//
	// Returns a pointer to the class name.
	//
	virtual const char* getClassName()
	{
	    return ClassAnnotationInfo;
	}
};

class NodeDistance
{
    private:
	Node* node;
	int distance;
	int location;
    protected:
    public:
	NodeDistance (Node* n, int distance, int location) {
	    this->node = n;
	    this->distance = distance;
	    this->location = location;
	}
	Node* getNode() { return this->node; }
	int getDistance() { return this->distance; }
	int getLocation() { return this->location; }
};

#define ClassLayoutGroup "LayoutGroup"
class LayoutGroup : public Base
{
    private:
	boolean initialized;
	int id;
    protected:
	int orig_x1,orig_y1,orig_x2,orig_y2;
	int x1,y1,x2,y2;
	int x,y;
	static int Comparator(const void* a, const void* b);
	friend class GraphLayout;
    public:
	LayoutGroup(int id) {
	    this->initialized = FALSE;
	    this->x1 = this->orig_x1 = 999999;
	    this->y1 = this->orig_y1 = 999999;
	    this->x2 = this->orig_x2 = -999999;
	    this->y2 = this->orig_y2 = -999999;
	    this->id = id;
	}
	virtual ~LayoutGroup(){}
	void initialize (List* nodes);
	void getOriginalXYPosition(int& x, int& y) {
	    x = this->orig_x1;
	    y = this->orig_y1;
	}
	void getXYSize(int& w, int& h) {
	    w = this->x2 - this->x1;
	    h = this->y2 - this->y1;
	}
	void getOriginalXYSize(int& w, int& h) {
	    w = this->orig_x2 - this->orig_x1;
	    h = this->orig_y2 - this->orig_y1;
	}
	void getXYPosition(int& x, int& y) {
	    x = this->x1;
	    y = this->y1;
	}
	int getId() { return this->id; }
	void setProposedLocation (int x, int y) {
	    this->x = x;
	    this->y = y;
	}
	void getProposedLocation (int& x, int& y) {
	    x = this->x;
	    y = this->y;
	}
	virtual const char* getClassName()
	{
	    return ClassLayoutGroup;
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

    boolean adjustHopCounts (Node* reflow[], int reflow_count, int& min);
    void adjustAncestorHops (Node* parent, int new_hop_count, int& min);
    int computeRequiredHopsTo (Node* n);
    int computeRequiredHopsToSiblingsOf (Node* n);
    void fixForTooManyReceivers(Node* n, int& min);

    //
    // Return TRUE if the node's standin can move to x,y without
    // causing overlap with any other node in the list.
    //
    boolean nodeCanMoveTo (Node* n, int x, int y); 

    //
    // return TRUE if the positioning was accomplished without collision
    //
    boolean positionSourceOverDest(Ark* arc, int& x, int& y, 
	    int& best_x, int& best_y,
	    int offset=0, 
	    boolean saw_tooth=FALSE, boolean prefer_left=FALSE,
	    boolean place_the_node=TRUE);

    //
    // return TRUE if the positioning was accomplished without collision
    //
    boolean positionDestUnderSource(Ark* arc, int& x, int& y, 
	    int& best_x, int& best_y,
	    int offset=0, 
	    boolean prefer_left=FALSE,
	    boolean place_the_node=TRUE);

    void repositionGroups(Node* reflow[], int reflow_count);

  protected:
    //
    // Protected member data:
    //

    static int StandInHeight;
    static int HeightPerLevel;
    static int NarrowStandIn;
    static int WideStandIn;

    static int ArcComparator(const void* a, const void* b);

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

    void doPlacements(Node* n, LayoutInfo* linfo, Node* reflow[], int reflow_count, List& positioned);

    boolean hasNoCloserDescendant (Node* source, Node* dest);

    //
    // An additional pass over the nodes to make whatever minor mods
    // might beautify the result.
    //
    void postProcessing(Node* reflow[], int reflow_count);

    boolean computeBoundingBox (List& nodes, int& minx, int& miny, int& maxx, int& maxy);
    boolean computeBoundingBox (Node* nodes[], int count, int& minx, int& miny, 
	    int& maxx, int& maxy, List* decorators=NUL(List*));

    void repositionDecorators (List& decorators, boolean same_event_flag, Node* reflow[], int reflow_count);

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

    //
    // 
    void prepareAnnotationPlacement(List& decorators, Node* reflow[], int reflow_count, 
	    const List& all_decorators, WorkSpace* workSpace, int& widest, int& tallest);

    List layout_groups;

    //
    // Count the connected tabs and return the number of the specified
    // tab in the ordering of the visible tabs.  i.e. The 20th input
    // of Image might be the 2nd input tab.
    //
    int countConnectedInputs (Node* n, int input, int& nth_tab);
    int countConnectedOutputs (Node* n, int output, int& nth_tab);

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

    static boolean CanMoveTo (LayoutInfo* info, int x, int y, Node* reflow[], 
	int count, List* decorators); 

    static Ark* IsSingleInputNoOutputNode(Node* n, boolean *shares_an_output, boolean positioned=TRUE);
    static boolean IsSingleOutputNoInputNode(Node* n);

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
    // Check for 3 or more connections between a pair of nodes 
    // 
    Node* hasPriorityAncestor(Node* destination, Ark** priority_arc, int at_least);

    void repositionNewPlacements (Node* , boolean , List&);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassGraphLayout;
    }
};


#endif // _GraphLayout_h
