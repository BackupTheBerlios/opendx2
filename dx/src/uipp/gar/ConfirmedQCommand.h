//////////////////////////////////////////////////////////////////////////////
// ConfirmedQCommand.h -						    //
//                                                                          //
// Definition for the ConfirmedQCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/ConfirmedQCommand.h,v 1.1 1999/03/24 15:17:27 gda Exp $
 */

#ifndef _ConfirmedQCommand_h
#define _ConfirmedQCommand_h


#include "../base/defines.h"
#include "../base/OptionalPreActionCommand.h"

#include <Xm/Xm.h>

class   Command;

//
// Class name definition:
//
#define ClassConfirmedQCommand	"ConfirmedQCommand"


//
// ConfirmedQCommand class definition:
//				
class ConfirmedQCommand : public OptionalPreActionCommand 
{
  private:

    Command     *command;

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
    ConfirmedQCommand(const char*   name,
                        CommandScope* scope,
                        boolean       active);

    //
    // Destructor:
    //
    ~ConfirmedQCommand(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassConfirmedQCommand;
    }
};


#endif // _ConfirmedQCommand_h
