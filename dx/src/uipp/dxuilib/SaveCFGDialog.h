/*  Open Visualization Data Explorer Source File */




#ifndef _SaveCFGDialog_h
#define _SaveCFGDialog_h


#include "UIConfig.h"

#include <Xm/Xm.h>

#include "defines.h"
#include "SaveFileDialog.h"


//
// Class name definition:
//
#define ClassSaveCFGDialog	"SaveCFGDialog"

class Network;

//
// SaveCFGDialog class definition:
//				
class SaveCFGDialog : public SaveFileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];

    Network	*network;

  protected:
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
    SaveCFGDialog(Widget parent, Network *net);


    //
    // Destructor:
    //
    ~SaveCFGDialog(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSaveCFGDialog;
    }
};


#endif // _SaveCFGDialog_h
