/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#include "dx/dx.h"

/*
 * This module sends a message across the connection that is intended for
 * a DXLink application (i.e one that has linked with libdxl.a).
 */

#define TAG in[0]
#define VALUE in[1]

/* FIXME: this should be in an include file somewhere (see echo.m) */
Error _dxf_ConvertObjectsToStringValues(Object *in, int nobj, char **retrstr);


Error m_DXLOutput(Object in[], Object out[])
{
    char *tag, *value;

    if (!TAG) {
        DXSetError(ERROR_BAD_PARAMETER,"#10000","tag");
        goto error; 
    } else if (!DXExtractString(TAG,&tag)) {
        DXSetError(ERROR_BAD_PARAMETER,"#10200","tag");
        goto error; 
    }

    if (!VALUE) {
        value = "";
    } else if (!_dxf_ConvertObjectsToStringValues(&VALUE,1,&value)) {
        DXSetError(ERROR_BAD_PARAMETER,"#10200","value");
        goto error; 
    }
    

    DXUIMessage("LINK","DXLOutput VALUE %s %s",tag,value);
    if (VALUE)
	DXFree((Pointer)value);

    return OK;

error:
    return ERROR;

}

Error m_DXLOutputNamed(Object in[],  Object out[])
{
    return m_DXLOutput(in, out);
}
