/*  Open Visualization Data Explorer Source File */



#ifndef _ColormapNBinsDialog_h
#define _ColormapNBinsDialog_h


#include "defines.h"
#include "Dialog.h"

//
// Class name definition:
//
#define ClassColormapNBinsDialog	"ColormapNBinsDialog"

class ColormapEditor;

//
// ColormapNBinsDialog class definition:
//				

class ColormapNBinsDialog : public Dialog
{
  private:
    //
    // Private member data:
    //
    static Boolean ClassInitialized;

    boolean okCallback(Dialog *dialog);

  protected:
    //
    // Protected member data:
    //
    static String  DefaultResources[];

    ColormapEditor* editor;

    Widget label;
    Widget nbinsstepper;

    Widget createDialog(Widget);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

  public:

    virtual void post();

    //
    // Constructor:
    //
    ColormapNBinsDialog(Widget parent,ColormapEditor* editor);

    //
    // Destructor:
    //
    ~ColormapNBinsDialog();

    void        setStepper();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassColormapNBinsDialog;
    }
};


#endif // _ColormapNBinsDialog_h
