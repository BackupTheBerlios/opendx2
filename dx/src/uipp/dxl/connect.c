/*  Open Visualization Data Explorer Source File */

#include <malloc.h>

#include "../base/UIConfig.h"
#include "../base/defines.h"
#include "dxlP.h"

DXLError
uiDXLStartServer(DXLConnection *conn)
{
    if (!conn->dxuiConnected)
	return ERROR;
    return DXLSend(conn, "StartServer");
}

DXLError
uiDXLConnectToRunningServer(DXLConnection *conn, const int port)
{
    char buffer[100];

    if (!conn->dxuiConnected)
	return ERROR;

    sprintf(buffer, "ConnectToServer %d", port);
    return DXLSend(conn, buffer);
}
