/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/gradient.c,v 1.3 1999/05/10 15:45:26 gda Exp $:
 */

#include <dxconfig.h>


/***
MODULE:		
    _dxfGradient
SHORTDESCRIPTION:
    Computes the gradient of a scalar field
CATEGORY:
    Data Transformation
INPUTS:
    data;     scalar field;        NULL; field to compute gradient of
    method;         string; "manhattan"; method to use
OUTPUTS:
    gradient; vector field;        NULL; gradient field
FLAGS:
BUGS:
AUTHOR:
    Brian P. O'Toole
END:
***/

#include <stdio.h>
#include <math.h>
#include <dx/dx.h>

extern Object _dxfGradient(Object);
static Error gradient_method(Object);

int m_Gradient (in, out)
Object		*in;
Object		*out;
{
    out[0] = NULL;

    if (! in[0])
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "data");
	return ERROR;
    }

    if (! gradient_method(in[1]))
	return ERROR;

    out[0] = _dxfGradient(in[0]);
    if (! out[0])
	return ERROR;

    return (OK);
}

static Error
gradient_method (Object object)
{
    char *str;

    if (! object)
	return OK;

    if (! DXExtractString (object, &str)) 
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10200", "method");
	return ERROR;
    }

    if (strcmp (str, "manhattan"))
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10211", "method", "manhattan");
	return ERROR;
    }

    return (OK);
}
