//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SetPanelNameDialog.C -						    //
//                                                                          //
// SetPanelNameDialog Class methods and other related functions/procedures. //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetPanelNameDialog.C,v 1.1 1999/03/24 15:17:47 gda Exp $
 */


#include "Xm/Form.h"
#include "Xm/Label.h"
#include "Xm/PushB.h"
#include "Xm/Separator.h"
#include "Xm/Text.h"

#include "defines.h"
#include "Strings.h"
#include "SetPanelNameDialog.h"

#include "Application.h"
#include "ControlPanel.h"
#include "Network.h"
#include "ErrorDialogManager.h"

boolean SetPanelNameDialog::ClassInitialized = FALSE;
String SetPanelNameDialog::DefaultResources[] =
{
    "*dialogTitle:               	Change Control Panel Name...", 
    "*nameLabel.labelString:            Control Panel Name:",
    NULL
};


SetPanelNameDialog::SetPanelNameDialog(Widget parent, ControlPanel *cp) :
    SetNameDialog("setPanelNameDialog", parent)
{
    this->controlPanel = cp;
  
    if (NOT SetPanelNameDialog::ClassInitialized)
    {
        SetPanelNameDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetPanelNameDialog::~SetPanelNameDialog()
{
}

//
// Install the default resources for this class.
//
void SetPanelNameDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget,
				SetPanelNameDialog::DefaultResources);
    this->SetNameDialog::installDefaultResources( baseWidget);
}

const char *SetPanelNameDialog::getText()
{
    return this->controlPanel->getPanelNameString();
}

boolean SetPanelNameDialog::saveText(const char *s)
{
    if (IsBlankString(s)) {
	ModalErrorMessage(this->getRootWidget(),
		"The name string cannot be blank.");
        return FALSE;
    } else {
	ControlPanel *panel = this->controlPanel;
    	panel->setPanelName(s);
    	panel->getNetwork()->setFileDirty();
    }

    return TRUE;
}

