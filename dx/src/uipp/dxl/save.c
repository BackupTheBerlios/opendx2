/*  Open Visualization Data Explorer Source File */

#include <malloc.h>
#include <string.h>

#include "../base/UIConfig.h"
#include "../base/defines.h"
#include "dxlP.h"

DXLError
uiDXLSaveVisualProgram(DXLConnection *conn, const char *file)
{
    int l = strlen(file);
    int sts;
    char *buffer = MALLOC(l + 32);

    if (conn->dxuiConnected)
    {
	sprintf(buffer, "save network %s", file);
	sts = DXLSend(conn, buffer);
    }
    else
    {
	_DXLError(conn, "saving visual programs  requires a UI connection");
	sts = ERROR;
    }
	
    FREE(buffer);
    return sts;
}
