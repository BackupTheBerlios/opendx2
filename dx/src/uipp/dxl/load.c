/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <malloc.h>
#include <string.h>

#include "../base/UIConfig.h"
#include "../base/defines.h"
#include "dxlP.h"

int
DXLLoadMacroFile(DXLConnection *conn, const char *file)
{
    int l = strlen(file);
    char *buffer = MALLOC(l + 50);
    int sts;

    sprintf(buffer, "load macroFile %s", file);
    sts = DXLSend(conn, buffer);
    FREE(buffer);
    return sts;
}

int
DXLLoadMacroDirectory(DXLConnection *conn, const char *dir)
{
    int l = strlen(dir);
    char *buffer = MALLOC(l + 50);
    int sts;

    sprintf(buffer, "load macroDirectory %s", dir);
    sts = DXLSend(conn, buffer);
    FREE(buffer);
    return sts;
}
