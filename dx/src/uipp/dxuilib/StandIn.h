//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// StandIn.h -							            //
//                                                                          //
// Definition for the StandIn class.				            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/StandIn.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 *
 */

#ifndef _StandIn_h
#define _StandIn_h


#include <Xm/Xm.h>
#include "defines.h"
#include "UIComponent.h"
#include "List.h"
#include "DXDragSource.h"


//
// Class name definition:
//
#define ClassStandIn	"StandIn"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void StandIn_TrackArcEH(Widget, XtPointer, XEvent*, Boolean*);
extern "C" void StandIn_Button2PressEH(Widget, XtPointer, XEvent*, Boolean*);
extern "C" void StandIn_Button2ReleaseEH(Widget, XtPointer, XEvent*, Boolean*);
extern "C" void StandIn_DisarmTabCB(Widget, XtPointer, XtPointer);
extern "C" void StandIn_ArmOutputCB(Widget, XtPointer, XtPointer);
extern "C" void StandIn_ArmInputCB(Widget, XtPointer, XtPointer);
extern "C" void StandIn_SelectNodeCB(Widget, XtPointer, XtPointer);

class Tab;
class Arc;
class Node;
class EditorWindow;
class WorkSpace;

typedef long NodeParameterStatusChange;	// Also defined in Node.h

//
// StandIn class definition:
//				
class StandIn : public UIComponent, public DXDragSource
{

//friend class Node;
//friend class Network;


  private:
   
    static Boolean ClassInitialized;
    static Widget DragIcon;
    static Dictionary *DragTypeDictionary;

    int selected;
    WorkSpace *workSpace;

    List  inputTabList;
    List  outputTabList;

   
    /*
     * module label (button):
     */
    Widget 	buttonWidget;
    Dimension	buttonHeight;
    Dimension   requiredButtonWidth;


    friend void StandIn_SelectNodeCB(Widget widget,
                XtPointer clientData,
                XtPointer cdata);

    friend void StandIn_ArmInputCB(Widget widget,
                XtPointer clientData,
                XtPointer cdata);
    void armInput(Widget widget, XtPointer cdata);

    friend void StandIn_ArmOutputCB(Widget widget,
                XtPointer clientData,
                XtPointer cdata);
    void armOutput(Widget widget, XtPointer cdata);


    friend void StandIn_DisarmTabCB(Widget widget,
                XtPointer clientData,
                XtPointer cdata);
    void disarmTab(Widget widget, XtPointer cdata);


    friend void StandIn_Button2PressEH(Widget widget,
                XtPointer ,
                XEvent* event,
		Boolean *keep_going);
    friend void StandIn_Button2ReleaseEH(Widget widget,
                XtPointer ,
                XEvent* event,
		Boolean *keep_going);

    friend void StandIn_TrackArcEH(Widget widget,
                XtPointer clientData,
                XEvent* event,
		Boolean *cont);
    void trackArc(Widget widget, XEvent *event);

    boolean  setMinimumWidth(int &width);
    int  getVisibleInputCount();
    int  getVisibleOutputCount();
    void adjustParameterLocations(int width);

    Tab *createInputTab(Widget parent, int index, int width);
    Tab *createOutputTab(Widget parent, int index, int width);

    void indicateSelection(boolean select);

    void setVisibility(int index, boolean outputTab);
    XmString   createButtonLabel();

    //
    // Supply the type dictionary which stores the types we can supply for a dnd 
    //
    virtual Dictionary *getDragDictionary() { return StandIn::DragTypeDictionary; }

    // Define the data type for the drag operation.  These replace the use of
    // function pointers.  They're passed to addSupportedType and decoded in
    // decodeDragType
    enum {
	Modules,
	Interactors,
	Trash
    };

  protected:
    //
    // Protected member data:
    //
    static String  DefaultResources[];

    Node* node;
    virtual void  initialize();

    void       setButtonLabel();
    virtual    const char *getButtonLabel();
    virtual    void handleSelectionChange(boolean select);

    //
    // Drag and Drop related stuff
    //
    virtual int decideToDrag(XEvent *);
    virtual void dropFinish(long, int, unsigned char);
    virtual boolean decodeDragType (int, char *, XtPointer*, unsigned long*, long);

    virtual const char *getButtonLabelFont();

    //
    // Constructor:
    //
    StandIn(WorkSpace *w, Node *node);

  public:


    //
    // Allocator that is installed in theSIAllocatorDictionary
    //
    static StandIn *AllocateStandIn(WorkSpace *w, Node *n);

    //
    // Destructor:
    //
    ~StandIn();

    void createStandIn();
    void addInput(int index);
    void removeLastInput();

    void addOutput(int index);
    void removeLastOutput();

    virtual void setLabelColor(Pixel color);
    virtual Pixel getLabelColor();

    void deleteArc(Arc *a);
    void drawArcs(Node *dst_node);
    void drawTab(int paramIndex, boolean outputTab);

    void ioStatusChange(int index, boolean outputTab, 
					NodeParameterStatusChange status);

    static void ToggleHotSpots(EditorWindow* editor,
                               Node*    destnode,
                               boolean     on);

    void displayTabLabel(int index, boolean outputTab);
    void clearTabLabel();
    Tab *getInputParameterTab(int i);
    Tab *getOutputParameterTab(int i); 

    Tab *getParameterTab(int i, int input) 
        { return (input ? getInputParameterTab(i):
                          getOutputParameterTab(i)); }

    Widget getInputParameterLine(int i);
    Widget getOutputParameterLine(int i); 
    Widget getParameterLine(int i, int input) 
        { return (input ? getInputParameterLine(i):
                          getOutputParameterLine(i)); }

    void setInputParameterLine(int i, Widget w);
    void setOutputParameterLine(int i, Widget w);
    void setParameterLine(int i, Widget w, int input) 
        { input ? setInputParameterLine(i,w) :
                  setOutputParameterLine(i,w); }

    int getIOWidth();
    int getIOHeight();

    int getInputParameterTabX(int i);
    int getInputParameterTabY(int i);

    int getOutputParameterTabX(int i);
    int getOutputParameterTabY(int i);

    int getParameterTabY(int i,int input) 
        { return (input ? getInputParameterTabY(i):getOutputParameterTabY(i));}

    int getParameterTabX(int i,int input) 
        { return (input ? getInputParameterTabX(i):getOutputParameterTabX(i));}



    void setSelected(int s); 
    int isSelected()        { return this->selected; }

    void addArc(EditorWindow* editor, Arc *a);

    //
    // Print a representation of the stand in on a PostScript device.  We
    // assume that the device is in the same coordinate space as the parent
    // of this uicomponent (i.e. we send the current geometry to the 
    // PostScript output file).  We do not print the ArcStandIns, but do
    // print the Tabs.
    //
    boolean printPostScriptPage(FILE *f, boolean label_parameters = TRUE);
    static boolean PrintPostScriptSetup(FILE *f);
    virtual const char *getPostScriptLabelFont();


    //
    // This function can be called to notify a standin that its label
    // has changed.  By default, this standin just calls setButtonLabel() 
    // to reset the label. 
    virtual void notifyLabelChange();

    //
    // Now that StandIns can live in any WorkSpace, we need to query this.
    //
    WorkSpace *getWorkSpace() { return this->workSpace; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassStandIn;
    }
};

extern Pixel standInGetDefaultForeground();

#endif // _StandIn_h
