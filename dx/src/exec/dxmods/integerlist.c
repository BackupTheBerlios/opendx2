/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#include <dx/dx.h>

extern 
Error _dxfinteger_base(Object *,Object *, int);

int m_IntegerList(Object *in, Object *out)
{
   if (!_dxfinteger_base(in, out,1))
      return ERROR;
   return OK;
}

