//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// ConfirmedExitCommand.h -						    //
//                                                                          //
// Definition for the ConfirmedExitCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ConfirmedExitCommand.h,v 1.1 1999/03/31 22:30:54 gda Exp $
 *
 */

#ifndef _ConfirmedExitCommand_h
#define _ConfirmedExitCommand_h


#include "defines.h"
#include "OptionalPreActionCommand.h"


class   DXApplication;
class   Command;

//
// Class name definition:
//
#define ClassConfirmedExitCommand	"ConfirmedExitCommand"


//
// ConfirmedExitCommand class definition:
//				
class ConfirmedExitCommand : public OptionalPreActionCommand 
{
  private:

    Command     *command;
    DXApplication *application;

  protected:
    //
    // Implements the command:

    virtual boolean needsConfirmation();
    virtual void    doPreAction();

  public:
    //
    // Constructor:
    //
    ConfirmedExitCommand(const char*   name,
                        CommandScope* scope,
                        boolean       active,
			DXApplication *app);

    //
    // Destructor:
    //
    ~ConfirmedExitCommand(){}

    boolean doIt(CommandInterface*);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassConfirmedExitCommand;
    }
};


#endif // _ConfirmedExitCommand_h
