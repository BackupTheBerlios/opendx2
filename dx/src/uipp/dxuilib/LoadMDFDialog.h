//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/LoadMDFDialog.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */



#ifndef _LoadMDFDialog_h
#define _LoadMDFDialog_h


#include "defines.h"
#include "FileDialog.h"

//#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassLoadMDFDialog	"LoadMDFDialog"

class DXApplication;

//
// LoadMDFDialog class definition:
//				
class LoadMDFDialog : public FileDialog
{
    static boolean ClassInitialized;
    static String  DefaultResources[];

  protected:
    virtual void okFileWork(const char *string);
    virtual void helpCallback(Dialog* dialog);
    DXApplication *dxApp;

    //
    // Constructor: For derived classes.
    //
    LoadMDFDialog(char *name, Widget        parent, DXApplication *app);

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
    LoadMDFDialog(Widget        parent, DXApplication *app);


    //
    // Destructor:
    //
    ~LoadMDFDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassLoadMDFDialog;
    }
};


#endif // _LoadMDFDialog_h
