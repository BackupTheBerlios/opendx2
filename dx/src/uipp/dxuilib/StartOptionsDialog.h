///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/StartOptionsDialog.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 */



#ifndef _StartOptionsDialog_h
#define _StartOptionsDialog_h


#include "defines.h"
#include "Dialog.h"


//
// Class name definition:
//
#define ClassStartOptionsDialog	"StartOptionsDialog"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void StartOptionsDialog_NumberTextCB(Widget, XtPointer, XtPointer);
extern "C" void StartOptionsDialog_ToggleCB(Widget, XtPointer, XtPointer);


//
// StartOptionsDialog class definition:
//				
class StartOptionsDialog : public Dialog
{
  private:
    //
    // Private member data:
    //
    static Boolean ClassInitialized;

  protected:
    //
    // Protected member data:
    //
    static String  DefaultResources[];
    friend void StartOptionsDialog_ToggleCB(Widget w, XtPointer clientData, XtPointer);
    friend void StartOptionsDialog_NumberTextCB(Widget w, XtPointer clientData, XtPointer);

    virtual boolean okCallback(Dialog *clientData);

    virtual Widget createDialog(Widget parent);
    Widget execText;
    Widget cwdText;
    Widget memText;
    Widget optionsText;
    Widget connectButton;
    Widget portStepper;

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

  public:
    //
    // Constructor:
    //
    StartOptionsDialog(Widget parent);

    //
    // Destructor:
    //
    ~StartOptionsDialog(){}

    virtual void manage();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassStartOptionsDialog;
    }
};


#endif // _StartOptionsDialog_h
