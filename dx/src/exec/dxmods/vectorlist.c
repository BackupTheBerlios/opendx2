/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#include <dx/dx.h>

extern
Error _dxfvector_base(Object *,Object *, int);

int m_VectorList(Object *in, Object *out)
{
   if (!_dxfvector_base(in, out,1))
      return ERROR;
   return OK;
}

