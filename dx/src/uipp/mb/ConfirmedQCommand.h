//////////////////////////////////////////////////////////////////////////////
// ConfirmedQCommand.h -						    //
//                                                                          //
// Definition for the ConfirmedQCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/mb/ConfirmedQCommand.h,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

#ifndef _ConfirmedQCommand_h
#define _ConfirmedQCommand_h


#include "defines.h"
#include "OptionalPreActionCommand.h"

#include <Xm/Xm.h>

class   MBApplication;
class   MBMainWindow;
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
    MBApplication *application;
    MBMainWindow *mbmw;

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
                        boolean       active,
			MBMainWindow  *mbmw,
			MBApplication *app);

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
