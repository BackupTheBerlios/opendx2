//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/RepeatingToggle.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */



#include "RepeatingToggle.h"
#include "Command.h"


RepeatingToggle::RepeatingToggle(Widget parent, char* name, 
    Command* command, boolean  state, const char *bubbleHelp):
	ToggleButtonInterface(parent, name, command, state, bubbleHelp)
{
}

void RepeatingToggle::activate()
{
    this->ToggleButtonInterface::activate();
    if (this->getState())
	this->command->execute();
}
