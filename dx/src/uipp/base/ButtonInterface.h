//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/ButtonInterface.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


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
