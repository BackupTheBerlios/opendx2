//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoCommand.h -							    //
//                                                                          //
// Definition for the NoUndoCommand class.				    //
//                                                                          //
// This class serves as the base abstract class for all commands without    //
// undo (rollback) capability.						    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/NoUndoCommand.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#ifndef _NoUndoCommand_h
#define _NoUndoCommand_h


#include "defines.h"
#include "Command.h"


//
// NoUndoCommand class definition:
//				
class NoUndoCommand : public Command
{
  protected:
    //
    // No op for this class...
    //
    virtual boolean undoIt()
    {
	return FALSE;
    }

    //
    // Constructor:
    //   Protected to prevent direct instantiation.
    //
    NoUndoCommand(const char*   name,
		  CommandScope* scope,
		  boolean       active);

  public:
    //
    // Destructor:
    //
    ~NoUndoCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return "NoUndoCommand";
    }
};


#endif /*  _NoUndoCommand_h */
