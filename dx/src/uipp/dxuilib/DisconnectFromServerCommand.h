//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/DisconnectFromServerCommand.h,v 1.1 1999/03/24 15:17:39 gda Exp $
 */


#ifndef _DisconnectFromServerCommand_h
#define _DisconnectFromServerCommand_h


#include "defines.h"
#include "ConfirmedCommand.h"


//
// Class name definition:
//
#define ClassDisconnectFromServerCommand	"DisconnectFromServerCommand"


//
// DisconnectFromServerCommand class definition:
//				
class DisconnectFromServerCommand : public ConfirmedCommand
{
  protected:
    //
    // Implements the command:
    //   Queries the user for confirmation of the command.
    //   If affirmatively confirmed, the command terminates
    //   the application program.
    //
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    DisconnectFromServerCommand(const char*   name,
		CommandScope* scope,
		boolean       active);

    //
    // Destructor:
    //

    ~DisconnectFromServerCommand();
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDisconnectFromServerCommand;
    }
};


#endif // _DisconnectFromServerCommand_h
