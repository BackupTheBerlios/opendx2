/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _NoOpCommand_h
#define _NoOpCommand_h


#include "defines.h"
#include "Command.h"


//
// Class name definition:
//
#define ClassNoOpCommand	"NoOpCommand"


//
// NoOpCommand class definition:
//				
class NoOpCommand : public Command
{
  protected:
    //
    // Does nothing;
    //
    virtual boolean doIt(CommandInterface *ci);

    //
    // Undoes nothing;
    //
    virtual boolean undoIt();

  public:
    //
    // Constructor:
    //
    NoOpCommand(const char*   name,
		CommandScope* scope,
		boolean       active);

    //
    // Destructor:
    //
    ~NoOpCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoOpCommand;
    }
};


#endif // _NoOpCommand_h
