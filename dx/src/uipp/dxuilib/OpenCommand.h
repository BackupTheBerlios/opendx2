//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// OpenCommand.h -							    //
//                                                                          //
// Definition for the OpenCommand class.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/OpenCommand.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 *
 */

#ifndef _OpenCommand_h
#define _OpenCommand_h


#include "defines.h"
#include "OptionalPreActionCommand.h"

#include <Xm/Xm.h>

class	Network;
class   DXApplication;

//
// Class name definition:
//
#define ClassOpenCommand	"OpenCommand"


//
// OpenCommand class definition:
//				
class OpenCommand : public OptionalPreActionCommand 
{
  private:

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
    OpenCommand(const char*   name,
                        CommandScope* scope,
                        boolean       active,
			DXApplication *app,
			Widget dialogParent = NULL);

    //
    // Destructor:
    //
    ~OpenCommand(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenCommand;
    }
};


#endif // _OpenCommand_h
