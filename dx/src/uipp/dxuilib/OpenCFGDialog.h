/*  Open Visualization Data Explorer Source File */




#ifndef _OpenCFGDialog_h
#define _OpenCFGDialog_h


#include "defines.h"
#include "FileDialog.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassOpenCFGDialog	"OpenCFGDialog"

class Network;

//
// OpenCFGDialog class definition:
//				
class OpenCFGDialog : public FileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];

    Network 	*network;

  protected:
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
    OpenCFGDialog(Widget parent, Network* net);


    //
    // Destructor:
    //
    ~OpenCFGDialog(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenCFGDialog;
    }
};


#endif // _OpenCFGDialog_h
