#include <dx/dx.h>

#define WHERE in[0]

extern Field _dxfSaveSoftwareWindow(char *);
extern Field _dxfSaveHardwareWindow(char *);

m_ReadImageWindow(Object *in, Object *out)
{
    Object image;
    char *where;

    out[0] = NULL;

    if (! WHERE)
    {
	DXSetError(ERROR_MISSING_DATA, "where");
	return ERROR;
    }

    if (! DXExtractString(WHERE, &where))
    {
	DXSetError(ERROR_INVALID_DATA, "where");
	return ERROR;
    }

    image = (Object)_dxfSaveSoftwareWindow(where);

#if DXD_CAN_HAVE_HW_RENDERING
    if (! image)
    {
	DXResetError();
	image = (Object)_dxfSaveHardwareWindow(where);
    }
#endif
    
    if (! image)
	return ERROR;
    
    out[0] = (Object)image;
    return OK;
}

