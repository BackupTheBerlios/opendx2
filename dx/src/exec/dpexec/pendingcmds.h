/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/pendingcmds.h,v 1.2 2000/08/11 15:28:13 davidt Exp $
 */

#ifndef _PENDINGCMDS_H
#define _PENDINGCMDS_H

#define PJL_KEY "__PendingObjectList"
typedef int (*PFI_P)(Private);

typedef struct
{
    char    *major;
    char    *minor;
    PFI_P   job;
    Private data;
} PendingCmd;

typedef struct
{
    Object       private;
    PendingCmd  *pendingCmdList;
    int          pendingCmdListMax;
    int          pendingCmdListSize;
} PendingCmdList;

Error _dxf_RunPendingCmds();
Error _dxf_CleanupPendingCmdList();

#endif /* _PENDINGCMDS_H */
