/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dx/dx.h>
static Error  GetObjectAndCameraFromCache(char *, Object *, Camera *);

#define CACHE_TAG    	in[0]

#define OBJECT		out[0]
#define CAMERA		out[1]

Error
m_GetScene(Object *in, Object *out)
{
    char *tag;

    if (! CACHE_TAG)
    {
	DXSetError(ERROR_MISSING_DATA, "no cache tag");
	goto error;
    }

    if (! DXExtractString(CACHE_TAG, &tag))
    {
	DXSetError(ERROR_MISSING_DATA, "cache tag must be a string");
	goto error;
    }

    if (! GetObjectAndCameraFromCache(tag, &OBJECT, &CAMERA))
    {
	DXSetError(ERROR_INTERNAL, "unable to access scene data");
	goto error;
    }

    return OK;

error:

    OBJECT = NULL;
    CAMERA = NULL;
}


static Error
GetObjectAndCameraFromCache(char *tag, Object *object, Camera *camera)
{
    char *buf;

    if (object)
    {
	buf = (char *)DXAllocate(strlen(tag) + strlen(".object") + 1);
	if (! buf)
	    goto error;
    
	sprintf(buf, "%s.object", tag);

	*object = DXGetCacheEntry(buf, 0, 0);
	DXFree((Pointer)buf);
    }

    if (camera)
    {
	buf = (char *)DXAllocate(strlen(tag) + strlen(".camera") + 1);
	if (! buf)
	    goto error;
    
	sprintf(buf, "%s.camera", tag);

	*camera = (Camera)DXGetCacheEntry(buf, 0, 0);
	DXFree((Pointer)buf);
    }

    return OK;

error:
    return ERROR;
}
