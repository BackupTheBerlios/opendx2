/*  Open Visualization Data Explorer Source File */



#include "UndoCommand.h"
#include "ListIterator.h"
#include "CommandScope.h"


UndoCommand::UndoCommand(const char*   name,
			 CommandScope* scope): NoUndoCommand(name, scope, FALSE)
{
    ASSERT(scope);

    //
    // Register this command as this scope's undo command.
    //
    scope->setUndoCommand(this);
}


boolean UndoCommand::doIt(CommandInterface *ci)
{
    ListIterator  scopeIterator(this->scopeList);
    CommandScope* scope;
    Command*      command;

    while (scope = (CommandScope*)scopeIterator.getNext())
    {
	if (command = scope->getLastCommand())
	{
	    if (command->undo())
	    {
		scope->setLastCommand(NUL(Command*));
	    }
	    else
	    {
		return FALSE;
	    }
	}
    }

    return TRUE;
}


boolean UndoCommand::registerScope(CommandScope* scope)
{
    ASSERT(scope);

    if (Command::registerScope(scope))
    {
	scope->setUndoCommand(this);
	return TRUE;
    }
    else
    {
	return FALSE;
    }
}


boolean UndoCommand::unregisterScope(CommandScope* scope)
{
    ASSERT(scope);

    if (Command::unregisterScope(scope))
    {
	scope->setUndoCommand(NUL(Command*));
	return TRUE;
    }
    else
    {
	return FALSE;
    }
}


