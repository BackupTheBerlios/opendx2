//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/FileSelectorDialog.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 */



#ifndef _FileSelectorDialog_h
#define _FileSelectorDialog_h


#include "defines.h"
#include "ApplyFileDialog.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassFileSelectorDialog	"FileSelectorDialog"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
extern "C" void FileSelectorDialog_FilterChangeCB(Widget, XtPointer, XtPointer);

class FileSelectorInstance;

//
// FileSelectorDialog class definition:
//				
class FileSelectorDialog : public ApplyFileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];

  protected:

    FileSelectorInstance *fsInstance;

    //
    // Capture and save a filter change with the instance.
    //
    friend void FileSelectorDialog_FilterChangeCB(Widget, 
						XtPointer, XtPointer);
    void filterChangeCallback();

    //
    // Call super class and then set the dialog title and the dirMask resource. 
    //
    virtual Widget createDialog(Widget parent);

    //
    // Set the output value of  the interactor to the given string.
    //
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
    FileSelectorDialog(Widget        parent, FileSelectorInstance *fsi);

    //
    // Destructor:
    //
    ~FileSelectorDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassFileSelectorDialog;
    }
};

#endif // _FileSelectorDialog_h
