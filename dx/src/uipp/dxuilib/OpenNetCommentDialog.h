//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// OpenNetCommentDialog.h -			        		 	    //
//                                                                          //
// Definition for the OpenNetCommentDialog class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/OpenNetCommentDialog.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */


#ifndef _OpenNetCommentDialog_h
#define _OpenNetCommentDialog_h


#include "defines.h"
#include "TextEditDialog.h"

//
// Class name definition:
//
#define ClassOpenNetCommentDialog	"OpenNetCommentDialog"

//
// OpenNetCommentDialog class definition:
//				

class OpenNetCommentDialog : public TextEditDialog
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

    char	*text; 

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
    OpenNetCommentDialog(Widget parent);

    //
    // Destructor:
    //
    ~OpenNetCommentDialog();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenNetCommentDialog;
    }
};


#endif // _OpenNetCommentDialog_h
