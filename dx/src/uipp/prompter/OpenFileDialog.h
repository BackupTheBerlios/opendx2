//////////////////////////////////////////////////////////////////////////////
// OpenFileDialog.h -						    //
//                                                                          //
// Definition for the OpenFileDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/OpenFileDialog.h,v 1.1 1999/04/05 13:33:48 gda Exp $
 */


#ifndef _OpenFileDialog_h
#define _OpenFileDialog_h


#include "../base/defines.h"
#include "../base/FileDialog.h"
#include "GARMainWindow.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassOpenFileDialog	"OpenFileDialog"

class Dialog;
class GARMainWindow;

//
// OpenFileDialog class definition:
//				
class OpenFileDialog : public FileDialog
{
    static boolean ClassInitialized;

    GARMainWindow *gmw;

  protected:
    static String  DefaultResources[];

    virtual void okFileWork(const char *string); 
    virtual Widget createDialog(Widget parent);

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
    OpenFileDialog(GARMainWindow *gmw);


    //
    // Destructor:
    //
    ~OpenFileDialog(){}

    virtual void post();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenFileDialog;
    }
};


#endif // _OpenFileDialog_h
