//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/PacketHandler.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 */


#ifndef _PacketHandler_h
#define _PacketHandler_h


#include "defines.h"
#include "Base.h"


//
// Class name definition:
//
#define ClassPacketHandler	"PacketHandler"

typedef void (*PacketHandlerCallback)(void *clientData, int id, void *line);

//
// PacketHandler class definition:
//				
class PacketHandler : public Base
{
  private:
    //
    // Private member data:
    //
    int				linger;
    int				type;
    int				number;
    PacketHandlerCallback	callback;
    void		       *clientData;
    char		       *matchString;
    int				matchLen;


  protected:
    //
    // Protected member data:
    //


  public:
    //
    // Constructor:
    //
    PacketHandler(int plinger = 0,
		    int ptype = 0,
		    int pnumber = 0,
		    PacketHandlerCallback pcallback = NULL,
		    void * pclientData = NULL,
		    const char *matchString = NULL);

    //
    // Destructor:
    //
    ~PacketHandler();

    void callCallback(int id, void * token) 
    {
	(*this->callback)(this->clientData, id, token);
    }

    int getLinger() {return this->linger;}
    int getType() {return this->type;}
    int getNumber() {return this->number;}
    const char *getMatch() {return this->matchString;}
    boolean match(const char *s);
    boolean matchFirst(const char *s);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassPacketHandler;
    }
};

#endif // _PacketHandler_h
