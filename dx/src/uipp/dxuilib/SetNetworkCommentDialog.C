//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// SetNetworkCommentDialog.C -						    //
//                                                                          //
// SetNetworkCommentDialog Class methods and other related functions/procedures.    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetNetworkCommentDialog.C,v 1.1 1999/03/24 15:17:47 gda Exp $
 *
 */

#include "UIConfig.h"
#include "defines.h"
#include "Application.h"
#include "SetNetworkCommentDialog.h"
#include "Network.h"

boolean SetNetworkCommentDialog::ClassInitialized = FALSE;

String SetNetworkCommentDialog::DefaultResources[] =
{
        "*dialogTitle:     		Application Comment...",
	"*nameLabel.labelString:	Application Comment:",
        // 
        // These two must match what is in OpenNetCommentDialog
        // 
        "*editorText.columns:           45",  
        "*editorText.rows:              16",
        NULL
};

SetNetworkCommentDialog::SetNetworkCommentDialog(const char *name,
				Widget parent, boolean readonly, Network *n) : 
			TextEditDialog(name,parent, readonly)
{
    this->network = n;
}
SetNetworkCommentDialog::SetNetworkCommentDialog(Widget parent,
				boolean readonly, Network *n) : 
			TextEditDialog("setNetworkComment",parent, readonly)
{
    this->network = n;

    if (NOT SetNetworkCommentDialog::ClassInitialized)
    {
        SetNetworkCommentDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetNetworkCommentDialog::~SetNetworkCommentDialog()
{
}

//
// Install the default resources for this class.
//
void SetNetworkCommentDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget,
				SetNetworkCommentDialog::DefaultResources);
    this->TextEditDialog::installDefaultResources( baseWidget);
}
//
// Get the the text that is to be edited. 
//
const char *SetNetworkCommentDialog::getText()
{
    return this->network->getNetworkComment();
}

//
// Save the given text. 
//
boolean SetNetworkCommentDialog::saveText(const char *s)
{
    this->network->setNetworkComment(s);
    return TRUE;
}

