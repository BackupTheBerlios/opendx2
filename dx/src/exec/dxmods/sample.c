/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <math.h>
#include <stdlib.h>
#include <dx/dx.h>

extern Object  Sample(Object, int);

Error
m_Sample(Object *in, Object *out)
{
    Object	copy	= NULL;
    int		n	= 100;
    Class	class	= CLASS_MIN;

    out[0] = NULL;

    if (in[0] == NULL)
    {
	DXSetError (ERROR_BAD_PARAMETER, "#10000", "manifold");
	goto error;
    }

    if (in[1] != NULL)
    {
	if (DXExtractInteger (in[1], &n) == NULL)
	{
	    DXSetError (ERROR_BAD_PARAMETER, "#10030", "density");
	    goto error;
	}

	if (n <= 0)
	{
	    DXSetError (ERROR_BAD_PARAMETER, "#10030", "density");
	    goto error;
	}
    }

    class = DXGetObjectClass (in[0]);
    if (class == CLASS_ARRAY || class == CLASS_STRING)
    {	
	DXSetError (ERROR_BAD_PARAMETER, "#10190", "manifold");
	goto error;
    }

    out[0] = Sample(in[0], n);
    if (! out[0])
	goto error;

    return OK;

error:
    return ERROR;
}

