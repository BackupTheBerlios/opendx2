//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// XHandler.h -							    //
//                                                                          //
// Definition for the XHandler class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/XHandler.h,v 1.1 1999/03/24 15:17:25 gda Exp $
 */


#ifndef _XHandler_h
#define _XHandler_h


#include "defines.h"
#include "Base.h"
#include "List.h"

#include <X11/Xlib.h>


//
// Class name definition:
//
#define ClassXHandler	"XHandler"

//
// Function to handle events, return true if this event should also be
// past to the Intrinsics for handling.
typedef boolean (*XHandlerCallback)(XEvent *event, void *clientData);

//
// XHandler class definition:
//				
class XHandler : public Base
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //
    static List Handlers;

    int 	      eventName;
    Window            window;
    XHandlerCallback  callback;
    void             *clientData;


  public:
    //
    // Constructor:
    //
    XHandler(int eventName,
	     Window window,
	     XHandlerCallback cb,
	     void *clientData);

    //
    // Destructor:
    //
    ~XHandler();

    //
    // Function to handle events. Returns true if this event should also be
    // past to the Intrinsics for handling.
    //
    static boolean ProcessEvent(XEvent *event);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassXHandler;
    }
};


#endif // _XHandler_h
