/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/system.c,v 1.2 1999/05/03 14:06:37 gda Exp $
 */

#include <dx/dx.h>

int
m_System(Object *in, Object *out)
{
    static char format[] = "/bin/sh -c \"%s\" </dev/null";
    char *cmd;
#ifdef DXD_WIN
#define MAX_CMD_ARGS 30
    char *p[MAX_CMD_ARGS];
    char *s;
    int i;
#endif

    if (DXExtractString(in[0], &cmd)) {
	char *buf = (char *)DXAllocate(sizeof(format) + strlen(cmd) + 1);
#ifdef DXD_WIN
	strcpy(buf, cmd);
	for (s = buf, i = 0; *s && (i < MAX_CMD_ARGS - 1); s++, i++) {
	    for ( ; *s && isspace(*s); s++);
	    p[i] = s;
	    p[i+1] = '\0';
	    for ( ; *s && !isspace(*s); s++);
	    if (*s)
		*s = '\0';
	      else
	        break;
	}
	for (s = *p; s && *s; s++)
	    if (*s == '/')
		*s = '\\';

	spawnvp(_P_WAIT, p[0], p);
#else
	sprintf(buf, format, cmd);
	system(buf);
#endif
	DXFree(buf);
    } else
	DXErrorReturn(ERROR_BAD_PARAMETER, "bad command string");

    return OK;
}
