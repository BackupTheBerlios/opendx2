//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// HelpOnContextCommand.C -						    //
//                                                                          //
// HelpOnContextCommand Class methods and other related			    //
// functions/procedures.						    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/HelpOnContextCommand.C,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#include <X11/cursorfont.h>
#include <Xm/Xm.h>

#include "HelpOnContextCommand.h"
#include "Application.h"
#include "MainWindow.h"


boolean HelpOnContextCommand::HelpOnContextCommandClassInitialized = FALSE;
Cursor  HelpOnContextCommand::HelpCursor = NUL(Cursor);


HelpOnContextCommand::HelpOnContextCommand(const char*   name,
					   CommandScope* scope,
					   boolean       active,
					   MainWindow*   window) :
	NoUndoCommand(name, scope, active)
{
    MainWindowHelpCallbackStruct callData;

    ASSERT(window);

    if (NOT HelpOnContextCommand::HelpOnContextCommandClassInitialized)
    {
	ASSERT(theApplication);
	HelpOnContextCommand::HelpCursor =
	    XCreateFontCursor(theApplication->getDisplay(), XC_question_arrow);

	HelpOnContextCommand::HelpOnContextCommandClassInitialized = TRUE;
    }

    this->window = window;
}


boolean HelpOnContextCommand::doIt(CommandInterface *ci)
{
    Widget                       widget;
    MainWindowHelpCallbackStruct callData;

    widget =
	XmTrackingLocate
	    (this->window->getMainWindow(), 
	     HelpOnContextCommand::HelpCursor,
	     False);

    XSync(theApplication->getDisplay(), False);

    while (widget)
    {
	if (XtHasCallbacks(widget, XmNhelpCallback) == XtCallbackHasSome)
	{
	    callData.reason = DxCR_HELP;
	    callData.event  = NULL;
	    callData.widget = widget;
	    XtCallCallbacks
		(widget,
		 XmNhelpCallback,
		 (XtPointer)&callData);
	    break;
	}
	else
	{
	    widget = XtParent(widget);
	}
    }

    return TRUE;
}


