//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// DescrDialog.h -							    //
//                                                                          //
// Definition for the DescrDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/DescrDialog.h,v 1.1 1999/03/24 15:17:39 gda Exp $
 */


#ifndef _DescrDialog_h
#define _DescrDialog_h


#include "defines.h"
#include "Dialog.h"


//
// Class name definition:
//
#define ClassDescrDialog	"DescrDialog"

class Node;

//
// DescrDialog class definition:
//				
class DescrDialog : public Dialog
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    Node *node;

    static boolean ClassInitialized;
    static String  DefaultResources[];

    Widget createDialog(Widget parent);


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
    DescrDialog(Widget parent, Node *n);

    //
    // Destructor:
    //
    ~DescrDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDescrDialog;
    }
};


#endif // _DescrDialog_h
