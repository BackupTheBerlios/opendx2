/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "../base/defines.h"





#ifndef _ToolSelector_h
#define _ToolSelector_h


#include "Base.h"
#include "ActiveItemDictionary.h"
#include "Application.h"
#include "UIComponent.h"
#include "DropSite.h"
#include "DragSource.h"


//
// Class name definition:
//


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
class ToolSelector : public UIComponent , public DropSite, public DragSource
{
  friend class FindToolSelector;

  private:
    //
    // Private member data:
    //
    ActiveItemDictionary 	categoryDictionary;

    Widget			categoryList;	// List of categories

    Widget			toolListLabel;	// Label for tools.
    Widget			toolList;	// List of tools.

    const void			*activeData;
    boolean			lockedData;
    boolean			toolListDirty;
    int				lastToolIndex;

    static boolean ToolSelector::ToolSelectorClassInitialized;

    static String ToolSelector::DefaultResources[]; 

    //
    // Static member callback for the category selection list.
    //
    friend void ToolSelector_CategorySelectCB(Widget w, 
				XtPointer clientData, XtPointer callData);
    //
    // Static member callback for tool selection list.
    //
    friend void ToolSelector_ToolSelectCB(Widget w, 
				XtPointer clientData, XtPointer callData);
    friend void ToolSelector_ToolHelpCB(Widget w, 
				XtPointer clientData, XtPointer callData);

    // List of all tool selectors.
    static List AllToolSelectors;
  
    //
    // data type dictionary for drops.
    //
    static Dictionary *DropTypeDictionary;
    static Dictionary *DragTypeDictionary;

    //
    // Supply the type dictionary which stores the types we can supply for a dnd
    //
    virtual Dictionary *getDropDictionary() { return ToolSelector::DropTypeDictionary; }
    virtual Dictionary *getDragDictionary() { return ToolSelector::DragTypeDictionary; }

    static char* DragTranslations;
    static XtTranslations TransTable;

    static Widget DragIcon;
    // Define constants for the dnd data types we understand
    enum {
	Trash,
	ToolName
    };


  protected:

    //
    // Drag - n - Drop
    //
    virtual boolean decodeDropType (int , char *, XtPointer , unsigned long , int , int );
    virtual boolean decodeDragType (int, char *, XtPointer*, unsigned long*, long);

    //
    // Protected member data:
    //
    void clearToolListWidget();

    Widget	getToolListWidget() { return toolList; }
    Widget	getCategoryListWidget() { return toolList; }

    //
    // One time initialize for the class. 
    // 
    void initialize();

    //
    // Build the category lists and add the list items to the widgets.
    // from a dictionary of NodeDefinitions.
    //
    boolean layoutWidgets(Widget parent);
    boolean initializeWidgets(Widget parent);

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

#if 00
    boolean addTool(const char *cat, const char *tool, void *nd); 
    boolean removeTool(const char *cat, const char *tool); 
#endif

    //
    // Build a new Category list and install it in the categoryList.
    //
    boolean updateCategoryListWidget();

    //
    // Install new strings into the toolList widget based on the current
    // state of 'this' (i.e. the active_category)
    //
    boolean updateToolListWidget();

    //
    // Install the callbacks for the widgets in this class. 
    // Includes the tool list and category selection widgets.
    //
    void installCallbacks();

    //
    // Member function callback called through 
    // ToolSelector::ToolSelector_ToolSelectCB() to handle tool list 
    // selection callbacks.
    //
    virtual void toolSelect(Widget widget, XmListCallbackStruct* callData);

    //
    // Member function callback called through 
    // ToolSelector::ToolSelector_CategorySelectCB() to handle tool list selection 
    // callbacks.
    //
    virtual void categorySelect(Widget widget, XmListCallbackStruct* callData);

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

#if 00
    static boolean AddTool(const char *cat, const char *tool, void *nd); 
    static boolean RemoveTool(const char *cat, const char *tool); 
#endif

    static boolean UpdateCategoryListWidget();
    static boolean UpdateToolListWidget();

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
    void deselectAllTools();
 
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassToolSelector;
    }
};


#endif // _ToolSelector_h
