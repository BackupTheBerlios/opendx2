//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/NoUndoChoiceCommand.h,v 1.1 1999/03/24 15:17:28 gda Exp $
 */


#ifndef _NoUndoChoiceCommand_h
#define _NoUndoChoiceCommand_h


#include "defines.h"
#include "NoUndoCommand.h"

typedef long ChoiceCommandType;

class TypeChoice;

//
// Class name definition:
//
#define ClassNoUndoChoiceCommand	"NoUndoChoiceCommand"

//
// NoUndoChoiceCommand class definition:
//				
class NoUndoChoiceCommand : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    TypeChoice     *choice;
    ChoiceCommandType commandType;
 
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NoUndoChoiceCommand(const char*   name,
                   CommandScope  *scope,
                   boolean       active,
		   TypeChoice *chooser,
		   ChoiceCommandType comType);

    //
    // Destructor:
    //
    ~NoUndoChoiceCommand(){}

    // 
    // These are the various operations 
    // 
    enum {
	Browse		= 1,
	SetChoice	= 2,
	Visualize	= 4,
	SetGridType	= 5,
	Positions	= 6,
	NoOp		= 7,
	Prompter	= 8,
	RestrictNames	= 9,
	SpecifyRows	= 10,
	UseDelimiter	= 11,
	SimplePrompter	= 12,
	VerifyData	= 99
    };

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoUndoChoiceCommand;
    }
};


#endif // _NoUndoChoiceCommand_h
