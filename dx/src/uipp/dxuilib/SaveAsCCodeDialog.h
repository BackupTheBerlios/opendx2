/*  Open Visualization Data Explorer Source File */





#ifndef _SaveAsCCodeDialog_h
#define _SaveAsCCodeDialog_h

#include "UIConfig.h"

#ifdef DXUI_DEVKIT
 
#include "defines.h"
#include "SaveFileDialog.h"
#include "Application.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassSaveAsCCodeDialog	"SaveAsCCodeDialog"

class Dialog;
class Network;
class Command;

//
// SaveAsCCodeDialog class definition:
//				
class SaveAsCCodeDialog : public SaveFileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];

  protected:
    Network *network;

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
    SaveAsCCodeDialog(Widget        parent, Network *net);

    //
    // Destructor:
    //
    ~SaveAsCCodeDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSaveAsCCodeDialog;
    }
};

#endif // DXUI_DEVKIT

#endif // _SaveAsCCodeDialog_h
