
/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/divcurl.c,v 1.1 1999/03/24 15:18:27 gda Exp $:
 */

/***
MODULE:		
    _dxfDivCurl
SHORTDESCRIPTION:
    Computes divergence and curl
CATEGORY:
    Data Transformation
INPUTS:
    data;     vector field;        none; field to compute divergence and curl of
    method;         string; "manhattan"; gradient method to use
OUTPUTS:
    div;      scalar field;        NULL; divergence field
    curl;     vector field;        NULL; curl field
FLAGS:
BUGS:
AUTHOR:
    Brian P. O'Toole
END:
***/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dx/dx.h>

extern int _dxfDivCurl ();

static Error divcurl_method ();

int m_DivCurl (in, out)
    Object		*in;
    Object		*out;
{
    Object		ino0, ino1;

    out[0] = NULL;
    out[1] = NULL;

    ino0 = in[0];

    if (ino0 == NULL)
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "data");
	return ERROR;
    }

    if (in[1])
    {
	char *str;

	if (! DXExtractString(in[1], &str))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10200", "method");
	    return ERROR;
	}
	if (strcmp(str, "manhattan"))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10211", "method", "manhattan");
	    return ERROR;
	}
    }

    if (! _dxfDivCurl (ino0, &out[0], &out[1]))
	return ERROR;

    return (OK);
}
