//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// HelpOnPanelDialog.C -						    //
//                                                                          //
// HelpOnPanelDialog Class methods and other related functions/procedures.    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/HelpOnPanelDialog.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 *
 */

#include "Strings.h"
#include "UIConfig.h"
#include "defines.h"
#include "Application.h"
#include "HelpOnPanelDialog.h"
#include "ControlPanel.h"

boolean HelpOnPanelDialog::ClassInitialized = FALSE;

String HelpOnPanelDialog::DefaultResources[] =
{
        "*dialogTitle:     		Help on Control Panel...",
        NULL
};

HelpOnPanelDialog::HelpOnPanelDialog(Widget parent, ControlPanel *cp) : 
				SetPanelCommentDialog("helpOnPanel",
				parent, TRUE, cp)
{
    if (NOT HelpOnPanelDialog::ClassInitialized)
    {
        HelpOnPanelDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

HelpOnPanelDialog::~HelpOnPanelDialog()
{
}
char *HelpOnPanelDialog::getDialogTitle()
{
    const char *title = this->controlPanel->getWindowTitle();
    char *dialogTitle = NULL;

    if (title) {
        int len = STRLEN(title) + strlen(" Help On Control Panel...") + 16;
        dialogTitle = new char[len];
        sprintf(dialogTitle,"Help On %s...",title);
    }
    return dialogTitle;
}


//
// Install the default resources for this class.
//
void HelpOnPanelDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, HelpOnPanelDialog::DefaultResources);
    this->SetPanelCommentDialog::installDefaultResources( baseWidget);
}
