//////////////////////////////////////////////////////////////////////////////
// GARCommand.C -						    //
//                                                                          //
// GARCommand Class methods and other related functions/procedures.//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/GARCommand.C,v 1.1 1999/03/24 15:17:27 gda Exp $
 */

#include <Xm/Xm.h>
#if !defined(OS2)  && !defined(DXD_WIN)
#include <strstream.h>
#else
#include <strstrea.h>
#endif

#include "NoUndoCommand.h"
#include "GARApplication.h"
#include "GARCommand.h"
#include "GARMainWindow.h"
#include "ButtonInterface.h"
#include "OpenFileDialog.h"
#include "SADialog.h"
#include "CommentDialog.h"
#include "../base/WarningDialogManager.h"

String GARCommand::DefaultResources[] =
{
        NULL
};

GARCommand::GARCommand(const char*   name,
                         CommandScope* scope,
                         boolean       active,
                         GARMainWindow* gmw,
			 int option):NoUndoCommand(name,scope,active)
{
	this->gmw = gmw;	
	this->option = option;	
}

boolean GARCommand::doIt(CommandInterface *)
{
    Arg      	   wargs[8];
    GARMainWindow *gmw = this->gmw;
    char	  *fname;
    unsigned long mode;
    int dirty;
    strstream tmpstr;
#ifdef aviion
    strstream tmpstr2;
#endif

    switch (this->option)
    {
	case GARMainWindow::SAVE:
	    fname = gmw->getFilename();
	    gmw->saveGAR(fname);
	    delete fname;
	    break;
	case GARMainWindow::SAVE_AS:
	    gmw->save_as_fd->post();
	    break;
	case GARMainWindow::CLOSE_GAR:
	    gmw->unmanage();
	    break;
	case GARMainWindow::CLOSE:
	    break;
	case GARMainWindow::COMMENT:
	    gmw->comment_dialog->post();
	    break;
	case GARMainWindow::FULLGAR:
	    {
                dirty = theGARApplication->isDirty();
		if(!gmw->validateGAR(False)) return False;
		gmw->saveGAR(&tmpstr);
		theGARApplication->changeMode(GMW_FULL, &tmpstr);
                if (dirty) theGARApplication->setDirty();
	    }
	    break;
	case GARMainWindow::SIMPLIFY:
                dirty = theGARApplication->isDirty();
		if(!gmw->validateGAR(False)) return False;
		gmw->saveGAR(&tmpstr);
#ifdef aviion
		gmw->saveGAR(&tmpstr2);
#endif
		mode = gmw->getMode(&tmpstr);
		if(mode & GMW_FULL)
		{
		    WarningMessage("Sorry, the prompter can't be simplified");
		    break;
		}
// All these ifdefs because the aviion C++ libs don't seem to have seekg
#ifdef aviion
		theGARApplication->changeMode(mode, &tmpstr2);
#else
		tmpstr.clear();
		tmpstr.seekg(0, ios::beg);
		theGARApplication->changeMode(mode, &tmpstr);
#endif
                if (dirty) theGARApplication->setDirty();
	    break;

	default:
	    ASSERT(FALSE);
    }
    return TRUE;
}


