//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/NoUndoDXWindowCommand.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#ifndef _NoUndoDXWindowCommand_h
#define _NoUndoDXWindowCommand_h


#include "defines.h"
#include "NoUndoCommand.h"

typedef long DXWindowCommandType;

//
// Class name definition:
//
#define ClassNoUndoDXWindowCommand	"NoUndoDXWindowCommand"

class   DXWindow;

//
// NoUndoDXWindowCommand class definition:
//				
class NoUndoDXWindowCommand : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    DXWindow *dxWindow;
    DXWindowCommandType commandType;
 
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NoUndoDXWindowCommand(const char*   name,
                   CommandScope  *scope,
                   boolean       active,
		   DXWindow  *cp,
		   DXWindowCommandType comType);

    //
    // Destructor:
    //
    ~NoUndoDXWindowCommand(){}

    // 
    // These are the various operations that the NoUndoDXWindowCommand can 
    // implement on behalf of a DXWindow.
    // 
    enum {
	ToggleWindowStartup	= 1	// Flip startup state of window on/off
    };
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoUndoDXWindowCommand;
    }
};


#endif // _NoUndoDXWindowCommand_h
