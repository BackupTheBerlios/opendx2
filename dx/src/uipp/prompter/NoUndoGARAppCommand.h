//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/NoUndoGARAppCommand.h,v 1.1 1999/04/05 13:33:47 gda Exp $
 */


#ifndef _NoUndoGARAppCommand_h
#define _NoUndoGARAppCommand_h


#include "defines.h"
#include "NoUndoCommand.h"

typedef long GARAppCommandType;

//
// Class name definition:
//
#define ClassNoUndoGARAppCommand	"NoUndoGARAppCommand"

class   GARApplication;

//
// NoUndoGARAppCommand class definition:
//				
class NoUndoGARAppCommand : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    GARApplication     *application;
    GARAppCommandType commandType;
 
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NoUndoGARAppCommand(const char*   name,
                   CommandScope  *scope,
                   boolean       active,
		   GARApplication *application,
		   GARAppCommandType comType);

    //
    // Destructor:
    //
    ~NoUndoGARAppCommand(){}

    // 
    // These are the various operations that the NoUndoGARAppCommand can 
    // implement on behalf of a GARApplication.
    // 
    enum {
	HelpOnManual		= 1,   // Help command
	HelpOnHelp		= 2    // Help command
    };

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoUndoGARAppCommand;
    }
};


#endif // _NoUndoGARAppCommand_h
