/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#ifndef _ButtonInterface_h
#define _ButtonInterface_h


#include "defines.h"
#include "CommandInterface.h"


//
// Class name definition:
//
#define ClassButtonInterface	"ButtonInterface"


//
// ButtonInterface class definition:
//				
class ButtonInterface : public CommandInterface
{
  public:
    //
    // Constructor:
    //
    ButtonInterface(Widget   parent,
		    char*    name,
		    Command* command,
		    const char *bubbleHelp = NUL(char*));

    //
    // Destructor:
    //
    ~ButtonInterface(){}

    //
    // Set the label string.
    //
    void setLabel(const char* string);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassButtonInterface;
    }
};


#endif // _ButtonInterface_h
