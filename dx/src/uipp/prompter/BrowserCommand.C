//////////////////////////////////////////////////////////////////////////////
// BrowserCommand.C -						    //
//                                                                          //
// BrowserCommand Class methods and other related functions/procedures.//
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/BrowserCommand.C,v 1.1 1999/04/05 13:33:32 gda Exp $
 */

#include <Xm/Xm.h>

#include "../base/NoUndoCommand.h"
#include "BrowserCommand.h"
#include "Browser.h"
#include "GARApplication.h"
#include "../base/ButtonInterface.h"

String BrowserCommand::DefaultResources[] =
{
        NULL
};

BrowserCommand::BrowserCommand(const char*   name,
                         CommandScope* scope,
                         boolean       active,
                         Browser* browser,
			 int option):NoUndoCommand(name,scope,active)
{
	this->browser = browser;	
	this->option = option;	
}

boolean BrowserCommand::doIt(CommandInterface *)
{
    Browser 	  *browser = this->browser;

    theGARApplication->setBusyCursor(TRUE);
    switch (this->option)
    {
	case Browser::PLACE_MARK:
	    browser->placeMark();
	    break;

	case Browser::CLEAR_MARK:
	    browser->clearMark();
	    break;

	case Browser::GOTO_MARK:
	    browser->gotoMark();
	    break;

	case Browser::FIRST_PAGE:
	    browser->firstPage();
	    break;

	case Browser::LAST_PAGE:
	    browser->lastPage();
	    break;

	case Browser::SEARCH:
	    browser->postSearchDialog();
	    break;

	case Browser::CLOSE:
	    browser->unmanage();
	    break;

	default:
	    ASSERT(FALSE);
    }
    theGARApplication->setBusyCursor(FALSE);
    return TRUE;
}
