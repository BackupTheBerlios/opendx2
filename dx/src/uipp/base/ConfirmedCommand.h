//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/ConfirmedCommand.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#ifndef _ConfirmedCommand_h
#define _ConfirmedCommand_h


#include "UIConfig.h"

#include <Xm/Xm.h>

#include "defines.h"
#include "NoUndoCommand.h"

//
// Class name definition:
//
#define ClassConfirmedCommand	"ConfirmedCommand"

//
// ConfirmedCommand class definition:
//				
class ConfirmedCommand : public NoUndoCommand
{
  private:
    char* dialogQuestion;
    char* dialogTitle;

    static void OkDCB(void* clientData);

  protected:
    //
    // Constructor:
    //
    Widget dialogParent;

    ConfirmedCommand(const char*   name,
		     CommandScope* scope,
		     boolean       active,
		     char*         dialogTitle,
		     char*         dialogQuestion,
		     Widget	parent = NULL);


  public:
    //
    // Destructor:
    //
    ~ConfirmedCommand(){}

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
	return ClassConfirmedCommand;
    }
};


#endif // _ConfirmedCommand_h
