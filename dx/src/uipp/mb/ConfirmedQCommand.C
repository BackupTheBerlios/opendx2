/////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ConfirmedQCommand.C -						    //
//                                                                          //
// ConfirmedQCommand Class methods and other related functions/procedures.//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/ConfirmedQCommand.C,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

#include "ConfirmedQCommand.h"
#include "MBApplication.h"
#include "MBMainWindow.h"
#include "QuitCommand.h"

#include <Xm/Xm.h>
#include <Xm/FileSB.h>
#include <Xm/SelectioB.h>

ConfirmedQCommand::ConfirmedQCommand(const char*   name,
                         CommandScope* scope,
                         boolean       active,
			 MBMainWindow  *mbmw,
			 MBApplication *app) :
    OptionalPreActionCommand(name, scope, active,
                             "Save Confirmation",
                             "Do you want to save the file?")
{
    this->application = app;
    this->mbmw = mbmw;

    //
    // We create this later, because creation uses a virtual Application
    // method.  If this class gets instanced in the Application's constructor
    // (typical) then the wrong virtual method will get called. 
    //
    this->command = NULL;

}

void   ConfirmedQCommand::doPreAction()
{
    char *fname = mbmw->getFilename();

    if(fname)
    {
	if(this->mbmw->saveMB(fname))
	    this->doIt(NULL);
    }
    else
	this->mbmw->PostSaveAsDialog(this->mbmw, this);

}

boolean ConfirmedQCommand::doIt(CommandInterface *ci)
{
    if (!this->command) { 

	// 
	// We can use a static buffer since there is only one application.
	// 
        static char *dialogQuestion = NULL;
        if (!dialogQuestion) {
            dialogQuestion = new char[256];
            sprintf(dialogQuestion,"Do you really want to quit %s?",
                                theApplication->getInformalName());
        }

        CommandScope *scope = (CommandScope*)this->scopeList.getElement(1);
        this->command = 
            new QuitCommand
                (this->application,
                 "quit",
                 scope,
                 TRUE,
                 "Quit",
                 dialogQuestion);
    }

    this->command->execute(ci);
    return TRUE;
}

boolean ConfirmedQCommand::needsConfirmation()
{
    return this->application->isDirty();
}

