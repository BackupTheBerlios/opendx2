/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#include "privateClass.h"

static Private
_NewPrivate(Pointer data, Error (*delete)(Pointer),
	    struct private_class *class)
{
    Private p = (Private) _dxf_NewObject((struct object_class *)class);
    if (!p)
	return NULL;
    p->data = data;
    p->delete = delete;
    return p;
}

Private
DXNewPrivate(Pointer data, Error (*delete)(Pointer))
{
    return _NewPrivate(data, delete, &_dxdprivate_class);
}

Error
_dxfPrivate_Delete(Private p)
{
    return p->delete? p->delete(p->data) : OK;
}

Pointer
DXGetPrivateData(Private p)
{
    return p? p->data : NULL;
}
