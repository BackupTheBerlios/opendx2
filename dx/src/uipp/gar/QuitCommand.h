//////////////////////////////////////////////////////////////////////////////
// QuitCommand.h -							    //
//                                                                          //
// Definition for the QuitCommand class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/QuitCommand.h,v 1.1 1999/03/24 15:17:28 gda Exp $
 */

#ifndef _QuitCommand_h
#define _QuitCommand_h


#include "../base/defines.h"
#include "../base/ConfirmedCommand.h"


//
// Class name definition:
//
#define ClassQuitCommand	"QuitCommand"


class Application;


//
// QuitCommand class definition:
//				
class QuitCommand : public ConfirmedCommand
{
  private:
    Application *application;
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
    QuitCommand(Application*  app,
		const char*   name,
		CommandScope* scope,
		boolean       active,
		char*         dialogTitle,
		char*         dialogQuestion);

    //
    // Destructor:
    //
    ~QuitCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassQuitCommand;
    }
};


#endif // _QuitCommand_h
