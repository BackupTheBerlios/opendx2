/*  Open Visualization Data Explorer Source File */



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
