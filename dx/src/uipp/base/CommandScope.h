//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// CommandScope.h -							    //
//                                                                          //
// Definition for the CommandScope class.				    //
//                                                                          //
// This class embodies a command scope (there may be many in an application)//
// and the information shared between commands within a given scope.        //
// It is intended to be used only by Command and UndoCommand objects to     //
// store and access information pertinent to the scope.  To this end, most  //
// functions are protected to be accessible only to the above classes (and  //
// to derived classes).							    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/CommandScope.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#ifndef _CommandScope_h
#define _CommandScope_h


#include "defines.h"
#include "Base.h"
#include "Command.h"


//
// Class name definition:
//
#define ClassCommandScope	"CommandScope"


//
// Referenced classes:
//
class Command;
class UndoCommand;


//
// CommandScope class definition:
//				
class CommandScope : public Base
{
    friend class Command;
    friend class UndoCommand;

  protected:
    //
    // Protected member data:
    //
    Command* lastCommand;	// the last undoable command executed
    Command* undoCommand;	// the local undo command

    //
    // This routine is intended to be called by Command objects only.
    //
    virtual void setLastCommand(Command* command)
    {
	this->lastCommand = command;
    }

    //
    // This routine is intended to be called by UndoCommand objects only.
    //
    virtual void setUndoCommand(Command* command)
    {
	this->undoCommand = command;
    }

    //
    // Access routines:
    //   To be accessed by friend classes only.
    //
    Command* getLastCommand()
    {
	return this->lastCommand;
    }
    Command* getUndoCommand()
    {
	return this->undoCommand;
    }

  public:
    //
    // Constructor:
    //
    CommandScope()
    {
	this->lastCommand = NUL(Command*);
	this->undoCommand = NUL(Command*);
    }

    //
    // Destructor:
    //
    ~CommandScope(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCommandScope;
    }
};


#endif // _CommandScope_h
