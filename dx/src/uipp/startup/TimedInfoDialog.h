/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>


#ifndef _TimedInfoDialog_h
#define _TimedInfoDialog_h


#include "defines.h"
#include "TimedDialog.h"


//
// Class name definition:
//
#define ClassTimedInfoDialog	"TimedInfoDialog"

//
// TimedInfoDialog class definition:
//				
class TimedInfoDialog : public TimedDialog
{
  private:
    char *title;
    char *msg;

  protected:
    virtual Widget createDialog (Widget parent);

  public:
    //
    // Constructor:
    //
    TimedInfoDialog (
	const char* name, 
	Widget parent, 
	int timeout 
    ): TimedDialog(name, parent, timeout) {
	this->title = NUL(char*);
	this->msg   = NUL(char*);
    };

    void setTitle(const char *title);
    void setMessage(const char *message);

    //
    // Destructor:
    //
    ~TimedInfoDialog() {
	if (this->title) delete this->title;
	if (this->msg)   delete this->msg;
    }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassTimedInfoDialog; }
};
#endif // _TimedInfoDialog_h
