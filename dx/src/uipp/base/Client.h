//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Client.h,v 1.1 1999/03/24 15:17:22 gda Exp $
 */



#ifndef _Client_h
#define _Client_h


#include "defines.h"
#include "Base.h"
#include "SymbolManager.h"


//
// Class name definition:
//
#define ClassClient	"Client"


//
// Client class definition:
//				
class Client : virtual public Base
{
  protected:
    //
    // Constructor:
    //   Protected to prevent direct instantiation....
    //
    Client(){}

  public:
    //
    // Destructor:
    //
    ~Client(){}

    //
    // This routine should be implemented by subclasses to handle
    // notifications by the server.
    //
    virtual void notify(const Symbol message, 
	const void *data=NULL, const char *msg = NULL) = 0;

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassClient;
    }
};


#endif // _Client_h
