/////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/GARNewCommand.C,v 1.1 1999/04/05 13:33:37 gda Exp $
 */


#include "../base/UIConfig.h"
#include "../base/defines.h"
#include "GARNewCommand.h"
#include "GARMainWindow.h"
#include "GARApplication.h"

GARNewCommand::GARNewCommand(const char      *name,
		       CommandScope    *scope,
		       boolean		active,
		       GARMainWindow   *gmw,
		       Widget		dialogParent) :
    OptionalPreActionCommand(name, scope, active,
			     "Save Confirmation",
			     "Do you want to save the header?",
				dialogParent)
{
    this->gmw = gmw;
}

void   GARNewCommand::doPreAction()
{
    char    *fname = this->gmw->getFilename();

    if(fname)
    {
        if(this->gmw->saveGAR(fname))
            this->doIt(NULL);
    }
    else 
    {
        this->gmw->PostSaveAsDialog(this->gmw, this);
    }

}

boolean GARNewCommand::doIt(CommandInterface *)
{
    this->gmw->newGAR();
    return TRUE;
}


boolean GARNewCommand::needsConfirmation()
{
    return theGARApplication->isDirty();
}
