//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// Dialog.h -								    //
//                                                                          //
// Definition for the Dialog class.					    //
// This dialog class is intended to be used as a base for all other dialogs,//
// and not instantiated itself.  One needs to define createDialog to        //
// actually make an unmanaged dialog.  The base dialog class assumes that   //
// some of three buttons will be created, this->ok, this->cancel, and this  //
// ->help.  The virtual functions okCallback, cancelCallback, and 	    //
// helpCallback will be called, and if it's cancel, the dialog will be     //
// unmanaged.  If its ok and okCallback() returns TRUE, then the dialog will//
// be unmanged.  To add buttons, a derived class will emulate this, adding a  //
// static widget callback (like Dialog::Dialog_OkCB) and a virtual function  //
// like Dialog::okCallback.  A child that uses a dialog with built in 	    //
// buttons and callbacks should redefine post so that it installs Dialog's  //
// static widget callbacks Dialog::{Ok,Cancel,Help}Callback in the right    //
// way, and, if this->root doesn't exist, it should 			    //
// this->createDialog(this->parent); this->installWidgetDestroyCallback();  //
// it should also this->manage(); the dialog.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Dialog.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 *
 */

#ifndef _Dialog_h
#define _Dialog_h


#include "defines.h"
#include "UIComponent.h"


//
// DialogCallback type definition:
//
typedef void (*DialogCallback)(void*);

//
// Class name definition:
//
#define ClassDialog	"Dialog"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB) functions for this and derived classes
//
extern "C" void Dialog_HelpCB(Widget, XtPointer, XtPointer);
extern "C" void Dialog_CancelCB(Widget, XtPointer, XtPointer);
extern "C" void Dialog_OkCB(Widget, XtPointer, XtPointer);

//
// Dialog class definition:
//				
class Dialog : public UIComponent
{
  private:
    //
    // Private member data:
    //
    static boolean ClassInitialized;

  protected:
    //
    // Protected member data:
    //
    friend void Dialog_OkCB(Widget widget,
			   XtPointer clientData,
			   XtPointer);
    friend void Dialog_CancelCB(Widget widget,
			       XtPointer clientData,
			       XtPointer);
    friend void Dialog_HelpCB(Widget widget,
			     XtPointer clientData,
			     XtPointer);

    //
    // This is to create a top level form contained by a shell widget.
    // Most of the dialogs should use this method, instead of 
    // XmCreateFormDialog(), to avoid the X bug on some platforms
    // like SGI indigo.
    //
    static Widget CreateMainForm(Widget parent, String name, 
				 ArgList arg, Cardinal argcount);

    boolean managed;

    Widget parent;
    Widget ok;
    Widget cancel;
    Widget help;

    virtual boolean okCallback(Dialog * /* clientData */) {return TRUE;}
    virtual void helpCallback(Dialog * /* clientData */) {}
    virtual void cancelCallback(Dialog * /* clientData */) {}

    virtual Widget createDialog(Widget parent);

    //
    // One time class initializations.
    //
    virtual void initialize();

    //
    // Constructor for the subclasses:
    //
    Dialog(const char *name, Widget parent);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

  public:

    //
    // Destructor:
    //
    ~Dialog(){}

    virtual void post();

    virtual void manage();
    virtual void unmanage();
    virtual boolean isManaged();

    //
    // Set the title of the dialog after this->root has been created.
    // Ignored if this->root has not been created yet.
    //
    void setDialogTitle(const char *title);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDialog;
    }
};


#endif // _Dialog_h
