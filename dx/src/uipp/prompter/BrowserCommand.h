//////////////////////////////////////////////////////////////////////////////
// BrowserCommand.h -						    //
//                                                                          //
// Definition for the BrowserCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/BrowserCommand.h,v 1.1 1999/04/05 13:33:41 gda Exp $
 */

#ifndef _BrowserCommand_h
#define _BrowserCommand_h


#include "defines.h"
#include "NoUndoCommand.h"
#include <Xm/Xm.h>

class  Browser;

//
// BrowserCommand class definition:
//				

#define ClassBrowserCommand  "BrowserCommand"

class BrowserCommand : public NoUndoCommand 
{
  private:

    static  String	DefaultResources[];
    Browser* 		browser;
    int			option;

  protected:
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    BrowserCommand(const char*,
		CommandScope*,
		boolean active,
                Browser*,
		int option);

    //
    // Destructor:
    //
    ~BrowserCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassBrowserCommand;
    }
};


#endif // _BrowserCommand_h
