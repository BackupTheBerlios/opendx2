//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/LoadMDFDialog.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */



#include "defines.h"
#include "DXApplication.h"
#include "LoadMDFDialog.h"
#include "MacroDefinition.h"


boolean LoadMDFDialog::ClassInitialized = FALSE;

String LoadMDFDialog::DefaultResources[] =
{
        "*dialogTitle:     Load Module Description...",
        "*.dirMask:         *.mdf",
        "*helpLabelString: Comments",
        NULL
};

LoadMDFDialog::LoadMDFDialog(Widget parent, DXApplication *ap) : 
                       FileDialog("loadMDFDialog", parent)
{
    this->hasCommentButton = FALSE;
    this->dxApp = ap;

    if (NOT LoadMDFDialog::ClassInitialized)
    {
        LoadMDFDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}
LoadMDFDialog::LoadMDFDialog(char *name, Widget parent, DXApplication *ap) : 
                       FileDialog(name, parent)
{
    this->hasCommentButton = FALSE;
    this->dxApp = ap;
}

//
// Install the default resources for this class.
//
void LoadMDFDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, LoadMDFDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}

void LoadMDFDialog::helpCallback(Dialog* dialog)
{
    LoadMDFDialog *loadMacroDialog = (LoadMDFDialog *) dialog;
    printf("help callback \n");
}

void LoadMDFDialog::okFileWork(const char *string)
{
    Dictionary d;
    this->dxApp->loadUDF(string, &d, TRUE);
}

