/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "HelpOnNetworkDialog.h"

boolean HelpOnNetworkDialog::ClassInitialized = FALSE;

//String HelpOnNetworkDialog::DefaultResources[] =
//{
//        "*dialogTitle:     		Application Comment...",
//        NULL
//};

HelpOnNetworkDialog::HelpOnNetworkDialog(Network *n) : 
				SetNetworkCommentDialog("helpOnNetworkDialog",
				TRUE,n)
{
    if (NOT HelpOnNetworkDialog::ClassInitialized)
    {
        HelpOnNetworkDialog::ClassInitialized = TRUE;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

HelpOnNetworkDialog::~HelpOnNetworkDialog()
{
}

//
// Install the default resources for this class.
//
//void HelpOnNetworkDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,HelpOnNetworkDialog::DefaultResources);
//    this->SetNetworkCommentDialog::installDefaultResources( baseWidget);
//}
