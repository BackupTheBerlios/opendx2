/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#include <string.h>
#include "groupClass.h"


static MultiGrid
_dxf_NewMultiGrid(struct multigrid_class *class)
{
    MultiGrid s = (MultiGrid) _dxf_NewGroup((struct group_class *)class);
    if (!s)
	return NULL;
    return s;
}


MultiGrid
DXNewMultiGrid()
{
    return _dxf_NewMultiGrid(&_dxdmultigrid_class);
}


Group
_dxfMultiGrid_SetMember(MultiGrid s, char *name, Object value)
{
    if (!s->group.typed && value && !_dxf_SetType((Group)s, value))
	return NULL;
    return _dxfGroup_SetMember((Group)s, name, value);
}


Group
_dxfMultiGrid_SetEnumeratedMember(MultiGrid s, int n, Object value)
{
    if (!s->group.typed && value && !_dxf_SetType((Group)s, value))
	return NULL;
    return _dxfGroup_SetEnumeratedMember((Group)s, n, value);
}

