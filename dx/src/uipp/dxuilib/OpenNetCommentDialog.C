//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// OpenNetCommentDialog.C -						    //
//                                                                          //
// OpenNetCommentDialog Class methods and other related functions/procedures.    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/OpenNetCommentDialog.C,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */

#include "UIConfig.h"

#include <Xm/Xm.h>

#include "defines.h"
#include "Application.h"
#include "OpenNetCommentDialog.h"

boolean OpenNetCommentDialog::ClassInitialized = FALSE;

String OpenNetCommentDialog::DefaultResources[] =
{
       "*dialogTitle:		Application Comment..." ,
       "*nameLabel.labelString:	Application Comment:" ,
        //
        // These two must match what is in SetNetworkCommentDialog
        //
        "*editorText.columns:           45",  
        "*editorText.rows:              16",

	NULL
};

OpenNetCommentDialog::OpenNetCommentDialog(Widget parent)
			: TextEditDialog("openNetComment", parent, TRUE)
{
    this->dialogModality = XmDIALOG_APPLICATION_MODAL;

    if (NOT OpenNetCommentDialog::ClassInitialized)
    {
        OpenNetCommentDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

OpenNetCommentDialog::~OpenNetCommentDialog()
{
}

//
// Install the default resources for this class.
//
void OpenNetCommentDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget,
				OpenNetCommentDialog::DefaultResources);
    this->TextEditDialog::installDefaultResources( baseWidget);
}
