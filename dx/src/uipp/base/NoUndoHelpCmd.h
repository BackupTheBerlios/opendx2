//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoHelpCmd.h -						    //
//                                                                          //
// Definition for the NoUndoHelpCmd class.				    //
//
//  All commands implemented here are non-undoable commands and have a	    //	
// command scope that is local to the control panel.
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/NoUndoHelpCmd.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#ifndef _NoUndoHelpCmd_h
#define _NoUndoHelpCmd_h


#include "defines.h"
#include "NoUndoCommand.h"

typedef long HelpCmdType;

//
// Class name definition:
//
#define ClassNoUndoHelpCmd	"NoUndoHelpCmd"

class   HelpWin;

//
// NoUndoHelpCmd class definition:
//				
class NoUndoHelpCmd : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    HelpWin	*helpWin;
    HelpCmdType 	 commandType;
 
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NoUndoHelpCmd(const char*   name,
                CommandScope  *scope,
                boolean       active,
		HelpWin      *helpWin,
		HelpCmdType     comType);

    //
    // Destructor:
    //
    ~NoUndoHelpCmd(){}

    // 
    // These are the various operations that the NoUndoHelpCmd can 
    // implement on behalf of an image.
    // 
    enum {
	Close			= 3	// Unmanage the window.
    };
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoUndoHelpCmd;
    }
};


#endif // _NoUndoHelpCmd_h
