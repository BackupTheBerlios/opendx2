/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _COMMAND_H
#define _COMMAND_H

#include "distp.h"

void _dxf_ExDeleteHost(char *host, int err, int closepeer);
void _dxf_ExDeletePeer(SlavePeers *sp, int closepeer);
void _dxf_ExAddPeer(SlavePeers *sp);
void _dxf_ExDeletePeerByName(char *host, int closepeer);
void _dxf_ExFlushGlobal(void);
void _dxf_ExFlushMacro (void);
Error _dxf_ExExecCommandStr (char *cmd);
int   _dxf_NewDPTableEntry();
void  _dxf_InitDPtableflag();

#endif /* _COMMAND_H */
