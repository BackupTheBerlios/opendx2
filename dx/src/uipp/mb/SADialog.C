/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "defines.h"
#include "Strings.h"
#include "SADialog.h"
#include "Application.h"
#include "MBNewCommand.h"
#include "MBMainWindow.h"
#include <Xm/Text.h>
#include <Xm/SelectioB.h>


boolean SADialog::ClassInitialized = FALSE;

String SADialog::DefaultResources[] =
{
        "*dirMask:      *.mb",
        "*textColumns:  30",
        "*dialogTitle:	Save a Module Builder file...",
        NULL
};

SADialog::SADialog(MBMainWindow *mbmw ) : 
                       SaveFileDialog("saveAsFileDialog", 
					mbmw->getRootWidget(),
					".mb")
{
    if (!SADialog::ClassInitialized)
    {
        this->setDefaultResources(theApplication->getRootWidget(),
                                  SADialog::DefaultResources);
        this->setDefaultResources(theApplication->getRootWidget(),
                                  SaveFileDialog::DefaultResources);
        this->setDefaultResources(theApplication->getRootWidget(),
                                  FileDialog::DefaultResources);
        SADialog::ClassInitialized = TRUE;
    }

    this->mbmw = mbmw;
    this->hasCommentButton = False;
    this->cmd = NULL;
}

void SADialog::saveFile(const char *string)
{
    if(this->mbmw->saveMB((char *)string))
	if(this->cmd)
	    ((MBNewCommand *)(this->cmd))->execute();
    this->cmd = NULL;
}

void SADialog::setPostCommand(Command *cmd)
{
    this->cmd = cmd;
}

