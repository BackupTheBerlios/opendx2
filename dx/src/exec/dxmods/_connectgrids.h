/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/_connectgrids.h,v 1.2 2001/04/27 04:25:52 davidt Exp $
 */

#include <dxconfig.h>


#ifndef  __CONNECTGRIDS_H_
#define  __CONNECTGRIDS_H_

#include <dx/dx.h>

Error _dxfConnectNearestObject(Object, Object, int, float *, float, Array);
Error _dxfConnectRadiusObject(Object, Object, float, float, Array);
Error _dxfConnectScatterObject(Object, Object, Array);

#endif /* __CONNECTGRIDS_H_ */