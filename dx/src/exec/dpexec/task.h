/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _TASK_H
#define _TASK_H

#include "utils.h"
#include "context.h"

typedef struct _EXTask          *EXTask;
typedef struct _EXTaskGroup     *EXTaskGroup;

/* #define TASK_TIME */

#define EX_TASK_DATA    128                     /* local task data      */
#define EX_TASK_BLOCKS  256                     /* initial task blocks  */
#define FREE_THRESHOLD  2
#define MAX_SAVED_TASKS (EX_TASK_BLOCKS)

typedef struct _EXTask
{
    EXTaskGroup         tg;                     /* control block        */
    float               work;                   /* work estimate        */
    PFE                 func;                   /* function to call     */
    int                 repeat;                 /* number of requested reps */
    int                 nocopy;                 /* just pass arg flag   */
    int                 delete;                 /* 1->not in `tasks' array */
    Pointer             arg;                    /* function argument    */
    unsigned char       data[EX_TASK_DATA];     /* local data storage   */
    Context             taskContext;            /* copy of global context */
} _EXTask;

typedef struct _EXTaskGroup
{
    lock_type           lock;
    EXTaskGroup         link;                   /* stack linkage        */
    int                 procId;                 /* Creating process ID  */
    int                 nalloc;                 /* # of tasks allocated */
    int                 nused;                  /* # of tasks used      */
    int                 ntodo;                  /* # of tasks to do     */
    EXTask              tasks;                  /* the task blocks      */
    float               minwork;                /* smallest work est.   */
    float               maxwork;                /* largest  work est.   */
    int                 sync;                   /* synchronous flag     */
    ErrorCode           error;                  /* for error return     */
    char                *emsg;                  /* for error return     */
} _EXTaskGroup;

typedef struct
{
    float       work;
    EXTask      task;
} WorkIndex;

void            _dxf_ExPrintTask                (EXTask t);
void            _dxf_ExPrintTaskGroup   (EXTaskGroup tg);
Error 		_dxf_ExInitTaskPerProc();
Error 		_dxf_ExInitTask(int n);


#endif /* _TASK_H */
