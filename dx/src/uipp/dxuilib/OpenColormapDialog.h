//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/OpenColormapDialog.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 */



#ifndef _OpenColormapDialog_h
#define _OpenColormapDialog_h


#include "defines.h"
#include "FileDialog.h"
#include "Application.h"

#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassOpenColormapDialog	"OpenColormapDialog"

class Dialog;
class ColormapEditor;

//
// OpenColormapDialog class definition:
//				
class OpenColormapDialog : public FileDialog
{
  private:

    static boolean ClassInitialized;
    static String  DefaultResources[];
    ColormapEditor *editor;
    boolean	   opening;

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
    OpenColormapDialog( Widget          parent,
		       ColormapEditor* editor,
		       int             mode);


    //
    // Destructor:
    //
    ~OpenColormapDialog(){}

    void setMode(boolean openMode);

    //
    // Set the correct title 'Open/Close Colormap...'
    //
    virtual void manage();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenColormapDialog;
    }
};


#endif // _OpenColormapDialog_h
