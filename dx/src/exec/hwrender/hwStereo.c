/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#define String dxString
#define Object dxObject
#define Angle dxAngle
#define Matrix dxMatrix
#define Screen dxScreen
#define Boolean dxBoolean

#include <dxconfig.h>


#include <dx/dx.h>

#undef String
#undef Object
#undef Angle
#undef Matrix
#undef Screen
#undef Boolean

#include <X11/Xlib.h>

#include <math.h>

#include "hwDeclarations.h"
#include "hwWindow.h"
#include "hwStereo.h"

typedef int (*PFI)();
extern PFI DXLoadObjFile(char *, char *);

/***********************************************************
 *              FIRST THE STEREO SYSTEM MODES 
 ***********************************************************/

static StereoSystemMode *_dxd_StereoSystemModes = NULL;
static int _dxd_nStereoSystemModes  = 0;
static int stereoSystemLoaded = 0;

Error
_dxfLoadStereoSystemModeFile(char *fname)
{
    int (*func)() = DXLoadObjFile(fname, "DXMODULES");
    if (! func)
    {
	DXWarning("unable to open stereo system mode file %s", fname);
	return ERROR;
    }
    else
	(*func)(&_dxd_nStereoSystemModes, &_dxd_StereoSystemModes);

    return OK;

error:
    return ERROR;
}

extern int DefaultStereoSystemModes(int *, StereoSystemMode **);

Error
_dxfLoadStereoSystemModes()
{
    char *fname;

    if ((fname = (char *)getenv("DX_STEREO_SYSTEM_FILE")) != NULL)
	if (_dxfLoadStereoSystemModeFile(fname))
	    return OK;
    
    return DXDefaultStereoSystemModes(&_dxd_nStereoSystemModes, &_dxd_StereoSystemModes);
}

Error
_dxfLoadStereoModes()
{
    if (! stereoSystemLoaded)
    {
	if (! _dxfLoadStereoSystemModes())
	    return ERROR;
	stereoSystemLoaded = 1;
    }
    return OK;
}


Error
_dxfInitializeStereoSystemMode(void *globals, dxObject args)
{
    DEFGLOBALDATA(globals);
    int mode = -1;

    if (! stereoSystemLoaded)
    {
	_dxfLoadStereoSystemModes();
	stereoSystemLoaded = 1;
    }

    if (args)
    {
	if (DXGetObjectClass(args) == CLASS_ARRAY)
	    if (! DXExtractInteger(args, &mode))
		mode = -1;
    }

    if (mode >= _dxd_nStereoSystemModes)
	mode = -1;

    if (mode != STEREOSYSTEMMODE)
    {
	if (STEREOSYSTEMMODE >= 0)
	    _dxfExitStereoSystemMode(globals);
	
	if (mode >= 0)
	{
	    StereoSystemMode *ssm = _dxd_StereoSystemModes + mode;

	    if (! (*ssm->initializeStereoSystemMode)(DPY, XWINID))
	    {
		STEREOSYSTEMMODE = -1;
		return ERROR;
	    }

	    (*ssm->createStereoWindows)(DPY, XWINID, 
				&LEFTWINDOW, &LEFTWINDOWINFO,
				&RIGHTWINDOW, &RIGHTWINDOWINFO);
	}

	STEREOSYSTEMMODE = mode;
    }

    return OK;
}

int
_dxfExitStereoSystemMode(void *globals)
{
    DEFGLOBALDATA(globals);
    if (STEREOSYSTEMMODE)
    {
	StereoSystemMode *ssm = _dxd_StereoSystemModes + STEREOSYSTEMMODE;
	(*ssm->exitStereo)(DPY, XWINID, LEFTWINDOW, RIGHTWINDOW);
	STEREOCAMERADATA  = NULL;
	LEFTWINDOW        = 0;
	RIGHTWINDOW       = 0;
    }
    return OK;
}

/***********************************************************
 *              NOW THE STEREO CAMERA MODES 
 ***********************************************************/

static void *defInitializeStereoCameraMode(void *, dxObject);
static int  defExitStereoCameraMode(void *);

static StereoCameraMode *_dxd_StereoCameraModes = NULL;
static int _dxd_nStereoCameraModes  = 0;
static int stereoCameraLoaded = 0;

Error
_dxfLoadStereoCameraModeFile(char *fname)
{
    int (*func)() = DXLoadObjFile(fname, "DXMODULES");
    if (! func)
    {
	DXWarning("unable to open stereo system mode file %s", fname);
	return ERROR;
    }
    else
	(*func)(&_dxd_nStereoCameraModes, &_dxd_StereoCameraModes);

    return OK;

error:
    return ERROR;
}

extern int DXDefaultStereoCameraModes(int *, StereoCameraMode **);

Error
_dxfLoadStereoCameraModes()
{
    char *fname;

    if ((fname = (char *)getenv("DX_STEREO_CAMERA_FILE")) != NULL)
	if (_dxfLoadStereoCameraModeFile(fname))
	    return OK;

    return DXDefaultStereoCameraModes(&_dxd_nStereoCameraModes, &_dxd_StereoCameraModes);
}


Error
_dxfInitializeStereoCameraMode(void *globals, dxObject stereoArgs)
{
    DEFGLOBALDATA(globals);
    int mode = -1;
    dxObject modeArg = NULL;
    dxObject argArg  = NULL;

    if (! stereoCameraLoaded)
    {
	_dxfLoadStereoCameraModes();
	stereoCameraLoaded = 1;
    }

    if (stereoArgs)
    {
	if (DXGetObjectClass(stereoArgs) == CLASS_GROUP)
	{
	    modeArg = DXGetMember((Group)stereoArgs, "mode");
	    argArg  = DXGetMember((Group)stereoArgs, "args");
	}
	else if (DXGetObjectClass(stereoArgs) == CLASS_ARRAY)
	{
	    modeArg = stereoArgs;
	}

	if (modeArg)
	    if (! DXExtractInteger(modeArg, &mode))
		mode = -1;
    }

    if (mode >= _dxd_nStereoCameraModes)
	mode = -1;

    if (mode != STEREOCAMERAMODE)
    {
	if (STEREOCAMERAMODE >= 0)
	    _dxfExitStereoCameraMode(globals);
	
	if (mode >= 0)
	{
	    StereoCameraMode *scm = _dxd_StereoCameraModes + mode;

	    STEREOCAMERADATA = (*scm->initializeStereoCameraMode)
				(STEREOCAMERADATA, argArg);
	    if (! STEREOCAMERADATA)
		return ERROR;
	}

	STEREOCAMERAMODE = mode;
    }
    else if (mode >= 0)
    {
	StereoCameraMode *scm = _dxd_StereoCameraModes + mode;
	STEREOCAMERADATA = (*scm->initializeStereoCameraMode)
				(STEREOCAMERADATA, argArg);
	if (! STEREOCAMERADATA)
	    return ERROR;
    }

    return OK;
}

int
_dxfCreateStereoCameras(void *globals,
		    int p, float fov, float width,
		    float *to, float *from, float *up, float Near, float Far,
		    float *lto, float *lfrom, float *lup, float **lProjection,
		    float *rto, float *rfrom, float *rup, float **rProjection)
{
    DEFGLOBALDATA(globals);

    if (STEREOCAMERAMODE >= 0)
    {
	return (*_dxd_StereoCameraModes[STEREOCAMERAMODE].createStereoCameras)(
		    STEREOCAMERADATA,
		    p, fov, width,
		    to, from, up, Near, Far,
		    lto, lfrom, lup, lProjection,
		    rto, rfrom, rup, rProjection);
    }
    else
    {
	rto[0] = lto[0] = to[0];
	rto[1] = lto[1] = to[1];
	rto[2] = lto[2] = to[2];
	rup[0] = lup[0] = up[0];
	rup[1] = lup[1] = up[1];
	rup[2] = lup[2] = up[2];
	rfrom[0] = lfrom[0] = from[0];
	rfrom[1] = lfrom[1] = from[1];
	rfrom[2] = lfrom[2] = from[2];
	*lProjection = NULL;
	*rProjection = NULL;
	return OK;
    }
}


int
_dxfExitStereoCameraMode(void *globals)
{
    DEFGLOBALDATA(globals);
    if (STEREOCAMERAMODE >= 0)
    {
	StereoCameraMode *scm = _dxd_StereoCameraModes + STEREOCAMERAMODE;
	(*scm->exitStereoCameraMode)(STEREOCAMERADATA);
	STEREOCAMERADATA  = NULL;
	STEREOCAMERAMODE  = -1;
    }
    return OK;
}

