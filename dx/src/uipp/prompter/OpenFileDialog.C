//////////////////////////////////////////////////////////////////////////////
// OpenFileDialog.C -							    //
//                                                                          //
// OpenFileDialog Class methods and other related functions/procedures.     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/OpenFileDialog.C,v 1.1 1999/04/05 13:33:39 gda Exp $
 */


#include "../base/defines.h"
#include "../base/Strings.h"
#include "OpenFileDialog.h"
#include "../base/Application.h"
#include "../base/WarningDialogManager.h"
#include <Xm/Text.h>
#include <Xm/SelectioB.h>
#include "GARApplication.h"

boolean OpenFileDialog::ClassInitialized = FALSE;

String OpenFileDialog::DefaultResources[] =
{
        "*dirMask:	*.general",
        "*textColumns:	30",
	".dialogTitle:	Open a Data Prompter Header...",
        NULL
};

Widget OpenFileDialog::createDialog(Widget parent)
{
    Widget shell = this->FileDialog::createDialog(parent);
    return shell;
}

void OpenFileDialog::okFileWork(const char *filenm)
{
    ifstream *from = new ifstream(filenm);
#ifdef aviion
    ifstream *from2 = new ifstream(filenm);
#endif
    if(!from)
    {
	WarningMessage("File open failed.");
	return;
    }

    unsigned long mode = this->gmw->getMode(from);

#ifdef aviion
    theGARApplication->changeMode(mode, from2);
#else
    from->clear();
    from->seekg(0, ios::beg);
    theGARApplication->changeMode(mode, from);
#endif

    //
    // The main window may have been destroyed and re-created, so use
    // the one the application knows about.
    //
    theGARApplication->getMainWindow()->setFilename((char *)filenm);
}

OpenFileDialog::OpenFileDialog(GARMainWindow *gmw ) : 
                       FileDialog("openFileDialog", gmw->getRootWidget())
{
    this->gmw = gmw;
    this->hasCommentButton = False;

    //
    // Install the default resources for THIS class (not the derived classes)
    //
    if (NOT OpenFileDialog::ClassInitialized)
    {
	ASSERT(theApplication);
        OpenFileDialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

//
// Install the default resources for this class.
//
void OpenFileDialog::installDefaultResources(Widget baseWidget)
{
    this->setDefaultResources(baseWidget, OpenFileDialog::DefaultResources);
    this->FileDialog::installDefaultResources(baseWidget);
}

void OpenFileDialog::post()
{
    this->FileDialog::post();
}
