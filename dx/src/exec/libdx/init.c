/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#include <string.h>
#include <dx/dx.h>

static int been_here = 0;

Error
DXinitdx()
{
    if (!been_here) {
	been_here = 1;

	if (!_dxf_initlocks())  return ERROR;
	if (!_dxf_initmemory()) return ERROR;
	if (!_dxf_initmessages()) return ERROR;
	if (!_dxf_inittiming()) return ERROR;
	if (!_dxf_initobjects()) return ERROR;
	if (!_dxf_initstringtable()) return ERROR;
	if (!_dxf_initdisk()) return ERROR;
	if (!_dxf_initcache()) return ERROR;
	if (!_dxf_initRIH()) return ERROR;
	if (!_dxf_initloader()) return ERROR;
#if DXD_HAS_LIBIOP
	if (!_dxf_initfb()) return ERROR;
#endif
    }
    return OK;
}

