/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <dx/dx.h>

extern Object _dxfNormals(Object, char *);

int
m_FaceNormals (Object *in, Object *out)
{
    char		*method;

    out[0] = NULL;

    if (in[0] == NULL)
    {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "input");
	goto error;
    }

    out[0] = _dxfNormals(in[0], "connections");

    if (out[0] == NULL || DXGetError() != ERROR_NONE)
	goto error;
    
    return OK;

error:
    DXDelete(out[0]);
    return ERROR;
}
