/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/swap.h,v 1.5 2000/08/11 15:28:14 davidt Exp $
 */

#include <dxconfig.h>

#ifndef _SWAP_H
#define _SWAP_H
#include "graph.h"

void  _dxf_ExSetGVarCost(gvar *gv, double cost);
void  _dxf_ExReclaimEnable ();
int   _dxf_ExReclaimDisable ();
Error _dxf_ExReclaimMemory (unsigned int nbytes);
Error _dxf_ExInitMemoryReclaim ();
int   _dxf_ExReclaimingMemory();

#endif /* _SWAP_H */
