/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>





#ifndef _PrintProgramFileDialog_h
#define _PrintProgramFileDialog_h

#include "UIConfig.h"

#include <Xm/Xm.h>

#include "defines.h"
#include "FileDialog.h"


//
// Class name definition:
//
#define ClassPrintProgramFileDialog	"PrintProgramFileDialog"

class Dialog;
class Network;
class Command;
class PrintProgramDialog;

//
// PrintProgramFileDialog class definition:
//				
class PrintProgramFileDialog : public FileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];


  protected:
    Network *network;
    PrintProgramDialog *printProgramDialog;

    virtual void okFileWork(const char *filename);
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
    PrintProgramFileDialog(PrintProgramDialog *ppd, Network *net);


    //
    // Destructor:
    //
    ~PrintProgramFileDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassPrintProgramFileDialog;
    }
};


#endif // _PrintProgramFileDialog_h
