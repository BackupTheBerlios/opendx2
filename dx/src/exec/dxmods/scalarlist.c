/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dx/dx.h>

extern
Error _dxfscalar_base(Object *,Object *, int);

int m_ScalarList(Object *in, Object *out)
{
   if (!_dxfscalar_base(in, out,1))
      return ERROR;
   return OK;
}

