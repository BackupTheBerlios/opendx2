/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/libdx/displayx.h,v 1.1 2000/08/24 20:04:58 davidt Exp $
 */

#include <dxconfig.h>

#ifndef _DISPLAYX_H_
#define _DISPLAYX_H_ 

Error  DXSetSoftwareWindowActive(char *, int);
Object DXDisplayX(Object, char *, char *);
Object DXDisplayX4(Object, char *, char *);
Object DXDisplayX8(Object, char *, char *);
Object DXDisplayX12(Object, char *, char *);
Object DXDisplayX15(Object, char *, char *);
Object DXDisplayX16(Object, char *, char *);
Object DXDisplayX24(Object, char *, char *);
Object DXDisplayX32(Object, char *, char *);
int    _dxf_getXDepth(char *);


#endif /* _DISPLAYX_H_ */

