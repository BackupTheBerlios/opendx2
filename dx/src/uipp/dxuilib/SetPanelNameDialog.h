///////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetPanelNameDialog.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 */


#ifndef _SetPanelNameDialog_h
#define _SetPanelNameDialog_h


#include "defines.h"
#include "SetNameDialog.h"


//
// Class name definition:
//
#define ClassSetPanelNameDialog	"SetPanelNameDialog"

class ControlPanel;

//
// SetPanelNameDialog class definition:
//				
class SetPanelNameDialog : public SetNameDialog
{
  private:
    //
    // Private member data:
    //
    ControlPanel	*controlPanel;
    static boolean 	ClassInitialized;

  protected:
    //
    // Protected member data:
    //

    static String DefaultResources[];

    virtual const char *getText();
    virtual boolean saveText(const char *s);

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
    SetPanelNameDialog(Widget parent, ControlPanel *cp);

    //
    // Destructor:
    //
    ~SetPanelNameDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSetPanelNameDialog;
    }
};


#endif // _SetPanelNameDialog_h
