/////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/MBNewCommand.C,v 1.1 1999/03/24 15:17:33 gda Exp $
 */


#include "../base/UIConfig.h"
#include "../base/defines.h"
#include "MBNewCommand.h"
#include "MBMainWindow.h"
#include "MBApplication.h"

MBNewCommand::MBNewCommand(const char      *name,
		       CommandScope    *scope,
		       boolean		active,
		       MBMainWindow   *mbmw,
		       Widget		dialogParent) :
    OptionalPreActionCommand(name, scope, active,
			     "Save Confirmation",
			     "Do you want to save the file?",
				dialogParent)
{
    this->mbmw = mbmw;
}

void   MBNewCommand::doPreAction()
{
    char    *fname = this->mbmw->getFilename();

    if(fname)
    {
        if(this->mbmw->saveMB(fname))
            this->doIt(NULL);
    }
    else 
    {
        this->mbmw->PostSaveAsDialog(this->mbmw, this);
    }

}

boolean MBNewCommand::doIt(CommandInterface *ci)
{
    this->mbmw->newMB(TRUE);
    return TRUE;
}


boolean MBNewCommand::needsConfirmation()
{
    return theMBApplication->isDirty();
}
