/*  Open Visualization Data Explorer Source File */




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

