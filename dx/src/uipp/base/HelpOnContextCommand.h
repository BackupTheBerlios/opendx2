//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// HelpOnContextCommand.h -						    //
//                                                                          //
// Definition for the HelpOnContextCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/HelpOnContextCommand.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#ifndef _HelpOnContextCommand_h
#define _HelpOnContextCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassHelpOnContextCommand	"HelpOnContextCommand"


//
// Referenced classes:
//
class MainWindow;


//
// HelpOnContextCommand class definition:
//				
class HelpOnContextCommand : public NoUndoCommand
{
  private:
    //
    // Private class data:
    //
   static boolean	HelpOnContextCommandClassInitialized;

  protected:
    //
    // Protected class data:
    //
    static Cursor	HelpCursor;	// help cursor for the component

    //
    // Protected member data:
    //
    MainWindow*		window;		// associated window

    //
    // Does nothing;
    //
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    HelpOnContextCommand(const char*   name,
			 CommandScope* scope,
			 boolean       active,
			 MainWindow*   window);

    //
    // Destructor:
    //
    ~HelpOnContextCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassHelpOnContextCommand;
    }
};


#endif // _HelpOnContextCommand_h
