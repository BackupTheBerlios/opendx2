//////////////////////////////////////////////////////////////////////////////
// FilenameSelectDialog.C -						    //
//                                                                          //
// FilenameSelectDialog Class methods and other related functions/procedures.  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/FilenameSelectDialog.C,v 1.1 1999/04/05 13:33:35 gda Exp $
 */

#include "../base/defines.h"
#include "../base/Strings.h"
#include "FilenameSelectDialog.h"
#include "../base/Application.h"
#include <Xm/Text.h>
#include <Xm/SelectioB.h>
#include <Xm/FileSB.h>


boolean FilenameSelectDialog::ClassInitialized = FALSE;

String FilenameSelectDialog::DefaultResources[] =
{
        "*dirMask:		*",
        "*textColumns:		30",
	"*dialogTitle:		Data File Name...",
        NULL
};

Widget FilenameSelectDialog::createDialog(Widget parent)
{
    Widget shell = this->FileDialog::createDialog(parent);
    // FIXME: we should have ModelessFileDialog class 
    //        (see ../base/ApplyFileDialog)
    XtVaSetValues(this->fsb, XmNdialogStyle, XmDIALOG_MODELESS, NULL);
    return shell;
}

void FilenameSelectDialog::okFileWork(const char *string)
{
    XmTextSetString(this->gmw->getFileTextWid(), (char *)string);
    XmTextShowPosition(this->gmw->getFileTextWid(), STRLEN((char *)string));
}

FilenameSelectDialog::FilenameSelectDialog(GARMainWindow *gmw ) : 
                       FileDialog("filenameSelectDialog", gmw->getRootWidget())
{
    this->gmw = gmw;
    this->hasCommentButton = FALSE;

    //
    // Install the default resources for THIS class (not the derived classes)
    //
    if (NOT FilenameSelectDialog::ClassInitialized)
    {
	ASSERT(theApplication);
        FilenameSelectDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}


//
// Install the default resources for this class.
//
void FilenameSelectDialog::installDefaultResources(Widget baseWidget)
{
    this->setDefaultResources(baseWidget, 
			FilenameSelectDialog::DefaultResources);
    this->FileDialog::installDefaultResources(baseWidget);
}

