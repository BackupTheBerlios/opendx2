//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
// 									    //
// SetInteractorNameDialog.h -					            // 
//                                                                          //
// Definition for the SetInteractorNameDialog class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetInteractorNameDialog.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 */


#ifndef _SetInteractorNameDialog_h
#define _SetInteractorNameDialog_h


#include "defines.h"
#include "SetNameDialog.h"


//
// Class name definition:
//
#define ClassSetInteractorNameDialog	"SetInteractorNameDialog"

class ControlPanel;

//
// SetInteractorNameDialog class definition:
//				
class SetInteractorNameDialog : public SetNameDialog
{
  private:
    //
    // Private member data:
    //
    static Boolean ClassInitialized;
    static String  DefaultResources[];

    ControlPanel *panel;

  protected:
    //
    // Protected member data:
    //

    virtual boolean saveText(const char *s);
    virtual const char *getText();

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

    virtual Widget createDialog (Widget parent);

  public:
    //
    // Constructor:
    //
    SetInteractorNameDialog(ControlPanel *panel);

    //
    // Destructor:
    //
    ~SetInteractorNameDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSetInteractorNameDialog;
    }
};


#endif // _SetInteractorNameDialog_h
