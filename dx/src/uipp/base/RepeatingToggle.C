/*  Open Visualization Data Explorer Source File */




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
