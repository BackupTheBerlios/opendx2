//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Server.C -								    //
//                                                                          //
// Server Class methods and other related functions/procedures.		    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/Server.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#include "Server.h"
#include "ListIterator.h"
#include "Client.h"


void Server::notifyClients(int message, const void *data, const char *msg)
{
    ListIterator iterator(this->clientList);
    Client*      client;

    //
    // Notify each of the clients in the client list.
    //
    while(client = (Client*)iterator.getNext())
    {
	client->notify(message, data, msg);
    }
}


boolean Server::registerClient(Client* client)
{
    ASSERT(client);

    //
    // If the client is already present in the list return FALSE;
    // otherwise, append the client to the list and return the result.
    //
    if (this->clientList.isMember(client))
    {
	return FALSE;
    }
    else
    {
	 return this->clientList.appendElement(client);
    }
}


boolean Server::unregisterClient(Client* client)
{
    int position;

    //
    // If the client is in the list, delete the client from the list
    // and return the result; otherwise, return FALSE.
    //
    if (position = this->clientList.getPosition(client))
    {
	return this->clientList.deleteElement(position);
    }
    else
    {
	return FALSE;
    }
}


