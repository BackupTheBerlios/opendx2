//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// DXPacketIF.h -							    //
//                                                                          //
// Definition for the DXPacketIF class.					    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/DXPacketIF.h,v 1.1 1999/03/24 15:17:39 gda Exp $
 */


#ifndef _DXPacketIF_h
#define _DXPacketIF_h

#include <stdio.h>

#include "defines.h"
#include "PacketIF.h"

//
// Class name definition:
//
#define ClassDXPacketIF	"DXPacketIF"

//
// DXPacketIF class definition:
//				
class DXPacketIF : public PacketIF
{
  private:

  protected:

    int id;

    //
    // Routines to handle dxexec messages.
    //
    static void DXProcessMessage(void *clientData, int id, void *line);
    static void DXProcessInformation(void *clientData, int id, void *line);
    static void DXProcessError(void *clientData, int id, void *line);
    static void DXProcessErrorWARNING(void *clientData, int id, void *line);
    static void DXProcessErrorERROR(void *clientData, int id, void *p);
    static void DXProcessCompletion(void *clientData, int id, void *line);
    static void DXProcessInterrupt(void *clientData, int id, void *line);
    static void DXProcessBeginExecNode(void *clientData, int id, void *line);
    static void DXProcessEndExecNode(void *clientData, int id, void *line);
    static void DXProcessLinkCommand(void *clientData, int id, void *p);
    static void DXHandleServerError(void *clientData, char *message);

    virtual void installLinkHandler();

  public:
    //
    // Constructor:
    //
    DXPacketIF(const char *server, int port, int local);


    //
    // Initializer
    //
    virtual void initializePacketIO();

    int send(int                   type,
             const char*           data = NULL,
             PacketHandlerCallback callback = NULL,
             void*                 clientData = NULL);
     //
     // Routine to format a message and send it
     //
    int sendFormat(const int type, const char *fmt, ...);


    int sendMacroStart(PacketHandlerCallback callback = NULL,
                       void*                 clientData = NULL);
    void sendMacroEnd();

    void setWaiter(int type,
                   int number,
                   PacketHandlerCallback callback,
                   void *clientData);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXPacketIF;
    }
};


#endif // _DXPacketIF_h
