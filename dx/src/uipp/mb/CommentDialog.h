//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// CommentDialog.h -			        		 	    //
//                                                                          //
// Definition for the CommentDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/CommentDialog.h,v 1.1 1999/03/24 15:17:33 gda Exp $
 */


#ifndef _CommentDialog_h
#define _CommentDialog_h


#include "MBMainWindow.h"
#include "defines.h"
#include "TextEditDialog.h"

//
// Class name definition:
//
#define ClassCommentDialog	"CommentDialog"

class MBMainWindow;

//
// CommentDialog class definition:
//				

class CommentDialog : public TextEditDialog
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

    MBMainWindow		*mbmw;

    //
    // Get the the text that is to be installed in the text window.
    //
    virtual const char *getText();

    //
    // Save the text in the text window 
    //
    virtual boolean saveText(const char *);

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
    CommentDialog(Widget parent, boolean readonly, MBMainWindow *mbmw);

    //
    // Destructor:
    //
    ~CommentDialog();

    //
    // Clear the Text widget
    //
    virtual void clearText();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCommentDialog;
    }
};


#endif // _CommentDialog_h
