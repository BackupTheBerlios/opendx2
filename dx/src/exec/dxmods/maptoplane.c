/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/maptoplane.c,v 1.1 1999/03/24 15:18:29 gda Exp $:
 */

/***
MODULE:		
    _dxfMapToPlane
SHORTDESCRIPTION:
    Maps a field onto a plane.
CATEGORY:
    Realization
INPUTS:
    data;    data field;              none; data to be mapped
    point;       vector;  center of object; a point on the map plane
    normal;      vector;           [0 0 1]; normal to the map plane
OUTPUTS:
    plane;   data field;              NULL; mapped plane
FLAGS:
BUGS:
AUTHOR:
    Brian P. O'Toole
END:
***/

#include <stdio.h>
#include <math.h>
#include <dx/dx.h>
#include <bounds.h>
#include "vectors.h"

extern Object _dxfMapToPlane ();
static Error map_normal ();

int m_MapToPlane (in, out)
    Object		*in;
    Object		*out;
{
    Object		ino0, ino1, ino2;
    Object		cutplane;
    Point               p;
    float		point[3];
    float		normal[3];
    Class		class;

    out[0] = NULL;

    ino0 = in[0];
    ino1 = in[1];
    ino2 = in[2];

    if (ino0 == NULL)
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "input");
	goto error;
    }

    class = DXGetObjectClass (ino0);

    if (ino1 == NULL) 
    {
	/*
         * Choose the center of the bounding box as the point.
	 */

	if (! _dxf_BBoxPoint (in[0], &p, BB_CENTER))
	{
	    DXSetError(ERROR_INVALID_DATA,
		"unable to determine bounding box for data");
	    goto error;
	}

	point[0] = (float) p.x;
	point[1] = (float) p.y;
	point[2] = (float) p.z;
    }

    else 
    {
	if (! DXExtractParameter (ino1, TYPE_FLOAT, 3, 1, (Pointer) point))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10370", "point", "3-D vector");
	    return ERROR;
	}
    }

    if (! map_normal (normal, ino2))
	return ERROR;

    out[0] = _dxfMapToPlane (ino0, point, normal);

    if (DXGetError() != ERROR_NONE)
        return ERROR;

    if (! out[0])
    {
        out[0] = (Object)DXEndField(DXNewField());
	if (! out[0])
	    return ERROR;
	else
	    return OK;
    }

    if (! DXGetPart(out[0], 0))
    {
	DXDelete(out[0]);
	out[0] = (Object)DXEndField(DXNewField());
    }

    return OK;

error:
    return ERROR;
}


static Error map_normal (normal, ino)
    float		*normal;
    Object		ino;
{
    if (ino == NULL)
    {
	normal[0] = (float) 0.0;
	normal[1] = (float) 0.0;
	normal[2] = (float) 1.0;
    }
    else
    {
	if (! DXExtractParameter (ino, TYPE_FLOAT, 3, 1, (Pointer) normal))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10370", "normal", "3-D vector");
	    return ERROR;
	}
	
	if (vector_zero((Vector *)normal))
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#11822", "normal");
	    return ERROR;
	}

    }

    return (OK);
}
