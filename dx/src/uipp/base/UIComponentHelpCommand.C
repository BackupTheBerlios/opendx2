//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/UIComponentHelpCommand.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#include <X11/cursorfont.h>
#include <Xm/Xm.h>

#include "UIComponentHelpCommand.h"
#include "UIComponent.h"


UIComponentHelpCommand::UIComponentHelpCommand(const char*   name,
					   CommandScope* scope,
					   boolean       active,
					   UIComponent*   component) :
	NoUndoCommand(name, scope, active)
{

    ASSERT(component);

    this->component = component;
}


boolean UIComponentHelpCommand::doIt(CommandInterface *ci)
{

    this->component->componentHelp();
    return TRUE;
}
