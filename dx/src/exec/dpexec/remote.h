/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _REMOTE_H
#define _REMOTE_H

#include <dx/dx.h>

int _dxfExRemoteExec(int dconnect, char *host, char *ruser, int r_argc,
                     char **r_argv, int outboard);
Error DXOutboard (Object *in, Object *out);
Error _dxf_ExDeleteReallyRemote (char *procgroup, char *name, int instance);
Error _dxf_ExDeleteRemote (char *name, int instance);
int   _dxf_ExInitRemote (void);

#endif /* _REMOTE_H */