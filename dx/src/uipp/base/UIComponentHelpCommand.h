/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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
