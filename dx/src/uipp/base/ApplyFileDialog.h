//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/ApplyFileDialog.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */



#ifndef _ApplyFileDialog_h
#define _ApplyFileDialog_h


#include "defines.h"
#include "FileDialog.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassApplyFileDialog	"ApplyFileDialog"


//
// ApplyFileDialog class definition:
//				
class ApplyFileDialog : public FileDialog
{
    static boolean ClassInitialized;

  protected:

    static String  DefaultResources[];

    //
    // Call super class and then set the dialog title and the dirMask resource. 
    //
    virtual Widget createDialog(Widget parent);

    //
    // Used to call this->okFileWork().
    //
    virtual void helpCallback(Dialog *d);

    //
    // Constructor: for derived classes
    //
    ApplyFileDialog(const char*   name, Widget        parent);

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
    ApplyFileDialog(Widget        parent);

    //
    // Destructor:
    //
    ~ApplyFileDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassApplyFileDialog;
    }
};

#endif // _ApplyFileDialog_h
