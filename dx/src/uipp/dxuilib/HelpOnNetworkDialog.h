//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// HelpOnNetworkDialog.h -			        		 	    //
//                                                                          //
// Definition for the HelpOnNetworkDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/HelpOnNetworkDialog.h,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */


#ifndef _HelpOnNetworkDialog_h
#define _HelpOnNetworkDialog_h


#include "defines.h"
#include "SetNetworkCommentDialog.h"

//
// Class name definition:
//
#define ClassHelpOnNetworkDialog	"HelpOnNetworkDialog"

class Network;

//
// HelpOnNetworkDialog class definition:
//				

class HelpOnNetworkDialog : public SetNetworkCommentDialog 
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
    HelpOnNetworkDialog(Widget parent, Network *n);

    //
    // Destructor:
    //
    ~HelpOnNetworkDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassHelpOnNetworkDialog;
    }
};


#endif // _HelpOnNetworkDialog_h
