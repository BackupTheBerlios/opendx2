//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// GridDialog.h -			        		 	    //
//                                                                          //
// Definition for the GridDialog class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/GridDialog.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */


#ifndef _GridDialog_h
#define _GridDialog_h


#include "defines.h"
#include "Dialog.h"

//
// Class name definition:
//
#define ClassGridDialog	"GridDialog"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void GridDialog_DimensionCB(Widget, XtPointer, XtPointer);
extern "C" void GridDialog_AlignmentCB(Widget, XtPointer, XtPointer);

class WorkSpace;

//
// GridDialog class definition:
//				

class GridDialog : public Dialog
{

  private:
    //
    // Private member data:
    //
    static boolean ClassInitialized;

    Widget toplevel_form;
    Widget separator1, separator2, separator3;
    Widget hLabel;
    Widget vLabel;
    Widget align_form;
    Widget ulbtn;
    Widget urbtn;
    Widget llbtn;
    Widget lrbtn;
    Widget ctbtn;
    Widget leftbtn;
    Widget rightbtn;
    Widget upperbtn;
    Widget lowerbtn;
    Widget vspacing;
    Widget hspacing;
    Widget alignLabel, spaceLabel;
    Widget gc_rc;
    Widget noneTButton;
    Widget oneDhTButton;
    Widget oneDvTButton;
    Widget twoDTButton;

    WorkSpace     *workSpace;

  protected:
    //
    // Protected member data:
    //
    static String  DefaultResources[];
    friend void GridDialog_AlignmentCB(Widget, XtPointer , XtPointer);
    friend void GridDialog_DimensionCB(Widget, XtPointer , XtPointer);

    //
    // Constructor:
    //
    GridDialog(char *name, Widget parent, WorkSpace*);

    virtual void manage();
    virtual Widget createDialog(Widget);
    virtual boolean okCallback(Dialog * /* clientData */);
    void   resetToggleBtn();

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

  public:

    //
    // Public Constructor that uses a static widget name:
    //
    GridDialog(Widget parent, WorkSpace*);

    //
    // Destructor:
    //
    ~GridDialog();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassGridDialog;
    }
};


#endif // _GridDialog_h
