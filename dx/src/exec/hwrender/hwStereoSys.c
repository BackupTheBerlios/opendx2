/* 
 * (C) COPYRIGHT International Business Machines Corp. 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 * 
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#define String dxString
#define Object dxObject
#define Angle dxAngle
#define Matrix dxMatrix
#define Screen dxScreen
#define Boolean dxBoolean

#include <dx/dx.h>

#undef String
#undef Object
#undef Angle
#undef Matrix
#undef Screen
#undef Boolean

#include <X11/Xlib.h>

#include <math.h>
#include <stdlib.h>     /* for getenv prototype */

#include "hwDeclarations.h"
#include "hwWindow.h"
#include "hwStereo.h"

/************** Default Stereo System Modes ********************
 * Default intialization is no system initialization. Default exit
 * is to delete the left and right windows if they differ from the
 * frame.  Two default window modes, both viewports inside the frame.
 * The first is side-by-size, dividing the frame in half.  The second
 * is top/bottom, with the top in the topmost 492 scanlines of the 
 * window and the bottom in the lowest 492 scan lines.
 ****************************************************************/

static int  defInitializeStereoSystemMode0(Display *, Window);
static int  defExitStereoSystem0(Display *, Window, Window, Window);
static int  defCreateStereoWindows0(Display *, Window,
					Window *, WindowInfo *,
					Window *, WindowInfo *);

static int  defInitializeStereoSystemMode1(Display *, Window);
static int  defExitStereoSystem1(Display *, Window, Window, Window);
static int  defCreateStereoWindows1(Display *, Window,
					Window *, WindowInfo *,
					Window *, WindowInfo *);

static int  defInitializeStereoSystemMode2(Display *, Window);
static int  defExitStereoSystem2(Display *, Window, Window, Window);
static int  defCreateStereoWindows2(Display *, Window,
					Window *, WindowInfo *,
					Window *, WindowInfo *);

static StereoSystemMode _defaultStereoSystemModes[3];

int 
DXDefaultStereoSystemModes(int *n, StereoSystemMode **ssms)
{
    *ssms = _defaultStereoSystemModes;

    (*ssms)[0].initializeStereoSystemMode = defInitializeStereoSystemMode0;
    (*ssms)[0].exitStereo 		  = defExitStereoSystem0;
    (*ssms)[0].createStereoWindows 	  = defCreateStereoWindows0;

    (*ssms)[1].initializeStereoSystemMode = defInitializeStereoSystemMode1;
    (*ssms)[1].exitStereo 		  = defExitStereoSystem1;
    (*ssms)[1].createStereoWindows 	  = defCreateStereoWindows1;

    (*ssms)[2].initializeStereoSystemMode = defInitializeStereoSystemMode2;
    (*ssms)[2].exitStereo 		  = defExitStereoSystem2;
    (*ssms)[2].createStereoWindows 	  = defCreateStereoWindows2;

    *n = 3;
    return OK;
}

static int
defInitializeStereoSystemMode0(Display *dpy, Window w)
{
    return OK;
}

static int
defExitStereoSystem0(Display *dpy, Window frame, Window left, Window right)
{
    if (left != frame)
	XDestroyWindow(dpy, left);
    if (right != frame)
	XDestroyWindow(dpy, right);
    return OK;
}

Error
defCreateStereoWindows0(Display *dpy, Window frame,
		Window *left, WindowInfo *leftWI,
		Window *right, WindowInfo *rightWI)
{
    XWindowAttributes xwattr;
    XGetWindowAttributes(dpy, frame, &xwattr);

    *left = frame;
    leftWI->xOffset = 0;
    leftWI->yOffset = 0;
    leftWI->xSize = xwattr.width/2;
    leftWI->ySize = xwattr.height;

    leftWI->aspect = xwattr.height / xwattr.width;

    *right = frame;
    rightWI->xOffset = xwattr.width/2;
    rightWI->yOffset = 0;
    rightWI->xSize = xwattr.width/2;
    rightWI->ySize = xwattr.height;

    rightWI->aspect = xwattr.height / xwattr.width;

    return OK;
}

static int
defInitializeStereoSystemMode1(Display *dpy, Window w)
{
#ifdef sgi
    system("/usr/gfx/setmon -n STR_RECT");
#endif
    return OK;
}

static int
defExitStereoSystem1(Display *dpy, Window frame, Window left, Window right)
{
#ifdef sgi
    system("/usr/gfx/setmon -n 60HZ");
#endif
    if (left != frame)
	XDestroyWindow(dpy, left);
    if (right != frame)
	XDestroyWindow(dpy, right);
    return OK;
}

Error
defCreateStereoWindows1(Display *dpy, Window frame,
		Window *left, WindowInfo *leftWI,
		Window *right, WindowInfo *rightWI)
{
    XWindowAttributes xwattr;
    XGetWindowAttributes(dpy, frame, &xwattr);

    *left = frame;
    leftWI->xOffset = 0;
    leftWI->yOffset = 0;
    leftWI->xSize = xwattr.width;
    leftWI->ySize = 492;

    leftWI->aspect = 492.0 / xwattr.width;

    *right = frame;
    rightWI->xOffset = 0;
    rightWI->yOffset = xwattr.height-492;
    rightWI->xSize = xwattr.width;
    rightWI->ySize = 492;

    rightWI->aspect = 492.0 / xwattr.width;

    return OK;
}


static int
defInitializeStereoSystemMode2(Display *dpy, Window w)
{
    char *cmd = getenv("DX_INIT_STEREO_COMMAND");
    if (cmd)
	system(cmd);

    return OK;
}

static int
defExitStereoSystem2(Display *dpy, Window frame, Window left, Window right)
{
    char *cmd = getenv("DX_EXIT_STEREO_COMMAND");
    if (cmd)
	system(cmd);

    if (left != frame)
	XDestroyWindow(dpy, left);
    if (right != frame)
	XDestroyWindow(dpy, right);
    return OK;
}

Error
defCreateStereoWindows2(Display *dpy, Window frame,
		Window *left, WindowInfo *leftWI,
		Window *right, WindowInfo *rightWI)
{
    XWindowAttributes xwattr;
    XGetWindowAttributes(dpy, frame, &xwattr);

    *left = frame;
    leftWI->xOffset = 0;
    leftWI->yOffset = 0;
    leftWI->xSize = xwattr.width;
    leftWI->ySize = xwattr.height/2;

    rightWI->aspect = ((float)rightWI->ySize) / rightWI->xSize;

    *right = frame;
    rightWI->xOffset = 0;
    rightWI->yOffset = xwattr.height/2;
    rightWI->xSize = xwattr.width;
    rightWI->ySize = xwattr.height/2;

    rightWI->aspect = ((float)rightWI->ySize) / rightWI->xSize;

    return OK;
}

