/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#ifndef _FilenameSelectDialog_h
#define _FilenameSelectDialog_h


#include "../base/defines.h"
#include "../base/FileDialog.h"
#include "GARMainWindow.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassFilenameSelectDialog	"FilenameSelectDialog"

class Dialog;
class GARMainWindow;

//
// FilenameSelectDialog class definition:
//				
class FilenameSelectDialog : public FileDialog
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
    FilenameSelectDialog(GARMainWindow *gmw);


    //
    // Destructor:
    //
    ~FilenameSelectDialog(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassFilenameSelectDialog;
    }
};


#endif // _FilenameSelectDialog_h
