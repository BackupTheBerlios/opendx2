//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// ConfirmedOpenCommand.h -						    //
//                                                                          //
// Definition for the ConfirmedOpenCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/ConfirmedOpenCommand.h,v 1.1 1999/03/24 15:17:27 gda Exp $
 */

#ifndef _ConfirmedOpenCommand_h
#define _ConfirmedOpenCommand_h


#include "../base/defines.h"
#include "../base/OptionalPreActionCommand.h"

#include <Xm/Xm.h>

class   GARApplication;
class   GARMainWindow;
class   OpenFileDialog;
class   Command;

//
// Class name definition:
//
#define ClassConfirmedOpenCommand	"ConfirmedOpenCommand"


//
// ConfirmedOpenCommand class definition:
//				
class ConfirmedOpenCommand : public OptionalPreActionCommand 
{
  private:

    Command     *command;
    GARApplication *application;
    GARMainWindow *gmw;

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
    ConfirmedOpenCommand(const char*   name,
                        CommandScope* scope,
                        boolean       active,
			GARMainWindow *gmw,
			GARApplication *app);

    //
    // Destructor:
    //
    ~ConfirmedOpenCommand(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassConfirmedOpenCommand;
    }
};


#endif // _ConfirmedOpenCommand_h
