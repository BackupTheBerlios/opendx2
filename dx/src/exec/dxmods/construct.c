/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/
/*
 */

#include <stdio.h>
#include <dx/dx.h>

extern Field _dxfConstruct(Array, Array, Array, Array);

int
m_Construct(Object *in, Object *out)
{
    out[0] = (Object)_dxfConstruct((Array)in[0], (Array)in[1],
					(Array)in[2], (Array)in[3]);
    if (! out[0])
	return ERROR;
    else
       return OK;
}
