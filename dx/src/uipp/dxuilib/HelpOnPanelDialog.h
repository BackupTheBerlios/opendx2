//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// HelpOnPanelDialog.h -			        		 	    //
//                                                                          //
// Definition for the HelpOnPanelDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/HelpOnPanelDialog.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */


#ifndef _HelpOnPanelDialog_h
#define _HelpOnPanelDialog_h


#include "defines.h"
#include "SetPanelCommentDialog.h"

//
// Class name definition:
//
#define ClassHelpOnPanelDialog	"HelpOnPanelDialog"

class ControlPanel;

//
// HelpOnPanelDialog class definition:
//				

class HelpOnPanelDialog : public SetPanelCommentDialog
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
    static String  DefaultResources[];

    //
    // The title to be applied the newly managed dialog.
    // The returned string is freed by the caller (TextEditDialog::manage()).
    //
    virtual char *getDialogTitle();

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
    HelpOnPanelDialog(Widget parent, ControlPanel *cp);

    //
    // Destructor:
    //
    ~HelpOnPanelDialog();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassHelpOnPanelDialog;
    }
};


#endif // _HelpOnPanelDialog_h
