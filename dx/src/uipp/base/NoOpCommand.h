//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/NoOpCommand.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


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
