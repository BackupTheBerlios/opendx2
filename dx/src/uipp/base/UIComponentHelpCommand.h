//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// UIComponentHelpCommand.h -						    //
//                                                                          //
// Definition for the UIComponentHelpCommand class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/UIComponentHelpCommand.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#ifndef _UIComponentHelpCommand_h
#define _UIComponentHelpCommand_h


#include "defines.h"
#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassUIComponentHelpCommand	"UIComponentHelpCommand"


//
// Referenced classes:
//
class UIComponent;


//
// UIComponentHelpCommand class definition:
//				
class UIComponentHelpCommand : public NoUndoCommand
{
  private:
    //
    // Private class data:
    //

  protected:
    //
    // Protected class data:
    //

    //
    // Protected member data:
    //
    UIComponent*		component;		

    //
    // Does nothing;
    //
    virtual boolean doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    UIComponentHelpCommand(const char*   name,
			 CommandScope* scope,
			 boolean       active,
			 UIComponent*   component);

    //
    // Destructor:
    //
    ~UIComponentHelpCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassUIComponentHelpCommand;
    }
};


#endif // _UIComponentHelpCommand_h
