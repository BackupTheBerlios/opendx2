//////////////////////////////////////////////////////////////////////////////
// OpenFileDialog.C -							    //
//                                                                          //
// OpenFileDialog Class methods and other related functions/procedures.     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/OpenFileDialog.C,v 1.1 1999/03/24 15:17:34 gda Exp $
 */


#include "defines.h"
#include "Strings.h"
#include "OpenFileDialog.h"
#include "Application.h"
#include <Xm/Text.h>
#include <Xm/SelectioB.h>


boolean OpenFileDialog::ClassInitialized = FALSE;

String OpenFileDialog::DefaultResources[] =
{
        "*dirMask:         *.mb",
        "*textColumns:     30",
        "*dialogTitle:     Open a Module Builder file...",
        NULL
};

OpenFileDialog::OpenFileDialog(MBMainWindow *mbmw ) : 
                       FileDialog("openFileDialog", mbmw->getRootWidget())
{
    //
    // Install the default resources for THIS class (not the derived classes)
    //
    if (NOT OpenFileDialog::ClassInitialized)
    {
	ASSERT(theApplication);
        OpenFileDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
    this->mbmw = mbmw;
    this->hasCommentButton = False;
}

//
// Install the default resources for this class.
//
void OpenFileDialog::installDefaultResources(Widget baseWidget)
{
    this->setDefaultResources(baseWidget, OpenFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources(baseWidget);
}

void OpenFileDialog::okFileWork(const char *string)
{
    this->mbmw->openMB((char *)string);
}

