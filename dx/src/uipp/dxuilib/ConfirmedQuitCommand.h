//////////////////////////////////////////////////////////////////////////////
// ConfirmedQuitCommand.h -							    //
//                                                                          //
// Definition for the ConfirmedQuitCommand class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ConfirmedQuitCommand.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 *
 */

#ifndef _ConfirmedQuitCommand_h
#define _ConfirmedQuitCommand_h


#include "defines.h"
#include "OptionalPreActionCommand.h"

#include <Xm/Xm.h>

class   DXApplication;
class   Command;

//
// Class name definition:
//
#define ClassConfirmedQuitCommand	"ConfirmedQuitCommand"


//
// ConfirmedQuitCommand class definition:
//				
class ConfirmedQuitCommand : public OptionalPreActionCommand 
{
  private:

    Command     *command;
    DXApplication *application;

  protected:
    //
    // Implements the command:

    virtual boolean needsConfirmation();
    virtual void    doPreAction();
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    ConfirmedQuitCommand(const char*   name,
                        CommandScope* scope,
                        boolean       active,
			DXApplication *app);

    //
    // Destructor:
    //
    ~ConfirmedQuitCommand();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassConfirmedQuitCommand;
    }
};


#endif // _ConfirmedQuitCommand_h
