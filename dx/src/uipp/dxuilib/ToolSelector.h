/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _ToolSelector_h
#define _ToolSelector_h

#include "Base.h"
#include "ActiveItemDictionary.h"
#include "Application.h"
#include "UIComponent.h"

#include "TreeView.h"
#include "TreeNode.h"

#define EXPANDED_CATEGORIES "expandedCategories"

//
// Class name definition:
//
class TreeNode;
class ToolView;
class TreeView;
class CategoryNode;
class ToolNode;

//
// Class name definition:
//
#define ClassToolSelector	"ToolSelector"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void ToolSelector_ToolHelpCB(Widget, XtPointer, XtPointer);
extern "C" void ToolSelector_ToolSelectCB(Widget, XtPointer, XtPointer);
extern "C" void ToolSelector_CategorySelectCB(Widget, XtPointer, XtPointer);


class NodeDefinition;

//
// ToolSelector class definition:
//				
class ToolSelector : public UIComponent 
{

  private:
    //
    // Private member data:
    //
    ActiveItemDictionary 	categoryDictionary;
    Dictionary			categoryNodeDictionary;

    TreeNode* treeModel;
    TreeView* treeView;

    const void			*activeData;
    boolean			lockedData;
    boolean			toolListDirty;
    int				lastToolIndex;

    static boolean ToolSelectorClassInitialized;

    static String DefaultResources[]; 

    friend class ToolView;
    friend void ToolSelector_ToolHelpCB(Widget, XtPointer, XtPointer);

    // List of all tool selectors.
    static List AllToolSelectors;
  
    void buildTreeModel();

    class ToolCategoryNode : public CategoryNode {
	private:
	protected:
	    ToolSelector* toolSelector;
	    ToolCategoryNode(Symbol s, TreeNode* parent, ToolSelector* ts) : 
		CategoryNode(s, parent) { 
		    this->toolSelector = ts;
	    }
	    friend class ToolSelector;
	public:
	    void setExpanded(boolean e=TRUE);
    };
    class ToolNode : public LeafNode {
	private:
	protected:
	    ToolSelector* toolSelector;
	    ToolNode(Symbol s, TreeNode* cat, ToolSelector* ts) : LeafNode(s, cat) { 
		this->toolSelector = ts;
	    }
	    friend class ToolSelector;
	public:
	    CategoryNode* getCategory() { return (CategoryNode*)this->getParent(); }
    };

    class ToolView : public TreeView {
	private:
	    ToolSelector* toolSelector;
	protected:
	    void select(TreeNode* node, boolean repaint=TRUE);
	    void multiClick(TreeNode* node);
	    friend class ToolSelector;
	    void adjustVisibility(int, int, int, int);
	    void getSearchableNodes (List& nodes_to_search);
	    ToolView (Widget parent, ToolSelector* t) : TreeView(parent) {
		this->toolSelector = t;
	    }
    };

  protected:

    //
    // One time initialize for the class. 
    // 
    void initialize();

    //
    // Build the category lists and add the list items to the widgets.
    // from a dictionary of NodeDefinitions.
    //
    virtual Widget layoutWidgets(Widget parent);

    //
    //  Add tools in the given dictionary to the category/tool lists.
    //
    boolean augmentLists(Dictionary *d);

    //
    // Add the Node named 'tool' that is in category 'cat' and defined by 'nd'
    // to the table of category/tool pairings.
    // The widgets are not updated.
    //
    boolean addTool(Symbol cat, Symbol tool, void *ptr);
    boolean removeTool(Symbol cat, Symbol tool);

    //
    // Build a new Category list and install it in the categoryList.
    //
    boolean updateCategoryListWidget();

    virtual void toolSelect(Symbol s);
    virtual void lockSelect(Symbol s);
    virtual void categorySelect(Symbol s);

    CategoryNode* getCategoryNode (TreeNode* node, Symbol cat);
    TreeNode* getToolNode (TreeNode* node, Symbol tool);

    virtual void adjustVisibility(int, int, int, int){}

    virtual void help();

  public:
    //
    // Constructor:
    //
    ToolSelector(const char *name);

    //
    // Destructor:
    //
    ~ToolSelector();

    //
    // Drag-n-Drop support.  Dnd requires some ability to change/access the selected
    // item in the toolList Widget.
    //
    NodeDefinition* definitionOf (const char *category, const char *tool);

    //
    // These perform addTool and removeTool to all tool selectors.
    //
    static boolean AddTool(Symbol cat, Symbol tool, void *ptr);
    static boolean RemoveTool(Symbol cat, Symbol tool);

    static boolean UpdateCategoryListWidget();

    //
    // Merge new tools definitions into all tool selectors from a dictionary 
    // of NodeDefinitions.
    //
    static boolean MergeNewTools(Dictionary *d);

    //
    // Get the current Selection. 
    // 
    NodeDefinition *getCurrentSelection() {return (NodeDefinition*)activeData;}

    boolean  isSelectionLocked()	{ return this->lockedData; }

    //
    // Build two list widgets and initialize the lists from the items in
    // the dictionary.
    //
    virtual boolean initialize(Widget parent, Dictionary *d);

    //
    // Unhighlight any selected tools in the tool list. 
    //
    virtual void deselectAllTools();

    //
    // is the object in the anchor window. At this level we know nothing
    // of windows.  EditorToolSelector has this knowledge.
    //
    virtual boolean inAnchor(){ return TRUE; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassToolSelector;
    }
};


#endif // _ToolSelector_h
