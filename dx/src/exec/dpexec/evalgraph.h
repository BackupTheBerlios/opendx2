/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _EVALGRAPH_H
#define _EVALGRAPH_H

#include "graph.h"

typedef struct qsr_args {
    char *procid;
    ProgramVariable *pv;
    int index;
}  qsr_args;

extern int        *_dxd_exKillGraph; /* from evalgraph.c */
extern int        *_dxd_exBadFunc;   /* from evalgraph.c */

Error       _dxf_ExQueueGraphInit();
void        _dxf_ExQueueGraph(Program * p);
void        DXLoopDone(int done);
int 	    _dxf_ExIsExecuting();

#endif /* _EVALGRAPH_H */