/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/post.c,v 1.1 1999/03/24 15:18:30 gda Exp $:
 */

#include <stdio.h>
#include <dx/dx.h>

extern Object _dxfPost(Object, char *, Array);

int
m_Post(Object *in, Object *out)
{
    Object object;
    int    dir;
    char   *str = "positions";

    out[0] = NULL;
    object = NULL;

    if (! in[0])
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "field");
	goto error;
    }

    if (in[1])
    {
	if (! DXExtractString(in[1], &str))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10200", "dependency");
	    goto error;
	}
    }

    object = DXCopy(in[0], COPY_STRUCTURE);
    if (! object)
	goto error;

    if (! _dxfPost(object, str, (Array)in[2]))
	goto error;
    
    out[0] = object;
    return OK;

error:
    if (in[0] != object)
	DXDelete(object);
    out[0] = NULL;
    return ERROR;
}

