/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _MWClearCmd_h
#define _MWClearCmd_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassMWClearCmd	"MWClearCmd"

class MsgWin;

//
// MWClearCmd class definition:
//				
class MWClearCmd : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    MsgWin *messageWindow;

    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    MWClearCmd(const char *name,
	       CommandScope *scope,
	       boolean active,
	       MsgWin *win);

    //
    // Destructor:
    //
    ~MWClearCmd(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMWClearCmd;
    }
};


#endif // _MWClearCmd_h
