//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/OpenCFGDialog.C,v 1.1 1999/03/24 15:17:44 gda Exp $
 */



#include "defines.h"
#include "Network.h"
#include "OpenCFGDialog.h"
#include "ControlPanel.h"
#include "Application.h"
#include "ErrorDialogManager.h"


boolean OpenCFGDialog::ClassInitialized = FALSE;

String OpenCFGDialog::DefaultResources[] =
{
        "*dialogTitle:         Open Configuration...",
        "*dirMask:         *.cfg",
        NULL
};

void OpenCFGDialog::okFileWork(const char *string)
{
    boolean  result;
    char *op;

    result = this->network->openCfgFile(string, TRUE);
    op = "reading";

    if(NOT result)
        ErrorMessage("Error while %s configuration file %s", op, string);

}

OpenCFGDialog::OpenCFGDialog(Widget parent, Network *net) : 
                       FileDialog("openCFGDialog", parent)
{

    this->network = net;
    this->hasCommentButton = FALSE;

    if (NOT OpenCFGDialog::ClassInitialized)
    {
        OpenCFGDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }

}

//
// Install the default resources for this class.
//
void OpenCFGDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, OpenCFGDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}
