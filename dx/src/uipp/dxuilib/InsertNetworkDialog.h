//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// InsertNetworkDialog.h -						    //
//                                                                          //
// Definition for the InsertNetworkDialog class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/InsertNetworkDialog.h,v 1.1 1999/03/24 15:17:42 gda Exp $
 */



#ifndef _InsertNetworkDialog_h
#define _InsertNetworkDialog_h


#include "defines.h"
#include "FileDialog.h"
#include "OpenNetworkDialog.h"
#include "Application.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassInsertNetworkDialog	"InsertNetworkDialog"


//
// InsertNetworkDialog class definition:
//				
class InsertNetworkDialog: public OpenNetworkDialog 
{
    static boolean ClassInitialized;

  protected:

    static String  DefaultResources[];

    virtual void okFileWork(const char *string);

    //
    // For sub-classes of this dialog
    //
    InsertNetworkDialog(const char*   name, Widget        parent);

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
    InsertNetworkDialog(Widget        parent);


    //
    // Destructor:
    //
    ~InsertNetworkDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassInsertNetworkDialog;
    }
};


#endif // _InsertNetworkDialog_h
