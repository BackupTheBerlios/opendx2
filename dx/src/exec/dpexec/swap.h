/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



#ifndef _SWAP_H
#define _SWAP_H


extern int lockGvar(gvar *gv);
extern int unlockGvar(gvar *gv);
extern void _dxf_ExSetGVarCost(gvar *gv, double cost);
extern void _dxf_ExReclaimEnable ();


#endif /* _SWAP_H */
