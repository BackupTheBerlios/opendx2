/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#if sgi
#include <limits.h>
#endif
#include <string.h>
#include <stdio.h>
#include <dx/dx.h>
#include <stdlib.h>

#if 0
#include <dl.h>
#include <sys/stat.h>
#include <errno.h>
#endif

extern Object _dxf_EncodeImage(Field);
extern Field  _dxf_DecodeImage(Object);

#ifdef DXD_HAS_LIBIOP
#define RLE_DEFAULT	0
#else
#define RLE_DEFAULT	1
#endif

static Object message(Object image, char *name, int buttonState,
						int ddcamera, Object o);

static Error _link_message(char *link, char *where, Camera c);

extern Error DXSetSoftwareWindowActive(char *, int);

static Error _dxf_NoHardwareMessage();

#if DXD_CAN_HAVE_HW_RENDERING
Error _dxfAsyncRender (Object, Camera, char *, char *);
Error _dxfAsyncDelete (char *);
#endif

Error DXDisplayX16(Object, char *, char *);

int
m_Display(Object *in, Object *out)
{
    char *where, copy[201], *s, type[201];
    char *arg1=NULL, *arg2=NULL, *arg3=NULL, *arg4=NULL, *arg5=NULL;
    int wid, i, x, y;
    Object image=NULL, object=NULL, options, mode, bstate, ddcam;
    Camera camera;
    char   cacheid[201];	/* "Display.xxx" */
    char free_image;
    int ui_window = 0;
    int external_window = 0;
    double *old = NULL, new;
    Private p;
    int buttonState, ddcamera;

    /* throttle - borrow the where parameter for a while */
    if (in[2] && DXExtractString(in[2], &where))
	;
    else
	where = "throttle";

    p = (Private) DXGetCacheEntry(where, 0, 0);
    if (p) 
	old = (double *) DXGetPrivateData(p);

    if (in[3]) {
	float throttle;

	if (!DXExtractFloat(in[3], &throttle))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "#13610");

	if (throttle < 0)
	    DXErrorReturn(ERROR_BAD_PARAMETER, "#13620");

	if (throttle && p && old) {
	    new = DXGetTime();
	    if ((throttle - new + *old) > 0)
		DXWaitTime(throttle - new + *old);
	}
    }

    if (!p) {
	old = (double *) DXAllocate(sizeof(double));
	if (!old)
	    return ERROR;

	p = DXNewPrivate((Pointer)old, DXFree);
	if (!p)
	    return ERROR;

	if (!DXSetCacheEntry((Object)p, CACHE_PERMANENT, where, 0, 0)) {
	    DXDelete((Object)p);
	    old = NULL;
	}
    }
    if (old)
	*old = DXGetTime();


    /* object parameter */
    object = in[0];

    /* camera parameter */
    camera = (Camera) in[1];

#if 0
    DXPrintV((Object)camera, "rd", 0);
#endif

    /* extract where parameter */
    if (in[2])
    {
	char *c;

	if (!DXExtractString(in[2], &where))
	    DXErrorGoto(ERROR_BAD_PARAMETER, "#13630");
	
	if (where)
	    for (c = where; c[0] && c[1]; c++)
	    {
		if (c[0] == '#' && c[1] == '#')
		{
		    ui_window ++;
		    break;
		}
		else if (c[0] == '#' && c[1] == 'X')
		{
		    external_window ++;
		    break;
		}
	    }
    }
    else
	where = "X";


    /* check length of where parameter */
    /* XXX - better yet, make this dynamic */
    if (strlen(where)>=sizeof(copy)) {
	DXSetError(ERROR_BAD_PARAMETER, "#13660", sizeof(copy)-1);
	return ERROR;
    }

    /* parse where parameter */
    strcpy(copy, where);
    for (s=copy; *s; s++) {
	if (*s==',') {
	    if (!arg1) arg1 = s+1;
	    else if (!arg2) arg2 = s+1;
	    else if (!arg3) arg3 = s+1;
	    else if (!arg4) arg4 = s+1;
	    else if (!arg5) arg5 = s+1;
	    *s = '\0';
	}
    }
    strcpy(type, *copy? copy : "X");
    if (type[0] == 'X') 	/* matches X, X8, X12, X24 */
    {
 	if (arg1)
	{
	    strcat(type, ",");
	    strcat(type, arg1);
	}
    }

    if (in[1] &&
	NULL != (mode = DXGetAttribute(object, "rendering mode")))
    {
	char *s; 

	if (!DXExtractString(mode, &s))
	    DXErrorGoto(ERROR_BAD_PARAMETER, "#13640");

	if (strcmp(s,"hardware")==0 && 
		!DXGetCacheEntry("_DXD_NO_HARDWARE", 0, 0))
	{
#if DXD_CAN_HAVE_HW_RENDERING
	    DXSetSoftwareWindowActive(where, 0);
	    if  (_dxfAsyncRender(object, camera, NULL, where))
		goto done;

	    if (DXGetError() != ERROR_NO_HARDWARE_RENDERING)
	        goto error;

	    DXResetError();
	    DXSetSoftwareWindowActive(where, 0);
	    _dxf_NoHardwareMessage();
#else
	    _dxf_NoHardwareMessage();
#endif
	 }
    }

    /* look for button state */
    if (NULL != (bstate = DXGetAttribute(object, "button state")))
    {
	if (!DXExtractInteger(bstate, &buttonState) || 
			 (buttonState != 1 && buttonState != 2))
	    DXErrorGoto(ERROR_BAD_PARAMETER, 
		"button state must be an integer and either 1 or 2");
    }
    else
	 buttonState = 1;

    /* look for ddcamera */
    if (NULL != (ddcam = DXGetAttribute(object, "ddcamera")))
    {
	if (!DXExtractInteger(ddcam, &ddcamera) || 
			 (ddcamera != 1 && ddcamera != 2))
	    DXErrorGoto(ERROR_BAD_PARAMETER, 
		"ddcamera must be an integer and either 1 or 2");
    }
    else
	 ddcamera = 1;

#if DXD_CAN_HAVE_HW_RENDERING
    if (!_dxfAsyncDelete(where))
	return ERROR;
#endif

    /* render? */
    if (in[1])
    {
	int obTag, renderEvery;
	char *renderApprox;
	Object attr;
	char *cacheTag;

	/*
	 * stash the camera and object in cache
	 */
	cacheTag = (char *)DXAllocate(strlen("CACHED_OBJECT_") 
			+ strlen(where) + 32);

	sprintf(cacheTag, "%s%s", "CACHED_OBJECT_", where);
	DXSetCacheEntry(in[0], CACHE_PERMANENT, cacheTag, 0, 0);

	sprintf(cacheTag, "%s%s", "CACHED_CAMERA_", where);
	DXSetCacheEntry(in[1], CACHE_PERMANENT, cacheTag, 0, 0);

	DXFree((Pointer)cacheTag);

	if (!object)
	    DXErrorGoto(ERROR_MISSING_DATA, "#13650");
	
	attr = DXGetAttribute(object, "object tag");
	if (attr)
	    DXExtractInteger(attr, &obTag);
	else
	    obTag = DXGetObjectTag(object);
	
	attr = DXGetAttribute(object, "render every");
	if (attr)
	    DXExtractInteger(attr, &renderEvery);
	else
	    renderEvery = 1;
	
	attr = DXGetAttribute(object, "rendering approximation");
	if (attr)
	    renderApprox = DXGetString((String)attr);
	else 
	    renderApprox = "none";
	
	sprintf (cacheid, "Display.%s.%x.%d.%s",
		type, obTag, renderEvery, renderApprox);

	image = DXGetCacheEntry(cacheid, 0, 1, in[1]);
	if (image)
	{
	    if (DXGetAttribute(image, "encoding type"))
	    {
		Field new_image = _dxf_DecodeImage(image);
		if (! new_image)
		    goto error;

		DXDelete(image);
		image = DXReference((Object)new_image);
	    }
	}
	else
	{
	    Object encoded_image;
	    int cacheIt = 1;
	    Object attr;

	    image = (Object) DXRender(object, (Camera)in[1], where);
	    if (!image)
	      goto error;

	    DXReference(image);

	    attr = DXGetAttribute(object, "rendering approximation");
	    if (attr)
	    {
		if (DXGetObjectClass(attr) != CLASS_STRING)
		{
		    DXSetError(ERROR_BAD_CLASS, 
			"rendering approximation attribute");
		    goto error;
		}

		if (strcmp(DXGetString((String)attr), "none"))
		    cacheIt = 0;
	    }

	    if (cacheIt)
	    {
		attr = DXGetAttribute(object, "cache");
		if (attr)
		    if (! DXExtractInteger(attr, &cacheIt))
			goto error;
	    }
	    
	    if (cacheIt)
	    {
		int rle;

		if (! DXGetIntegerAttribute(object, "rle", &rle))
		    rle = RLE_DEFAULT;

		if (rle)
		{
		    encoded_image = _dxf_EncodeImage((Field)image);
		    if (! encoded_image)
			goto error;

		    if (!DXSetCacheEntry(encoded_image, 0.0,
				       cacheid, 0, 1, in[1]))
			goto error;
		}
		else
		{
		    if (!DXSetCacheEntry(image, 0.0,
				       cacheid, 0, 1, in[1]))
			goto error;
		}
		    
	    }

	}

    } else {

        image = DXReference(object);
	if (!image)
	    DXErrorGoto(ERROR_MISSING_DATA, "#13500");
    }

    /* display */
    if (type[0] == 'X')
    {

	if (ui_window && !message(image, arg2, buttonState, ddcamera, object))
	    goto error;

	if (external_window && !_link_message(arg3, where, camera))
	    goto error;
	    
	switch (_dxf_getXDepth(type)) {
	case 0:
	  if(!DXDisplayX(image, arg1, arg2))
	    goto error;
	  break;
	case 8:
	  if(!DXDisplayX8(image, arg1, arg2))
	    goto error;
	  break;
	case 12:
	  if(!DXDisplayX12(image, arg1, arg2))
	    goto error;
	  break;
	case 16:
	  if(!DXDisplayX16(image, arg1, arg2))
	    goto error;
	  break;
	case 24:
	  if(!DXDisplayX24(image, arg1, arg2))
	    goto error;
	  break;
	default:
	  goto error;
	  break;
	}
    } else if (strcmp(type,"FB")==0) {
	int x, y;
	if (!message(image, arg4, buttonState, ddcamera, object))
	    goto error;
	x = arg2? atoi(arg2) : 0;
	y = arg3? atoi(arg3) : 0;
	if (!DXDisplayFB(image, arg1, x, y))
	    goto error;
    } else {
	DXSetError(ERROR_BAD_PARAMETER, "#13630");
	goto error;
    }

    DXDelete(image);

done:
    out[0] = (Object)DXNewString(where);
    return OK;

error:
    DXDelete(image);
    return ERROR;
}


#define THREE(v) v.x,v.y,v.z

static Object
message(Object image, char *name, int buttonState, int ddcamera, Object object)
{
    Camera c;
    Array a;
    Point *box1, box2[8], corner[4], from, to, up;
    Point v0, v1, v2, v3;
    Matrix t, m;
    int i, width, height;
    float cwidth, aspect, fov;
    float minX = DXD_MAX_FLOAT, maxX = -DXD_MAX_FLOAT;
    float minY = DXD_MAX_FLOAT, maxY = -DXD_MAX_FLOAT;
    float minZ = DXD_MAX_FLOAT, maxZ = -DXD_MAX_FLOAT;

    c = (Camera) DXGetAttribute(image, "camera");
    a = (Array) DXGetAttribute(image, "object box");
    box1 = (Point *)DXGetArrayData(a);
    if (!name)
	name = "";

    if (c && box1)
    {
	Object attr;

	m = Identity;

#if 0
	if (NULL != (attr = DXGetAttribute(object, "autoaxes")))
	{
	    int aaflag;

	    if (! DXExtractInteger(attr, &aaflag))
	    {
		DXSetError(ERROR_INTERNAL,
			"autoaxes attribute is not an integer");
		return NULL;
	    }

	    if (aaflag)
	    {
		if (! DXGetXformInfo((Xform)object, NULL, &m))
		    return NULL;
	    }
	}
#endif

	DXGetView(c, &from, &to, &up);

	if (!DXGetImageBounds(image, NULL, NULL, &width, &height))
	    return NULL;

	t = DXGetCameraMatrix(c);
	for (i=0; i<8; i++)
	{
	    if (box1[i].x > maxX) maxX = box1[i].x;
	    if (box1[i].x < minX) minX = box1[i].x;
	    if (box1[i].y > maxY) maxY = box1[i].y;
	    if (box1[i].y < minY) minY = box1[i].y;
	    if (box1[i].z > maxZ) maxZ = box1[i].z;
	    if (box1[i].z < minZ) minZ = box1[i].z;
	}

	corner[0].x = minX; corner[0].y = minY; corner[0].z = minZ;
	corner[1].x = minX; corner[1].y = minY; corner[1].z = maxZ;
	corner[2].x = minX; corner[2].y = maxY; corner[2].z = minZ;
	corner[3].x = maxX; corner[3].y = minY; corner[3].z = minZ;

	if (DXGetOrthographic(c, &cwidth, &aspect)) {

	    DXUIMessage("IMAGE", "%s %dx%d width=%.6g aspect=%.3f "
		      "from=(%.6g,%.6g,%.6g) "
		      "to=(%.6g,%.6g,%.6g) "
		      "up=(%.6g,%.6g,%.6g) "
		      "box=(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g)"
		      "(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g) "
		      "aamat=(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g)"
		      "(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g) "
		      " ddcamera=%d button=%d",
		      name, width, height, cwidth, aspect,
		      THREE(from), THREE(to), THREE(up),
		      THREE(corner[0]), THREE(corner[1]),
		      THREE(corner[2]), THREE(corner[3]),
		      m.A[0][0], m.A[0][1], m.A[0][2],
		      m.A[1][0], m.A[1][1], m.A[1][2],
		      m.A[2][0], m.A[2][1], m.A[2][2],
		      m.b[0], m.b[1], m.b[2],
		      ddcamera, buttonState);

	} else if (DXGetPerspective(c, &fov, &aspect)) {

	    DXUIMessage("IMAGE", "%s %dx%d fov=%.6g aspect=%.3f "
		      "from=(%.6g,%.6g,%.6g) "
		      "to=(%.6g,%.6g,%.6g) "
		      "up=(%.6g,%.6g,%.6g) "
		      "box=(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g)"
		      "(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g) "
		      "aamat=(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g)"
		      "(%.6g,%.6g,%.6g)(%.6g,%.6g,%.6g) "
		      " ddcamera=%d button=%d",
		      name, width, height, fov, aspect,
		      THREE(from), THREE(to), THREE(up),
		      THREE(corner[0]), THREE(corner[1]),
		      THREE(corner[2]), THREE(corner[3]),
		      m.A[0][0], m.A[0][1], m.A[0][2],
		      m.A[1][0], m.A[1][1], m.A[1][2],
		      m.A[2][0], m.A[2][1], m.A[2][2],
		      m.b[0], m.b[1], m.b[2],
		      ddcamera, buttonState);
	    
	}

    } else {

	if (!DXGetImageBounds(image, NULL, NULL, &width, &height))
	    return NULL;
	DXUIMessage("IMAGE", "%s %dx%d", name, width, height);

    }
    
    DXMarkTime("uimessage");
    return image;
}

#define CACHE_APPENDAGE "CACHED_CAMERA_"

static Error
_link_message(char *link, char *where, Camera c)
{
    Point F, T;
    Vector U;
    char *tag;
    float width = 0;
    int   pixwidth;
    float aspect;
    float fov = 0;
    int projection;

    DXGetView(c, &F, &T, &U);

    if (DXGetOrthographic(c, &width, &aspect))
    {
	projection = 0;
    }
    else
    {
	DXGetPerspective(c, &fov, &aspect);
	projection = 1;
    }

    DXGetCameraResolution(c, &pixwidth, NULL);

    DXUIMessage("LINK",
	"VALUE camera %s [%f %f %f] [%f %f %f] [%f %f %f] %f %d %f %f %d",
		where,
		T.x, T.y, T.z,
		U.x, U.y, U.z,
		F.x, F.y, F.z,
		width, pixwidth, aspect, fov, projection);


    DXReference((Object)c);
    tag = DXAllocate(strlen(CACHE_APPENDAGE) + strlen(where) + 10);
    sprintf(tag, "%s%s", CACHE_APPENDAGE, where);
    DXSetCacheEntry((Object)c, CACHE_PERMANENT, tag, 0, 0);
    DXFree(tag);
    DXUnreference((Object)c);

    DXReadyToRunNoExecute(link);

    return OK;
}

static Error
_dxf_NoHardwareMessage()
{
    if (! DXGetCacheEntry("_DXD_NO_HARDWARE", 0, 0))
    {
        String str = DXNewString("no hardware rendering");
        if (! str)
            return ERROR;

        DXSetCacheEntry((Object)str,
                CACHE_PERMANENT, "_DXD_NO_HARDWARE", 0, 0);

	if (DXGetError() != ERROR_NONE)
	{
	    DXWarning(DXGetErrorMessage());
	    DXWarning("(couldn't load hardware rendering library)");
	}
	else
	    DXWarning("hardware rendering is unavailable");
    }

    DXResetError();

    return OK;
}

