//////////////////////////////////////////////////////////////////////////////
// OpenFileDialog.h -						    //
//                                                                          //
// Definition for the OpenFileDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/OpenFileDialog.h,v 1.1 1999/03/24 15:17:34 gda Exp $
 */


#ifndef _OpenFileDialog_h
#define _OpenFileDialog_h


#include "defines.h"
#include "FileDialog.h"
#include "MBMainWindow.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassOpenFileDialog	"OpenFileDialog"

class Dialog;
class MBMainWindow;

//
// OpenFileDialog class definition:
//				
class OpenFileDialog : public FileDialog
{
    static boolean ClassInitialized;

    MBMainWindow *mbmw;

  protected:
    static String  DefaultResources[];

    virtual void okFileWork(const char *string); 

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
    OpenFileDialog(MBMainWindow *mbmw);

    //
    // Destructor:
    //
    ~OpenFileDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenFileDialog;
    }
};


#endif // _OpenFileDialog_h
