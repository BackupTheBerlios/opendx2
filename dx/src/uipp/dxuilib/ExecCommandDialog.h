//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ExecCommandDialog.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 */


#ifndef _ExecCommandDialog_h
#define _ExecCommandDialog_h


#include "defines.h"
#include "SetNameDialog.h"


//
// Class name definition:
//
#define ClassExecCommandDialog	"ExecCommandDialog"

//
// ExecCommandDialog class definition:
//				
class ExecCommandDialog : public SetNameDialog
{
  private:
    //
    // Private member data:
    //
    static boolean 	ClassInitialized;

  protected:
    //
    // Protected member data:
    //
    char * lastCommand;

    static String DefaultResources[];

    void saveLastCommand(const char*);
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
    ExecCommandDialog(Widget parent);

    //
    // Destructor:
    //
    ~ExecCommandDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassExecCommandDialog;
    }
};


#endif // _ExecCommandDialog_h
