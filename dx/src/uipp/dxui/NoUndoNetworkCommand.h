//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/NoUndoNetworkCommand.h,v 1.1 1999/03/31 22:33:15 gda Exp $
 */



#ifndef _NoUndoNetworkCommand_h
#define _NoUndoNetworkCommand_h


#include "defines.h"
#include "NoUndoCommand.h"

typedef long NetworkCommandType;

//
// Class name definition:
//
#define ClassNoUndoNetworkCommand	"NoUndoNetworkCommand"

class   Network;

//
// NoUndoNetworkCommand class definition:
//				
class NoUndoNetworkCommand : public NoUndoCommand
{
    
  protected:
    //
    // Protected member data:
    //
    Network		*network;
    NetworkCommandType 	commandType;
 
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NoUndoNetworkCommand(const char*   name,
                   CommandScope  *scope,
                   boolean       active,
		   Network	*n,
		   NetworkCommandType comType);

    //
    // Destructor:
    //
    ~NoUndoNetworkCommand(){}

    // 
    // These are the various operations that the NoUndoNetworkCommand can 
    // implement on behalf of a control panel.
    // 
    enum {
	HelpOnNetwork,		// Display help on the network. 
	SetNetworkName,		// Set the name of the network.
	SaveNetwork,		// Save the network with current name.
	SaveNetworkAs,		// Save network with new name.
	OpenConfiguration,	// 
	SaveConfiguration	// 
    };

    //
    // Only activate the save and SaveAs commands when theDXApplication 
    // allows saving networks as defined by appAllowsSavingNetFile()
    //
    virtual void activate();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNoUndoNetworkCommand;
    }
};


#endif // _NoUndoNetworkCommand_h
