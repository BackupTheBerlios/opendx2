//////////////////////////////////////////////////////////////////////////////
// ApplyFileDialog.C -						    //
//                                                                          //
// ApplyFileDialog Class methods and other related functions/procedures.  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/ApplyFileDialog.C,v 1.1 1999/03/24 15:17:22 gda Exp $
 */



#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/FileSB.h>
#include <Xm/SelectioB.h>

#include "defines.h"
#include "Application.h"
#include "ApplyFileDialog.h"
#include "ErrorDialogManager.h"



boolean ApplyFileDialog::ClassInitialized = FALSE;

String ApplyFileDialog::DefaultResources[] =
{
	"*helpLabelString:	Apply",
	"*dialogStyle:		DIALOG_MODELESS",
        NULL
};


//
// Constructor for instances of THIS class
// (see also the other constructor)
//
ApplyFileDialog::ApplyFileDialog(Widget parent) :
			FileDialog("applyFileDialog",parent)
{
    this->hasCommentButton = TRUE;	// Turn the help button into Apply
    if (NOT ApplyFileDialog::ClassInitialized)
    {
        ApplyFileDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

//
// Constructor for derived  classes (see also the other constructor)
//
ApplyFileDialog::ApplyFileDialog(const char *name, Widget parent) :
			FileDialog(name,parent)
{
    this->hasCommentButton = TRUE;	// Turn the help button into Apply
}
void ApplyFileDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, ApplyFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}


//
// Call super class and then set the dialog title and the dirMask resource. 
//
Widget ApplyFileDialog::createDialog(Widget parent)
{
    Widget w = this->FileDialog::createDialog(parent);
    // This apparently must be hardcoded.
    XtVaSetValues(this->fsb, XmNdialogStyle, XmDIALOG_MODELESS,NULL);
    return w;
}


//
// Do the ok work using this->okFileWork() with the currently selected file. 
//
void ApplyFileDialog::helpCallback(Dialog *d)
{
    char *string = this->getSelectedFileName();

    if (!string) {
        ModalErrorMessage(this->getRootWidget(),"A filename must be given");
	return;
    } 

    theApplication->setBusyCursor(TRUE);
    this->okFileWork(string);
    theApplication->setBusyCursor(FALSE);
    delete string; 
}

