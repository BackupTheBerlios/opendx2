//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// MWClearCmd.h -							    //
//                                                                          //
// Definition for the MWClearCmd class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/MWClearCmd.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


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
