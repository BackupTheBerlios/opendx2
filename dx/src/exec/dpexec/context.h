/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include "graph.h"

typedef struct Context
{
    int userId;
    int graphId;
    Program *program;
    Program **subp;
} Context;

extern Context *_dxd_exContext;

extern void _dxfCopyContext(Context *to, Context *from);
