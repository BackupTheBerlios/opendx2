//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetImageNameDialog.h,v 1.1 1999/03/24 15:17:47 gda Exp $
 */


#ifndef _SetImageNameDialog_h
#define _SetImageNameDialog_h


#include "defines.h"
#include "SetNameDialog.h"


//
// Class name definition:
//
#define ClassSetImageNameDialog	"SetImageNameDialog"

class ImageWindow;

//
// SetImageNameDialog class definition:
//				
class SetImageNameDialog : public SetNameDialog
{
  private:
    //
    // Private member data:
    //
    ImageWindow		*imageWindow;
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
    SetImageNameDialog(ImageWindow *iw);

    //
    // Destructor:
    //
    ~SetImageNameDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSetImageNameDialog;
    }
};


#endif // _SetImageNameDialog_h
