//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// ToggleButtonInterface.h -						    //
//                                                                          //
// Definition for the ToggleButtonInterface class.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/RepeatingToggle.h,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#ifndef _RepeatingToggle_H
#define _RepeatingToggle_H


#include "ToggleButtonInterface.h"

//
// Class name definition:
//
#define ClassRepeatingToggle	"RepeatingToggle"


//
// ToggleButtonInterface class definition:
//				
class RepeatingToggle : public ToggleButtonInterface
{
  private:

  public:
    //
    // Constructor:
    //
    RepeatingToggle(Widget   parent, char*    name,
	      Command* command, boolean  state, const char *bubbleHelp = NULL);

    //
    // Destructor:
    //
    ~RepeatingToggle(){}

    virtual void activate();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassRepeatingToggle;
    }
};


#endif // _RepeatingToggle_H
