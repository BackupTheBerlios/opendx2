//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/NewCommand.h,v 1.1 1999/03/31 22:32:55 gda Exp $
 */


#ifndef _NewCommand_h
#define _NewCommand_h


#include "defines.h"
#include "OptionalPreActionCommand.h"
#include "Network.h"


//
// Class name definition:
//
#define ClassNewCommand	"NewCommand"


//
// NewCommand class definition:
//				
class NewCommand : public OptionalPreActionCommand
{
  private:
    //
    // Private member data:
    //
    Network *network;

  protected:
    //
    // Protected member data:
    //
    virtual boolean needsConfirmation();
    virtual void    doPreAction();

    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NewCommand(const char      *name,
	       CommandScope    *scope,
	       boolean		active,
	       Network	       *net, 
		Widget		dialogParent);


    //
    // Destructor:
    //
    ~NewCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNewCommand;
    }
};


#endif // _NewCommand_h