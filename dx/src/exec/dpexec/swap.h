/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "graph.h"


#ifndef _SWAP_H
#define _SWAP_H

void  _dxf_ExSetGVarCost(gvar *gv, double cost);
void  _dxf_ExReclaimEnable ();
int   _dxf_ExReclaimDisable ();
Error _dxf_ExReclaimMemory (unsigned int nbytes);
Error _dxf_ExInitMemoryReclaim ();
int   _dxf_ExReclaimingMemory();

#endif /* _SWAP_H */
