/*  Open Visualization Data Explorer Source File */



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
