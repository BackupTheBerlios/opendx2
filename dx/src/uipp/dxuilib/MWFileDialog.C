//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// MWFileDialog.C -							    //
//                                                                          //
// MWFileDialog Class methods and other related functions/procedures.	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/MWFileDialog.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#include "defines.h"
#include "MWFileDialog.h"
#include "Application.h"
#include "MsgWin.h"
#include "ToggleButtonInterface.h"


boolean MWFileDialog::ClassInitialized = FALSE;

String MWFileDialog::DefaultResources[] =
{
    "*dirMask:         *.log",
    NULL
};


void MWFileDialog::okFileWork(const char *file)
{
    if (this->log)
	this->messageWindow->log(file);
    else
	this->messageWindow->save(file);
}

void MWFileDialog::cancelCallback(Dialog *d)
{
    MWFileDialog *fd = (MWFileDialog*)d;

    fd->messageWindow->getLogInterface()->setState(FALSE);
    this->FileDialog::cancelCallback(d);
}

MWFileDialog::MWFileDialog(Widget parent, MsgWin *messageWindow):
    FileDialog("mwFileDialog", parent)
{
    this->log = TRUE;
    this->messageWindow = messageWindow;

    if (NOT MWFileDialog::ClassInitialized)
    {
        MWFileDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}
//
// Install the default resources for this class.
//
void MWFileDialog::installDefaultResources(Widget  baseWidget)
{
    this->setDefaultResources(baseWidget, MWFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources( baseWidget);
}

//
// True means that this will make a log request next, false means a save
//

void MWFileDialog::postAs(boolean log)
{
    this->log = log;

    this->FileDialog::post();

    XmString title = XmStringCreateSimple(log? "Log...": "Save As...");
    XtVaSetValues(this->getFileSelectionBox(),
		  XmNdialogTitle, title,
		  NULL);
    XmStringFree(title);
}
