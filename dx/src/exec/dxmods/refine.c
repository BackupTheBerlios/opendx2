/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/refine.c,v 1.1 1999/03/24 15:18:30 gda Exp $:
 */

/***
MODULE:
 _dxfRefine
SHORTDESCRIPTION:
 Refinement of input field
CATEGORY:
 Data Transformation
INPUTS:
 input;   field;   none;      field to refine
 level;   scalar;     1;      level of refinement
OUTPUTS:
 refined; field;   NULL;      refined input
FLAGS:
BUGS:
AUTHOR:
 Greg Abram
END:
***/

#define PARALLEL

#include <stdio.h>
#include <dx/dx.h>

extern Object _dxfRefine(Object, int);
extern Object _dxfChgTopology(Object, char *);

#define NEW_LEVEL	1
#define NEW_TOPOLOGY	2

int
m_Refine(Object *in, Object *out)
{
    int   level, refineType;
    char *newEltType;

    out[0] = NULL;

    if(! in[0])
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "input");
	return ERROR;
    }

    level = 1;
    refineType = NEW_LEVEL;
    if (in[1])
    {
	float fLevel;

	if (DXExtractInteger(in[1], &level))
	{
	    refineType = NEW_LEVEL;
	}
	else if (DXExtractFloat(in[1], &fLevel))
	{
	    if (fLevel != (int)fLevel)
	    {
		DXSetError(ERROR_BAD_PARAMETER, "#10620", "level");
		return NULL;
	    }
	    refineType = NEW_LEVEL;
	    level = (int)fLevel;
	}
	else if (DXExtractString(in[1], &newEltType))
	{
	    refineType = NEW_TOPOLOGY;
	}
	else
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10620", "level");
	    return ERROR;
	}
    }

    if (refineType == NEW_LEVEL && level < 0)
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10620", "level");
	return NULL;
    }

    if (refineType == NEW_LEVEL)
    {
	out[0] = _dxfRefine(in[0], level);

	if (! out[0])
	    return ERROR;
	
	return OK;
    }
    else /* refineType == NEW_TOPOLOGY */
    {
	out[0] = _dxfChgTopology(in[0], newEltType);

	if (! out[0])
	    return ERROR;
    }

    return OK;
}
