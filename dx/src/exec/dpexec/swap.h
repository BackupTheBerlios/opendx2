/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/swap.h,v 1.7 2002/05/23 02:11:23 rhh Exp $
 */

#include <dxconfig.h>

#ifndef _SWAP_H
#define _SWAP_H
#include "graph.h"

void  _dxf_ExSetGVarCost(gvar *gv, double cost);
void  _dxf_ExReclaimEnable ();
int   _dxf_ExReclaimDisable ();
int   _dxf_ExReclaimMemory (ulong nbytes);
Error _dxf_ExInitMemoryReclaim ();
int   _dxf_ExReclaimingMemory();

#endif /* _SWAP_H */
