/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/post.c,v 1.3 1999/05/10 15:45:29 gda Exp $:
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

