/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/nodeb.h,v 1.2 2000/08/11 15:28:12 davidt Exp $
 */

#ifndef _NODEB_H
#define _NODEB_H

#include "parse.h"

int _dxf_ExWriteTree(struct node *pt, int fd);
struct node *_dxf_ExReadTree(int fd, int swap);

#endif /* _NODEWRITEB_H */
