//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// OpenColormapDialog.C -						    //
//                                                                          //
// OpenColormapDialog Class methods and other related functions/procedures. //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/OpenColormapDialog.C,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */

#include <Xm/Xm.h>

#include "defines.h"
#include "Application.h"
#include "ColormapEditor.h"
#include "OpenColormapDialog.h"
#include "ErrorDialogManager.h"


boolean OpenColormapDialog::ClassInitialized = FALSE;

String OpenColormapDialog::DefaultResources[] =
{
        "*dialogTitle:     Open Colormap...",
        "*dirMask:         *.cm",
        NULL
};



void OpenColormapDialog::okFileWork(const char *string)
{
    boolean r;
    if (this->opening)
	r = this->editor->cmOpenFile((char*)string);
    else
	r = this->editor->cmSaveFile((char*)string);

    if (!r) {
	ErrorMessage("Cannot open file: %s.\n", string);
    }
}

OpenColormapDialog::OpenColormapDialog( Widget parent, 
                                       ColormapEditor* editor,
                                       boolean opening) : 
                       FileDialog("openColormapDialog", parent)
{

    this->editor = editor;
    this->opening = opening;

    //XMapRaised(XtDisplay(this->getRootWidget()),
    //           XtWindow(this->getRootWidget()));
 
    if (NOT OpenColormapDialog::ClassInitialized)
    {
        OpenColormapDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }

}

//
// Install the default resources for this class.
//
void OpenColormapDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, OpenColormapDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}
void OpenColormapDialog::setMode(boolean opening)
{
    this->opening = opening;
}
//
// Set the correct title 'Open/Close Colormap...' 
//
void OpenColormapDialog::manage()
{
    XmString   xmstring;

    if (opening)
	xmstring = XmStringCreateSimple("Open Colormap...");
    else
	xmstring = XmStringCreateSimple("Save Colormap...");

    XtVaSetValues(this->fsb,
		  XmNdialogTitle, xmstring,
		  NULL);
    XmStringFree(xmstring);

    this->FileDialog::manage();
}
