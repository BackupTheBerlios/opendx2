/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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
