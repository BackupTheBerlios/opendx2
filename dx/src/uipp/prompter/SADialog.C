//////////////////////////////////////////////////////////////////////////////
// SADialog.C -							    //
//                                                                          //
// SADialog Class methods and other related functions/procedures.     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/SADialog.C,v 1.1 1999/04/05 13:33:40 gda Exp $
 */


#include "../base/defines.h"
#include "../base/Strings.h"
#include "SADialog.h"
#include "GARNewCommand.h"
#include "GARMainWindow.h"
#include "../base/Application.h"
#include <Xm/Text.h>
#include <Xm/SelectioB.h>

static const char GenExtension[] = ".general";

boolean SADialog::ClassInitialized = FALSE;

String SADialog::DefaultResources[] =
{
        "*dirMask:	*.general",
        "*textColumns:	30",
	".dialogTitle:	Save a Data Prompter Header File...",
        NULL
};

SADialog::SADialog(GARMainWindow *gmw ) : 
                       SaveFileDialog("saveAsFileDialog", 
				      gmw->getRootWidget(),
				      GenExtension)
{
    this->gmw = gmw;
    this->hasCommentButton = False;
    this->cmd = NULL;

    //
    // Install the default resources for THIS class (not the derived classes)
    //
    if (NOT SADialog::ClassInitialized)
    {
	ASSERT(theApplication);
        SADialog::ClassInitialized = TRUE;
	this->installDefaultResources(theApplication->getRootWidget());
    }
}

//
// Install the default resources for this class.
//
void SADialog::installDefaultResources(Widget baseWidget)
{
    this->setDefaultResources(baseWidget, SADialog::DefaultResources);
    this->SaveFileDialog::installDefaultResources(baseWidget);
}
void SADialog::saveFile(const char *string)
{

    const char *ext;
    char *file;
    int len = strlen(GenExtension);

    file = new char[strlen(string) + len + 1];
    strcpy(file, string);

    // 
    // Build/add the extension
    // 
    ext = strrstr(file, GenExtension);
    if (!ext || (strlen(ext) != len))
	strcat(file,GenExtension);
    
    if(this->gmw->saveGAR(file))
	if(this->cmd)
	    ((GARNewCommand *)(this->cmd))->execute();
    this->cmd = NULL;
}

void SADialog::setPostCommand(Command *cmd)
{
    this->cmd = cmd;
}

