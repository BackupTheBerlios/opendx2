/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


/*---------------------------------------------------------------------------*\
 $Source: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/hwrender/hwPortHandle.c,v $

\*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

#ifndef DXD_WIN
#include <sys/param.h>
#endif

#if ibm6000
#include <sys/stat.h> 
#include <sys/ldr.h>
#endif

#if defined(sgi)
#include <get.h>
#include <stdlib.h>
#endif


#include "hwDeclarations.h"
#include "hwMemory.h"

#include "hwDebug.h"

extern tdmInteractorEchoP   	_dxf_initInteractorEchoPort ();

int
_dxfHWload(tdmPortHandleP (**initPP)(Display*, char*,void(*)(tdmPortHandleP)), Display *);

#ifndef STANDALONE
/*
 * _dxfExportHwddVersion
 * 
 * For DX versions greated than 2.0.1 this function should be called by the
 * port initialization code with the value of DX_HWDD_INTERFACE_VERSION
 * compiled into the load module code.
 *
 * This allows the common code to call only those functions defined for a
 * given version of DXhwdd.o
 */

int			_dxd_execHwddVersion,_dxd_lmHwddVersion = 0;

Error
_dxfExportHwddVersion(int version)
{
  ENTRY(("_dxfExportHwddVersion(%d)",version));

  _dxd_lmHwddVersion = version;

  EXIT(("OK"));
  return OK;
}

/*
 * _dxfNewPortHandle:
 * This function is responsible for deciding the appropriate device dependent
 * portHandle to use. This function should load the device dependented library
 * (if necessary) and call the appropriate device dependent _dxfInitPortHandle.
 *
 * If the architecture allows (requires) more than one device dependent libary,
 * this function may use the value of the 'format' parameter and information
 * queried from the selected hardware to select an appropriate port handle
 * definition.
 */

tdmPortHandleP
_dxfNewPortHandle(tdmParsedFormatP format, Display **dpy)
{
  /*
   *  Return NULL if hardware rendering is not available.  
   */

  tdmPortHandleP	ret = NULL;
  tdmPortHandleP	(*_initP)();

  ENTRY(("_dxfNewPortHandle(0x%x, 0x%x)", format, dpy));

  if (!*dpy) {
    if (((*dpy) = XOpenDisplay(format->where)) == NULL){
      /* can't open display '%s'. */
      DXSetError(ERROR_BAD_PARAMETER,"#13720",format->where);
      goto error;
    } 
  }

  if(! _dxfHWload(&_initP, *dpy)) 
    goto error;


  PRINT(("_initP = 0x%x",_initP));
  PRINT(("*dpy = 0x%x",*dpy));
  PRINT(("format->where  = %s",format->where));
  if(!(ret = (_initP)(*dpy, format->where)))
    goto error;
  
#if !defined(DEBUG)
  /* Check version of portHandle */

  /* lmHwddVersion should have been set by (*init) calling 
   * _dxfExportHwddVersion (will default to 0 if DXhwdd < 2.0.1)
   */
  DXHwddInterface(&_dxd_execHwddVersion);
  PRINT(("exec Version = %d,", _dxd_execHwddVersion));
  PRINT((" lm version = %d\n", _dxd_lmHwddVersion));
  if(_dxd_lmHwddVersion < _dxd_execHwddVersion) {
    DXErrorGoto(ERROR_UNEXPECTED,"#13920");
  }
#endif

  ret->dpy = (void*)*dpy;

  EXIT(("ret = 0x%x",ret));
  return ret;

error:
  if(ret) (ret->uninitP)(ret);
  ret = NULL;

  if(*dpy) {
      XSync(*dpy,0);
      XCloseDisplay(*dpy);
    }

  EXIT(("ret = NULL"));
  return NULL;
}

/*
 * _dxfNewPortHandle:
 * Deletes a port handle created by _dxfNewPortHandle.
 */
void
_dxfDeletePortHandle(tdmPortHandleP portHandle)
{
  Display *dpy = (Display*)portHandle->dpy;

  ENTRY(("_dxfDeletePortHandle(0x%x)", portHandle));

  if (portHandle) {
    (portHandle->uninitP)(portHandle);
    if (dpy) {
      XSync(dpy,0);
      XCloseDisplay(dpy);
    }
  }
  EXIT((""));
}

#endif
