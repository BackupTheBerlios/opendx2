//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/ImageFileDialog.C,v 1.1 1999/03/24 15:17:41 gda Exp $
 */


#include <Xm/Xm.h>

#include "defines.h"
#include "ImageFileDialog.h"
#include "Application.h"
#include "Strings.h"
#include "ErrorDialogManager.h"
#include "SaveImageDialog.h"

String ImageFileDialog::DefaultResources[] = {
    ".dialogStyle:	XmDIALOG_MODELESS",
    "*dialogTitle:	Save Image to File...",
    NUL(char*)
};

boolean ImageFileDialog::ClassInitialized = FALSE;

ImageFileDialog::ImageFileDialog(Widget parent, SaveImageDialog* dialog) :
                       FileDialog("imageFileSelector", parent)
{
    this->sid = dialog;
}

void ImageFileDialog::installDefaultResources(Widget  baseWidget)
{
    if (ImageFileDialog::ClassInitialized) return ;
    ImageFileDialog::ClassInitialized = TRUE;
    this->setDefaultResources(baseWidget, ImageFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}

void ImageFileDialog::okFileWork(const char *string)
{
    this->sid->setFilename(string, FALSE);
    this->sid->setCommandActivation();
}

void ImageFileDialog::cancelCallback (Dialog *)
{
    this->unmanage();
    this->sid->setCommandActivation();
}

Widget ImageFileDialog::createDialog (Widget parent)
{
    this->installDefaultResources (theApplication->getRootWidget());
    return this->FileDialog::createDialog(parent);
}
