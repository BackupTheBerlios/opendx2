//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// HelpOnNetworkDialog.C -						    //
//                                                                          //
// HelpOnNetworkDialog Class methods and other related functions/procedures.    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/HelpOnNetworkDialog.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */

#include "UIConfig.h"
#include "defines.h"
#include "Application.h"
#include "HelpOnNetworkDialog.h"

boolean HelpOnNetworkDialog::ClassInitialized = FALSE;

String HelpOnNetworkDialog::DefaultResources[] =
{
        "*dialogTitle:     		Application Comment...",
        NULL
};

HelpOnNetworkDialog::HelpOnNetworkDialog(Widget parent, Network *n) : 
				SetNetworkCommentDialog("helpOnNetworkDialog",
				parent,TRUE,n)
{
    if (NOT HelpOnNetworkDialog::ClassInitialized)
    {
        HelpOnNetworkDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

HelpOnNetworkDialog::~HelpOnNetworkDialog()
{
}

//
// Install the default resources for this class.
//
void HelpOnNetworkDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget,HelpOnNetworkDialog::DefaultResources);
    this->SetNetworkCommentDialog::installDefaultResources( baseWidget);
}
