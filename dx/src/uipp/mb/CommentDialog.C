//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// CommentDialog.C -						    //
//                                                                          //
// CommentDialog Class methods and other related functions/procedures.    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/CommentDialog.C,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

#include <Xm/Text.h>
#include "UIConfig.h"
#include "defines.h"
#include "Application.h"
#include "CommentDialog.h"

boolean CommentDialog::ClassInitialized = FALSE;

String CommentDialog::DefaultResources[] =
{
        "*dialogTitle:     		Comment...",
	"*nameLabel.labelString:	Comment",
        NULL
};

CommentDialog::CommentDialog(Widget parent,
				boolean readonly, MBMainWindow *mbmw) : 
				TextEditDialog("commentD",parent, readonly)
{
    this->mbmw = mbmw;

    //
    // Install the default resources for THIS class (not the derived classes)
    //
    if (NOT CommentDialog::ClassInitialized)
    {
	ASSERT(theApplication);
        CommentDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

CommentDialog::~CommentDialog()
{
}

//
// Install the default resources for this class.
//
void CommentDialog::installDefaultResources(Widget baseWidget)
{
    this->setDefaultResources(baseWidget, CommentDialog::DefaultResources);
    this->TextEditDialog::installDefaultResources(baseWidget);
}
//
// Get the the text that is to be edited. 
//
const char *CommentDialog::getText()
{
    return this->mbmw->getCommentText();
}

//
// Save the given text. 
//
boolean CommentDialog::saveText(const char *s)
{
    this->mbmw->setCommentText((char *)s);
    return True;
}

//
// Clear the given text. 
//
void CommentDialog::clearText()
{
    if(this->editorText)
	XmTextSetString(this->editorText, "");
}
