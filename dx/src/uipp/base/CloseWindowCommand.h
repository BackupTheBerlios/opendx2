//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/CloseWindowCommand.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#ifndef _CloseWindowCommand_h
#define _CloseWindowCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassCloseWindowCommand	"CloseWindowCommand"


//
// Referenced classes:
//
class MainWindow;


//
// CloseWindowCommand class definition:
//				
class CloseWindowCommand : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    MainWindow* window;

    //
    // Does nothing;
    //
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    CloseWindowCommand(const char*   name,
		       CommandScope* scope,
		       boolean       active,
		       MainWindow*   window);

    //
    // Destructor:
    //
    ~CloseWindowCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCloseWindowCommand;
    }
};


#endif // _CloseWindowCommand_h
