/*  Open Visualization Data Explorer Source File */



#ifndef _TimedMessage_h
#define _TimedMessage_h


#include "defines.h"
#include "TimedDialog.h"


//
// Class name definition:
//
#define ClassTimedMessage	"TimedMessage"


//
// TimedMessage class definition:
//				
class TimedMessage : public TimedDialog
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    char *message;
    char *title;

    Widget createDialog(Widget parent);

  public:
    //
    // Constructor:
    //
    TimedMessage(const  char *name,
		 Widget parent,
		 const  char *message,
		 const  char *title,
		 int    timeout);

    //
    // Destructor:
    //
    ~TimedMessage();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassTimedMessage;
    }
};


#endif // _TimedMessage_h
