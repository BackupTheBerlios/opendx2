/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>






#ifndef _SaveAsDialog_h
#define _SaveAsDialog_h


#include "defines.h"
#include "SaveFileDialog.h"
#include "Application.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassSaveAsDialog	"SaveAsDialog"

class Dialog;
class Network;
class Command;

//
// SaveAsDialog class definition:
//				
class SaveAsDialog : public SaveFileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];

    Command *postCmd;

  protected:
    Network *network;
    static  void SaveNetwork(void *data);
    static  void CancelSaveNetwork(void *data);

    virtual void saveFile(const char *filename);
    virtual char *getDefaultFileName();

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
    SaveAsDialog(Widget        parent, Network *net);


    //
    // Destructor:
    //
    ~SaveAsDialog(){}

     void setPostCommand(Command *cmd)
     {
	this->postCmd = cmd;
     }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSaveAsDialog;
    }
};


#endif // _SaveAsDialog_h
