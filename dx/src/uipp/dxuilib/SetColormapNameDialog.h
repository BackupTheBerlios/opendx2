//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetColormapNameDialog.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 */



#ifndef _SetColormapNameDialog_h
#define _SetColormapNameDialog_h


#include "defines.h"
#include "SetNameDialog.h"


//
// Class name definition:
//
#define ClassSetColormapNameDialog	"SetColormapNameDialog"

class ColormapNode;

//
// SetColormapNameDialog class definition:
//				
class SetColormapNameDialog : public SetNameDialog
{
  private:
    //
    // Private member data:
    //
    ColormapNode 	*colormapNode;
    static boolean 	ClassInitialized;

  protected:
    //
    // Protected member data:
    //

    static String DefaultResources[];

    virtual const char *getText();
    virtual boolean saveText(const char *s);

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
    SetColormapNameDialog(Widget parent, ColormapNode *cn);

    //
    // Destructor:
    //
    ~SetColormapNameDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSetColormapNameDialog;
    }
};


#endif // _SetColormapNameDialog_h
