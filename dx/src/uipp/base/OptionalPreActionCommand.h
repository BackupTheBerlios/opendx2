//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/OptionalPreActionCommand.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#ifndef _OptionalPreActionCommand_h
#define _OptionalPreActionCommand_h


#include "UIConfig.h"

#include <Xm/Xm.h>

#include "defines.h"
#include "PreActionCommand.h"


//
// Class name definition:
//
#define ClassOptionalPreActionCommand	"OptionalPreActionCommand"


//
// OptionalPreActionCommand class definition:
//				
class OptionalPreActionCommand : public PreActionCommand
{
  private:

  protected:
    //
    // Constructor:
    //
    OptionalPreActionCommand(const char*   name,
		     CommandScope* scope,
		     boolean       active,
		     char*         dialogTitle,
		     char*         dialogQuestion,
		     Widget	   dialogParent = NULL);

    virtual boolean needsConfirmation() = 0;

  public:
    //
    // Destructor:
    //
    ~OptionalPreActionCommand(){}

    //
    // Overrides the supperclass execute() function:
    //   First posts a dialog to ask for user confirmation before
    //   actually executing the command.
    //
    virtual boolean execute(CommandInterface *ci = NULL);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOptionalPreActionCommand;
    }
};


#endif // _OptionalPreActionCommand_h
