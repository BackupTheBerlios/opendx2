/*  Open Visualization Data Explorer Source File */



#ifndef _SADialog_h
#define _SADialog_h


#include "../base/defines.h"
#include "../base/SaveFileDialog.h"
//#include "GARMainWindow.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassSADialog	"SADialog"

class Dialog;
class Command;
class GARMainWindow;

//
// SADialog class definition:
//				
class SADialog : public SaveFileDialog
{
    static boolean ClassInitialized;

    GARMainWindow *gmw;
    Command	  *cmd;

  protected:
    static String  DefaultResources[];

    virtual void saveFile(const char *string); 

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
    SADialog(GARMainWindow *gmw);


    //
    // Destructor:
    //
    ~SADialog(){}

    void setPostCommand(Command *cmd);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSADialog;
    }
};


#endif // _SADialog_h
