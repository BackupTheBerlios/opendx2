/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/_refine.c,v 1.1 1999/03/24 15:18:24 gda Exp $
 */

#include <string.h>
#include "math.h"
#include <dx/dx.h>

static Field RefineField(Field, char *, int);
extern Field _dxfRefineReg(Field, int);
extern Field _dxfRefineIrreg(Field, int);

typedef struct 
{
    int		 limit;
} Args;

Object
_dxfRefine(Object object, int limit)
{
    Args	args;
    Object	result;

    args.limit     = limit;
	
    result = DXProcessParts
                 (object, RefineField, (char *)&args, sizeof(args), 1, 0);
    
    return result;
}

static Field
RefineField(Field field, char *args, int l)
{
    int	  limit = ((Args *)args)->limit;
    Field newField;
    Array array;

    if (DXEmptyField(field))
	return DXEndField(DXNewField());
    
    field = (Field)DXCopy((Object)field, COPY_STRUCTURE);
    if (! field)
	return NULL;

    array = (Array)DXGetComponentValue(field, "connections");

    if (DXQueryGridConnections(array, NULL, NULL))
	newField = _dxfRefineReg(field, limit);
    else
	newField = _dxfRefineIrreg(field, limit);

    if (newField == NULL)
	DXDelete((Object)field);
    
    return newField;
}
