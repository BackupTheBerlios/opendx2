/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/context.h,v 1.5 2000/08/11 15:28:10 davidt Exp $
 */

#include <dxconfig.h>

#ifndef _CONTEXT_H
#define _CONTEXT_H

#include "graph.h"

typedef struct Context
{
    int userId;
    int graphId;
    Program *program;
    Program **subp;
} Context;

void _dxfCopyContext(Context *to, Context *from);

#endif /* _CONTEXT_H */
