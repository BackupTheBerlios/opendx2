//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/LinkHandler.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#ifndef _LinkHandler_h
#define _LinkHandler_h

#include "defines.h"
#include "Base.h"
#include "Command.h"
#include "../base/CmdEntry.h"

//
// Class name definition:
//
#define ClassLinkHandler "LinkHandler"

class PacketIF;
class CmdEntry;
//typedef boolean (*CmdEntryFunction)(const char *, int, void *);

class LinkHandler : public Base
{
    private:

	CmdEntry   *commandEntry;
	PacketIF   *packetIF;

    protected:

	//
	// Just call packetIF->sendPacket().
	//
	void sendPacket(int packetType, int packetId, 
			const char *data = NULL, int length = 0);
    
    public:

	LinkHandler(PacketIF *);
	~LinkHandler();
    
	void addCommand(const char *, CmdEntryFunction f);
	void addCommand(const char *, Command *);

	void addSubCommand(const char *, const char *, CmdEntryFunction f);
	void addSubCommand(const char *, const char *, Command *);
	
	boolean executeLinkCommand(const char *, int);

	PacketIF *getPacketIF() {return this->packetIF;}

	//
	// Returns a pointer to the class name.
	//
	const char* getClassName()
	{
	    return ClassLinkHandler;
	}

};


#endif
    





