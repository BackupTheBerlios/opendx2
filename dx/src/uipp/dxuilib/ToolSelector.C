/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "../base/defines.h"
#include "../base/defines.h"




#include <Xm/Xm.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/Label.h>
#include <Xm/ScrolledW.h>


#include "ToolSelector.h" 
#include "NodeDefinition.h"
#include "Dictionary.h"
#include "DictionaryIterator.h"

boolean ToolSelector::ToolSelectorClassInitialized = FALSE;
List ToolSelector::AllToolSelectors;
Dictionary* ToolSelector::DropTypeDictionary = new Dictionary;
Dictionary* ToolSelector::DragTypeDictionary = new Dictionary;
Widget ToolSelector::DragIcon = NULL;

#include "tooldrag.bm"
#include "tooldragmask.bm"

#define UNSELECTED_INDEX -1
#define ALPHABETIZED "( ALL )"

#define DXTRASH "DXTRASH"
#define DXTOOLNAME "DXTOOLNAME"

// It's tough to make this string.  The name DragSource_StartDrag must be the name
// used in the superclass.  That name is not made available, we just know what it is.
char* ToolSelector::DragTranslations =
"#override <Btn2Down>: ListKbdDeSelectAll() ListBeginSelect() ListEndSelect() DragSource_StartDrag()";

XtTranslations ToolSelector::TransTable = NULL;

String ToolSelector::DefaultResources[] =
{
    ".width:    180",
    "*XmFrame.shadowThickness:	2",
    "*XmFrame.marginWidth:	3",
    "*XmFrame.marginHeight:	3",
    "*categoryListLabel.labelString: Categories:",
    "*toolListLabel.labelString:     Tools:",
     NUL(char*)
};

//
// Constructor:
//
ToolSelector::ToolSelector(const char *name) : UIComponent(name) 
{
    this->activeData = NUL(void*); 
    this->lockedData = FALSE;
    this->lastToolIndex = UNSELECTED_INDEX;

    this->initialize();

    AllToolSelectors.appendElement((void*)this);
}


//
// Destructor:
//
ToolSelector::~ToolSelector()
{
    ActiveItemDictionary *d;
    DictionaryIterator iterator(this->categoryDictionary);
    while (d = (ActiveItemDictionary*)iterator.getNextDefinition())
        delete d;

    AllToolSelectors.removeElement((void*)this);
}

//
// Unhighlight any selected tools in the tool list.
// We only allow one selection at a time so this is just deselecting THE 
// selected item (if there is one).
//
void ToolSelector::deselectAllTools()
{
    if (this->lastToolIndex != UNSELECTED_INDEX) {
	ASSERT(this->toolList);
	XmListDeselectAllItems(this->toolList);
	this->activeData = NULL;
	this->lockedData = FALSE;
	this->lastToolIndex = UNSELECTED_INDEX;
    }
}


void ToolSelector::initialize()
{
    //
    // Initialize default resources (once only).
    //
    if (NOT ToolSelector::ToolSelectorClassInitialized)
    {
        ASSERT(theApplication);
        this->setDefaultResources(theApplication->getRootWidget(),
                                  ToolSelector::DefaultResources);
        ToolSelector::ToolSelectorClassInitialized = TRUE;

	//XtAppAddActions (XtWidgetToApplicationContext(), actions, XtNumber(actions));

	ToolSelector::TransTable = XtParseTranslationTable (DragTranslations);

	this->DropSite::addSupportedType (ToolSelector::Trash, DXTRASH, TRUE);
	this->DragSource::addSupportedType (ToolSelector::ToolName, DXTOOLNAME, TRUE);
    }
    if (!ToolSelector::DragIcon) {
        ToolSelector::DragIcon =
                this->createDragIcon(tooldrag_width, tooldrag_height,
                                     (char *)tooldrag_bits,
                                     (char *)tooldragmask_bits);
    }

}
//
// Build two list widgets and initialize the lists from the items in
// the dictionary. 
//
boolean ToolSelector::initialize(Widget parent, 
                                 Dictionary *d)
{
    int rc;

    //
    // Create the widgets before do 'addTool'.
    //
    if (!this->layoutWidgets(parent))
	return FALSE;


    theSymbolManager->registerSymbol(ALPHABETIZED);

    this->installCallbacks();

    if (d->getSize() == 0)
	return TRUE;
    //
    // Build the category lists. 
    //
    if (!this->augmentLists(d))
	return FALSE;


    //
    // Install the strings in the list widgets.
    //
    rc = updateCategoryListWidget() && updateToolListWidget();

    //
    // After the lists are initialized, highlight the first
    // category.  This will call the callback associated with 
    // the list widget.
    //
    XmListSelectPos(this->categoryList, 1, True);

    return rc;
}


//
// Build the category lists and add the list items to the widgets. 
// from a dictionary of NodeDefinitions.
//
boolean ToolSelector::augmentLists(Dictionary *d)
{
    Symbol c, t;
    DictionaryIterator iterator(*d);
    NodeDefinition *nd;
 
    //
    // Look at all the node definitions and insert their category:name
    // pairs in the categories member.
    //
    while (nd = (NodeDefinition*)iterator.getNextDefinition()) {
        c = nd->getCategorySymbol();
        t = nd->getNameSymbol();
        if (!this->addTool(c, t, (void*)nd))
		return FALSE;
    }

    return TRUE;
}

//
//  Build the widget tree. 
//
boolean ToolSelector::layoutWidgets(Widget parent)
{
    Widget label;


    this->setRootWidget(
        XtCreateManagedWidget (this->name, xmFormWidgetClass, parent,NULL,0));

    this->setDragIcon(ToolSelector::DragIcon);

    XtVaSetValues(this->getRootWidget(), XmNresizePolicy, XmRESIZE_NONE, NULL);

    this->toolListLabel =
        XtVaCreateManagedWidget
            ("toolListLabel",
             xmLabelWidgetClass,
             this->getRootWidget(),
             XmNtopAttachment,   XmATTACH_POSITION,
             XmNtopPosition,     40,
             XmNleftAttachment,  XmATTACH_FORM,
             XmNrightAttachment, XmATTACH_FORM,
             XmNalignment,       XmALIGNMENT_BEGINNING,
             NULL);


    Widget frame = XtVaCreateManagedWidget("toolFrame",
                         xmFrameWidgetClass,     this->getRootWidget(), 
			 XmNtopAttachment,    XmATTACH_WIDGET,
			 XmNtopWidget,        this->toolListLabel,
			 XmNtopOffset,        5,
			 XmNleftAttachment,   XmATTACH_FORM,
			 XmNrightAttachment,  XmATTACH_FORM,
			 XmNbottomAttachment, XmATTACH_FORM,
			 NULL);

    this->toolList = XmCreateScrolledList(frame, 
				"toolList", NUL(ArgList), 0);
    XtManageChild(this->toolList);


    label = XtVaCreateManagedWidget
            ("categoryListLabel",
             xmLabelWidgetClass, 
	     this->getRootWidget(),
             XmNtopAttachment,   XmATTACH_FORM,
             XmNleftAttachment,  XmATTACH_FORM,
             XmNrightAttachment, XmATTACH_FORM,
             XmNalignment,       XmALIGNMENT_BEGINNING,
             NULL);

    frame = XtVaCreateManagedWidget("categoryFrame",
                         xmFrameWidgetClass, this->getRootWidget(), 
			 XmNtopAttachment,    XmATTACH_WIDGET,
			 XmNtopWidget,        label,
			 XmNtopOffset,        5,
			 XmNleftAttachment,   XmATTACH_FORM,
			 XmNrightAttachment,  XmATTACH_FORM,
			 XmNbottomAttachment, XmATTACH_WIDGET,
			 XmNbottomWidget,     this->toolListLabel,
			 XmNbottomOffset,     10,
			 NULL);

    this->categoryList = XmCreateScrolledList(frame,
				"categoryList", NUL(ArgList), 0);

    XtManageChild(this->categoryList);

    //
    // Set up drop widget.  
    // Set up drag widget.  This normall means telling motif about us
    // and installing a button2 translation.  In this case the button2
    // translation is special because we want to select the text under
    // the mouse and then let the drag operation proceed.  It's better
    // visual feedback
    //
    this->setDropWidget(this->getRootWidget(), XmDROP_SITE_COMPOSITE);
    this->setDragWidget(this->toolList);
    XtOverrideTranslations (this->toolList, ToolSelector::TransTable);

    return TRUE;
}

//
// Add the Node named 'tool' that is in category 'cat' and defined by 'nd'
// to the table of category/tool pairings.
// We keep an ActiveItemDictionary of ActiveItemDictoinaries.  The
// first level of dictionary is the categories, the second is the tools
// under the given category.
// In addition, we always update the alphabetic tool list.
// This does not update the widgets.
//
boolean ToolSelector::addTool(Symbol cat, Symbol tool, void *ptr)
{
    ActiveItemDictionary *toollist;

#if 00
    const char *vcr = theSymbolManager->getSymbolString(tool);
    if (EqualString(vcr,"VCR")) {
	printf("Found VCR in category '%s'\n",
		theSymbolManager->getSymbolString(cat));
    } 
#endif

    //
    // Tools without categories are ignored.
    //
    if (!cat)
	return TRUE;

    toollist = (ActiveItemDictionary*)
                        this->categoryDictionary.findDefinition(cat);
    //
    // If adding new category create a new toollist data structure
    //
    if (!toollist) {
        toollist = new ActiveItemDictionary;
        this->categoryDictionary.addDefinition(cat, toollist);
    }


    if (!toollist->addDefinition(tool,ptr) && 
        !toollist->replaceDefinition(tool,ptr))
	return FALSE;

    
    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
    if (cat != alpha)
	return this->addTool(alpha,tool,ptr);
    else
	return TRUE;
}

#if 00
// See the comments for addTool() above.
boolean ToolSelector::addTool(const char *cat, const char *tool,
                void *ptr)
{
   Symbol t, c;

    //
    // Tools without categories are ignored.
    //
    if (!cat || !*cat)
	return TRUE;

   c = theSymbolManager->registerSymbol(cat);
   t = theSymbolManager->registerSymbol(tool);
   ASSERT(c != 0);
   ASSERT(t != 0);

   return this->addTool(c,t,ptr);
}
#endif

//
// Remove the Node named 'tool' that is in category 'cat'
// from the table of category/tool pairings.
// We keep a of ActiveItemDictionary of ActiveItemDictoinaries.  The
// first level of dictionary is the categories, the second is the tools
// under the given category.
// This also removes the tool from the alphabetic list.
// This does not update the widgets.
//
boolean ToolSelector::removeTool(Symbol cat, Symbol tool)
{
    ActiveItemDictionary *toollist;


    toollist = (ActiveItemDictionary*)
                        this->categoryDictionary.findDefinition(cat);
    //
    // If adding new category create a new toollist data structure
    //
    if (!toollist ||
         toollist->removeDefinition(tool) == NULL)
	return FALSE;

    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
    if (cat != alpha)
	return this->removeTool(alpha,tool);
    else
	return TRUE;
}
#if 00
// See the comments for removeTool() above.
boolean ToolSelector::removeTool(const char *cat, const char *tool)
{
   Symbol t, c;

   c = theSymbolManager->registerSymbol(cat);
   t = theSymbolManager->registerSymbol(tool);
   ASSERT(c != 0);
   ASSERT(t != 0);

   return this->removeTool(c,t);
}
#endif

//
// Install new strings into the toolList widget based on the current 
// state of 'this' (i.e. the active_category)
//boolean ToolSelector::updateToolSelectorListWidgets()
//{
//	return updateCategoryListWidget() && updateToolListWidget();
//}
// 
// Install new strings into the toolList widget based on the current 
// state of 'this' (i.e. the active_category)
//
boolean ToolSelector::updateToolListWidget()
{
    int n, n_items;
    ActiveItemDictionary *toollist;
    Symbol tool;
    const char *str;
    XmString *xmstrings;
    Arg arg[3];
    Dimension   width;

    toollist = (ActiveItemDictionary*)
                        this->categoryDictionary.getActiveDefinition();
    ASSERT(toollist != NUL(ActiveItemDictionary*));


    DictionaryIterator iterator(*toollist);
    n_items = toollist->getSize();

    if (n_items != 0)
    {
        xmstrings = new XmString[n_items];
	n=0;
	while (tool = iterator.getNextSymbol()) {
	    str = theSymbolManager->getSymbolString(tool);
	    xmstrings[n] = XmStringCreateLtoR((char*)str,"bold");
	    n++;
	}
    }
    else
    {
	n_items = 1;
	xmstrings = new XmString[n_items];
        xmstrings[0] = XmStringCreateLtoR("(none)", "oblique");
    }

    n = 0;
    XtSetArg(arg[n], XmNitemCount,        n_items);   n++;
    XtSetArg(arg[n], XmNitems,            xmstrings); n++;
    XtSetValues(this->toolList, arg, n);

    for (n=0 ; n<n_items ; n++)
	XmStringFree(xmstrings[n]);
    delete xmstrings;

    this->toolListDirty = FALSE;

    return TRUE;

}


void ToolSelector::clearToolListWidget()
{
    this->activeData = NULL;
    this->lockedData = FALSE;
    this->lastToolIndex = UNSELECTED_INDEX;
    XmListDeleteAllItems(this->toolList);
}
//
// Build a new Category list and install it in the categoryList. 
// This assumes that there is at least ONE categorie.
//
boolean ToolSelector::updateCategoryListWidget()
{
    ASSERT(this->categoryList != NUL(Widget));

    int n_items = this->categoryDictionary.getSize();
    XmString *xmstrings = new XmString[n_items];
    DictionaryIterator iterator(this->categoryDictionary);
    Symbol cat;

    int i;
    Symbol first_cat = 0;
    for (i = 0; cat = iterator.getNextSymbol(); ++i) {
	const char *str;
	if (i==0)
	    first_cat = cat;	
        str = theSymbolManager->getSymbolString(cat);
        xmstrings[i] = XmStringCreateLtoR((char*)str,"bold");
    }

    XtVaSetValues(this->categoryList, 
	XmNitemCount,        n_items,
	XmNitems,            xmstrings,
	NULL);

    for (i = 0; i < n_items; ++i)
	XmStringFree(xmstrings[i]);
    delete xmstrings;

    if (!this->categoryDictionary.isActive())
        this->categoryDictionary.setActiveItem(first_cat);

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////


//
// Install the callbacks for the widgets in this class. 
// Includes the tool list and category selection widgets.
//
void ToolSelector::installCallbacks()
{
    Arg arg[1];

    
    XtSetArg(arg[0], XmNselectionPolicy, XmSINGLE_SELECT);

    // Enable single click selection
    XtSetValues(this->categoryList, arg, 1);

    // Install the single click callback
    XtAddCallback(this->categoryList,
		  XmNsingleSelectionCallback, 
		  (XtCallbackProc)ToolSelector_CategorySelectCB,
		  (XtPointer)this);

    // Enable single click selection
    XtSetValues(this->toolList, arg, 1);	

    // Install the single click callback
    XtAddCallback(this->toolList,
		  XmNsingleSelectionCallback, 
		  (XtCallbackProc)ToolSelector_ToolSelectCB,
		  (XtPointer)this);

    // Install the double click callback
    XtAddCallback(this->toolList,
		  XmNdefaultActionCallback, 
		  (XtCallbackProc)ToolSelector_ToolSelectCB,
		  (XtPointer)this);

    // Install the help callback
    XtAddCallback(this->toolList,
		  XmNhelpCallback, 
		  (XtCallbackProc)ToolSelector_ToolHelpCB,
		  (XtPointer)this);
}

//
// Static member callback for the category selection list.
//
extern "C" void ToolSelector_CategorySelectCB(
		Widget w, XtPointer clientData, XtPointer callData)
{
	ToolSelector *ts = (ToolSelector*) clientData;
	ts->categorySelect(w, (XmListCallbackStruct*)callData);
}
	
//
// Member function callback called through 
// (XtCallbackProc)ToolSelector_CategorySelectCB() to handle tool list selection 
// callbacks.
//
void ToolSelector::categorySelect(
		    Widget                widget,
	            XmListCallbackStruct* callData)
{
    char*    value;
    char     string[128];
    XmString label;
    Arg      arg[1];
    ActiveItemDictionary *toollist;

    ASSERT(widget);
    ASSERT(callData);

    /*
     * Get the index of the selected category.
     */
    toollist = (ActiveItemDictionary*)
		this->categoryDictionary.getDefinition(callData->item_position);
    ASSERT(toollist);

    /*
     * If a new category has been selected, build a module list.
     */
    if (toollist != this->categoryDictionary.getActiveDefinition()) {
	Symbol cat_symbol = this->categoryDictionary.getSymbol(
						callData->item_position);
	this->categoryDictionary.setActiveItem(cat_symbol);
	this->clearToolListWidget();
	this->updateToolListWidget();
    }

    /*
     * Set the module list label.
     */
    XmStringGetLtoR(callData->item, "bold", &value);
    sprintf(string, "%s Tools:", value);
    label = XmStringCreate(string, "bold");

    XtSetArg(arg[0], XmNlabelString, label);
    XtSetValues(this->toolListLabel, arg, 1);

    XmStringFree(label);
    XtFree(value);

}



//
// Static member callback for tool selection list.
//
extern "C" void ToolSelector_ToolSelectCB(
		Widget w, XtPointer clientData, XtPointer callData)
{
    ToolSelector *ts = (ToolSelector*) clientData;

    ts->toolSelect(w, (XmListCallbackStruct*)callData);
}

//
// Member function callback called through (XtCallbackProc)ToolSelector_ToolSelectCB().
// to handle tool list selection call backs.
//
void ToolSelector::toolSelect(
		    Widget                widget,
	            XmListCallbackStruct* callData)
{
    int        tool_index;
    ActiveItemDictionary *toollist;

    ASSERT(widget);
    ASSERT(callData);

    int selects, reason = callData->reason;
    XtVaGetValues(widget, XmNselectedItemCount, &selects, NULL);
    ASSERT(selects <= 1);

    // 
    //  Look for either a double click or the first single click
    // 
    if (selects == 1) {
	/*
	 * Search for the selected module.
	 */
	toollist = (ActiveItemDictionary*)
		this->categoryDictionary.getActiveDefinition();

        tool_index  = callData->item_position;
	ASSERT(tool_index > 0);
	this->activeData = toollist->getDefinition(tool_index); 
        this->lastToolIndex = tool_index;
    } else { 
        this->lastToolIndex = UNSELECTED_INDEX;
	this->activeData = NULL;
    } 

    if ((this->activeData != NULL) && (reason == XmCR_DEFAULT_ACTION)) {
	this->lockedData = TRUE;
	ASSERT(this->activeData);
    } else {
	this->lockedData = FALSE;
    }
}

//
// return the NodeDefinition of char strings or 0 if the item is not
// in the list.  Added 5/15/95 for dnd support.  The vpe needs this in
// order to know if the DXTOOLNAME dropped on him is a legal tool for
// the current copy of dx.  Just because something was dragged froma ToolSelector
// doesn't mean it will be dropped on the same dx. 
//
NodeDefinition *
ToolSelector::definitionOf (const char *category, const char *item)
{
ActiveItemDictionary *toolList;
NodeDefinition* activeData;

    toolList = (ActiveItemDictionary*)this->categoryDictionary.findDefinition(category);
    if (!toolList) return 0;

    activeData = (NodeDefinition*)toolList->findDefinition (item);
    if (!activeData) return 0;

    return activeData;
    
}

extern "C" void ToolSelector_ToolHelpCB(Widget w, 
			     XtPointer clientData, XtPointer callData)
{
    ToolSelector *ts = (ToolSelector*)clientData;
    XmString label;

    XtVaGetValues(ts->toolListLabel, XmNlabelString, &label, NULL);

    char *labelString;
    XmStringGetLtoR(label, "bold", &labelString);

    *strstr(labelString, " Tools:") = '\0';
    char *p;
    for (p = labelString; *p; ++p)
	if (*p == ' ' || *p == '\t')
	    *p = '-';

    theApplication->helpOn(labelString);
    XtFree(labelString);

}

// These perform addTool and removeTool to all tool selectors.
boolean ToolSelector::AddTool(Symbol cat, Symbol tool, void *ptr)
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;
    boolean result;

    //
    // If there is no category, don't put it in the list.
    //
    if (!cat)
	return TRUE;

    while(ts = (ToolSelector*)li.getNext())
    {
	if (!ts->addTool(cat, tool, ptr))
	    result = FALSE;
    }
    return TRUE;
}
#if 00
boolean ToolSelector::AddTool(const char *cat, const char *tool, void *nd)
{
   Symbol t, c;

    //
    // If there is no category, don't put it in the list.
    //
    if (!cat || !*cat)
	return TRUE;

   c = theSymbolManager->registerSymbol(cat);
   t = theSymbolManager->registerSymbol(tool);
   ASSERT(c != 0);
   ASSERT(t != 0);

   return AddTool(c,t,nd);
}
#endif

boolean ToolSelector::RemoveTool(Symbol cat, Symbol tool)
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;
    boolean result = TRUE;
    while(ts = (ToolSelector*)li.getNext())
    {
	if (!ts->removeTool(cat, tool))
	    result = FALSE;
    }
    return result;
}
#if 00
boolean ToolSelector::RemoveTool(const char *cat, const char *tool)
{
   Symbol t, c;

   c = theSymbolManager->registerSymbol(cat);
   t = theSymbolManager->registerSymbol(tool);
   ASSERT(c != 0);
   ASSERT(t != 0);

   return RemoveTool(c,t);
}
#endif

boolean ToolSelector::UpdateCategoryListWidget()
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;
    boolean result = TRUE;
    while(ts = (ToolSelector*)li.getNext())
    {
	if (!ts->updateCategoryListWidget())
	    result = FALSE;
    }
    return result;
}

boolean ToolSelector::UpdateToolListWidget()
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;
    boolean result = TRUE;
    while(ts = (ToolSelector*)li.getNext())
    {
	if (!ts->updateToolListWidget())
	    result = FALSE;
    }
    return result;
}

//
// Merge new tools definitions into all tool selectors from a dictionary 
// of NodeDefinitions.
//
boolean ToolSelector::MergeNewTools(Dictionary *d)
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;

    while(ts = (ToolSelector*)li.getNext())
    {
	if (!ts->augmentLists(d) 	|| 
	    !ts->updateToolListWidget() || 
	    !ts->updateCategoryListWidget())
	    return FALSE;
    }
    return TRUE;
}

// Called to consumate a dnd operation
boolean ToolSelector::decodeDropType (int tag,
	char *, XtPointer , unsigned long, int, int)
{
boolean retVal;
    switch (tag) {
	case ToolSelector::Trash:
	    retVal = TRUE;
	    break;
	default:
	    retVal = FALSE;
	    break;
    }
    return retVal;
}

boolean ToolSelector::decodeDragType (int tag,
	char *a, XtPointer *value, unsigned long *length, long operation)
{
boolean retVal;
NodeDefinition *nd;
const char *toolname;
const char *category;
char *cp;

    switch(tag) {

	// Get the text of item under the mouse. (Must be the selected item.)
	// Put that text into *value.  The format is "category:toolname".
	case ToolSelector::ToolName:

	    nd = this->getCurrentSelection();
	    // don't assert because rapid clicking can unselect something
	    // in the selector;
	    //ASSERT(nd);
	    if (nd) {

	        toolname = nd->getNameString();
	        category = nd->getCategoryString();
	        if ((!toolname) || (!toolname[0]) || (!category) || (!category[0])) {
		    retVal = FALSE;
		    break;
	        }

	        cp = (char *)new char[2 + strlen(category) + strlen(toolname)];
	        sprintf (cp, "%s:%s", category, toolname);
	        *value = cp;
	        *length = strlen(cp);
	        retVal = TRUE;
	    } else {
		retVal = FALSE;
	    }
	    
	    break;
	default:
	    retVal = FALSE;
	    break;
    }
    return retVal;
}

