/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#ifndef _MWFileDialog_h
#define _MWFileDialog_h


#include "defines.h"
#include "FileDialog.h"


//
// Class name definition:
//
#define ClassMWFileDialog	"MWFileDialog"

class MsgWin;

//
// MWFileDialog class definition:
//				
class MWFileDialog : public FileDialog
{
  private:
    //
    // Private member data:
    //
    static boolean ClassInitialized;

  protected:
    //
    // Protected member data:
    //
    MsgWin *messageWindow;
    virtual void okFileWork(const char *string);
    virtual void cancelCallback(Dialog *d);

    boolean log;
    static String  DefaultResources[];

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
    MWFileDialog(Widget parent, MsgWin *messageWindow);

    
    //
    // Destructor:
    //
    ~MWFileDialog(){}

    //
    // True means that this will make a log request next, false means a save
    //
    void postAs(boolean log);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMWFileDialog;
    }
};


#endif // _MWFileDialog_h
