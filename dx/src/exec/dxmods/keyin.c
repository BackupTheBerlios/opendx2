/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/keyin.c,v 1.2 1999/05/03 14:06:35 gda Exp $
 */

#include <dxconfig.h>


/***
MODULE:
 KeyIn 
SHORTDESCRIPTION:
 Stops execution until an Enter keystroke is received.
CATEGORY:
 Debugging
INPUTS:
 string;    String;    Type <ENTER> to continue;  message to print
OUTPUTS:
BUGS:
 this routine only works in completely serial mode (-S).
AUTHOR:
 nancy s collins
END:
***/

#include <dx/dx.h>
#include <fcntl.h>

static char defmessage[] = "Type <ENTER> to continue";


int
m_KeyIn(Object *in, Object *out)
{
    int fh;
    char c, *s;

    if(in[0]) {
	if(!DXExtractString(in[0], &s)) {
	    DXSetError(ERROR_BAD_PARAMETER, "#10200", "prompt");
	    return NULL;
	}
    } else
	s = defmessage;

#ifdef DXD_OS_NON_UNIX
    _cprintf("%s", s);
    /*
    {
	char tmpStr[1024];
	 _cgets(tmpStr);
     }
     */
     while(1) {
	c = getche();
	if( c == '\n' || c == 13)
	    break;

     }
     putch('\n');
#else
    fh = open("/dev/tty", 2);
    if (fh < 0) {
	DXSetError(ERROR_INVALID_DATA, "cannot open /dev/tty");
	return NULL;
    }
    write(fh, s, strlen(s));

    do {
	read(fh, &c, 1);
    } while(c != '\n');

    close(fh);
#endif

    return OK;
}
