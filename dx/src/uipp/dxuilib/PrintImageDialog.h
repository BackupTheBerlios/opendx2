//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/PrintImageDialog.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */

#ifndef _PrintImageDialog_h
#define _PrintImageDialog_h


#include "ImageFormatDialog.h"
#include <Xm/Xm.h>

//
// Class name definition:
//
#define ClassPrintImageDialog	"PrintImageDialog"


class Dialog;
class ImageNode;
class Command;
class CommandScope;
class List;

//
// PrintImageDialog class definition:
//				
class PrintImageDialog : public ImageFormatDialog
{
  private:

    static boolean ClassInitialized;
    static String  DefaultResources[];

    Widget		command;
    char*		command_str;

  protected:

    virtual Widget createControls(Widget parent );

    virtual boolean okCallback(Dialog *);
    virtual void    restoreCallback();

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    virtual void installDefaultResources(Widget baseWidget);

    virtual int  getRequiredHeight() { return 160; }

    enum {
	DirtyCommand   = 64
    };

  public:

    virtual void 		setCommandActivation();
    virtual const char *	getOutputFile();
    virtual boolean		isPrinting() { return TRUE; }

    //
    // Constructor:
    //
    PrintImageDialog(Widget parent, ImageNode* node, CommandScope* commandScope);

    //
    // Destructor:
    //
    ~PrintImageDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassPrintImageDialog; }
};


#endif // _PrintImageDialog_h
