/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _SADialog_h
#define _SADialog_h


#include "defines.h"
#include "SaveFileDialog.h"
//#include "MBMainWindow.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassSADialog	"SADialog"

class Dialog;
class Command;
class MBMainWindow;

//
// SADialog class definition:
//				
class SADialog : public SaveFileDialog
{
    static boolean ClassInitialized;

    MBMainWindow *mbmw;
    Command     *cmd;

  protected:
    static String  DefaultResources[];

    virtual void saveFile(const char *string); 

  public:
    //
    // Constructor:
    //
    SADialog(MBMainWindow *mbmw);

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
