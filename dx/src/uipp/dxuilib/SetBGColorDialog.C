//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// SetBGColorDialog.C -							    //
//                                                                          //
// SetBGColorDialog Class methods and other related functions/procedures.   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/SetBGColorDialog.C,v 1.1 1999/03/24 15:17:47 gda Exp $
 */



#include "defines.h"
#include "Strings.h"
#include "SetBGColorDialog.h"
#include "ImageWindow.h"
#include "Application.h"

boolean SetBGColorDialog::ClassInitialized = FALSE;
String  SetBGColorDialog::DefaultResources[] =
{
    "*dialogTitle:                      Change Background Color...",
    "*nameLabel.labelString:            Background Color:",
    NULL
};
SetBGColorDialog::SetBGColorDialog(ImageWindow *image) :
    SetNameDialog("setBGColorDialog", image->getRootWidget())
{
    this->imageWindow = image;

    if (NOT SetBGColorDialog::ClassInitialized)
    {
        SetBGColorDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetBGColorDialog::~SetBGColorDialog()
{
}


//
// Install the default resources for this class.
//
void SetBGColorDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, SetBGColorDialog::DefaultResources);
    this->SetNameDialog::installDefaultResources( baseWidget);
}
boolean SetBGColorDialog::saveText(const char *s)
{
    if (s && !IsBlankString(s))
	this->imageWindow->setBackgroundColor(s);
    else
	this->imageWindow->setBackgroundColor(NULL);

    return TRUE;
}

const char *SetBGColorDialog::getText()
{
    return this->imageWindow->getBackgroundColor();
}
