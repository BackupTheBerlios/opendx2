/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _NODEB_H
#define _NODEB_H

#include "parse.h"

int _dxf_ExWriteTree(struct node *pt, int fd);
struct node *_dxf_ExReadTree(int fd, int swap);

#endif /* _NODEWRITEB_H */
