//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/NoUndoJavaNetCommand.h,v 1.1 1999/03/31 22:33:12 gda Exp $
 */



#ifndef _NoUndoJavaNetCommand_h
#define _NoUndoJavaNetCommand_h


#include "NoUndoCommand.h"

typedef long JavaNetCommandType;

//
// Class name definition:
//
#define ClassNoUndoJavaNetCommand	"NoUndoJavaNetCommand"

class   JavaNet;

//
// NoUndoJavaNetCommand class definition:
//				
class NoUndoJavaNetCommand : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    JavaNet		*network;
    JavaNetCommandType 	commandType;
 
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NoUndoJavaNetCommand(const char*   name,
                   CommandScope  *scope,
                   boolean       active,
		   JavaNet	*n,
		   JavaNetCommandType comType);

    //
    // Destructor:
    //
    ~NoUndoJavaNetCommand(){}

    // 
    // These are the various operations that the NoUndoJavaNetCommand can 
    // implement on behalf of a control panel.
    // 
    enum {
	SaveWebPage,
	SaveApplet,
	SaveBean
    };

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoUndoJavaNetCommand;
    }
};


#endif // _NoUndoJavaNetCommand_h
