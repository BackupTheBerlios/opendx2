//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// UndoCommand.h -							    //
//                                                                          //
// Definition for the UndoCommand class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/UndoCommand.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


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
