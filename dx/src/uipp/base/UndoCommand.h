/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _UndoCommand_h
#define _UndoCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassUndoCommand	"UndoCommand"


//
// UndoCommand class definition:
//				
class UndoCommand : public NoUndoCommand
{
  protected:
    //
    // 
    //
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    UndoCommand(const char*   name,
		CommandScope* scope);

    //
    // Destructor:
    //
    ~UndoCommand(){}

    //
    // Override of superclass registerScope():
    //   Calls superclass function() then registers 
    //   this command as the scope's undo command.
    //
    boolean registerScope(CommandScope* scope);

    //
    // Override of superclass registerScope():
    //   Calls superclass function() then unregisters 
    //   this command as the scope's undo command.
    //
    boolean unregisterScope(CommandScope* scope);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassUndoCommand;
    }
};


#endif // _UndoCommand_h
