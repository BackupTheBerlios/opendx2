/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



/* this file is NOT used with the normal dxexec - the one from
 * the executive directory is used instead.  these stubs are only
 * used for libDXlite and libDXcallm, which have primitive tasking support.
 */

#include <dx/dx.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(HAVE_SYS_TIMES_H)
#include <sys/times.h>
#endif

#if defined(HAVE_SYS_PARAM_H)
#include <sys/param.h>
#endif

#if defined(HAVE_SYS_SIGNAL_H)
#include <sys/signal.h>
#endif

#if defined(HAVE_SYS_M_WAIT_H)
#include <sys/m_wait.h>
#endif

#if defined(HAVE_SYS_WAIT_H)
#include <sys/wait.h>
#endif

#if defined(HAVE_SIGNAL_H)
#include <signal.h>
#endif

#if ibmpvs /* XXX */
#define HZ 100
#endif

typedef Error                   (*PFE)();

/*
 * Task tracing
 */

static int trace = 0;

void
DXTraceTask(int t)
{
    trace = t;
}


/*
 * Number of processors
 */

#define MAXPROC 100
#if sgi
static int nprocs = 8;
#else
static int nprocs = -1;
#endif
int pids[MAXPROC];

int
DXProcessors(int n)
{
    int old;
    if (nprocs<0) {
	/* XXX - automatic */
	nprocs = 1;
    }		       
    old = nprocs;
    if (n>0)
	nprocs = n;
    return old;
}


void 
_dxfGetProcessIds(int *childp)
{
    int i;
    
    for (i = 0; i < nprocs; i++)
	childp[i] = pids[i];
}


/*
 *
 */

static int id = 0;

int
DXProcessorId(void)
{
    return id;
}


/*
 * The following info is modified by each processor,
 * so must be in a shared area in global memory,
 * which we allocate on the first DXCreateTaskGroup.
 */

static struct taskinfo {
    struct task {
        Error(*proc)(Pointer);	/* function to do the task */
        Pointer arg;		/* pointer to argument block */
        int size;		/* size of argument block */
        float work;		/* estimate of amount of work */
	struct task *next;	/* for tasks added by other tasks only */
    } *tasks;			/* dynamically allocated */
    struct task *first, *last;	/* tasks added by other tasks only */
    volatile int ntasks;	/* count of tasks not yet started */
    int undone;			/* count of tasks not yet finished */
    Error rc;			/* return code for this task group */
    				/* XXX - return message */
    lock_type extra_lock;	/* DXlock for first, last pointers */
    lock_type task_lock;	/* unlocked when there is a task to do */
    lock_type undone_lock;	/* DXlock for undone count */
    lock_type done_flag;	/* unlocked when all tasks are done */
    int ready[MAXPROC];		/* ready flags for each proc */
} *ti;

static struct ltaskinfo {
    struct task *tasks;		/* pointer to local task info */
    int alloc;			/* number allocated */
    int ntasks;			/* count of tasks */
} lti;


/*
 * define a sorting routine
 */

#define TYPE struct task
#define LT(a,b) ((a)->work < (b)->work)
#define GT(a,b) ((a)->work > (b)->work)
#define QUICKSORT tasksort
#include "qsort.c"


/*
 * Start out with no tasks
 */

Error
DXCreateTaskGroup()
{
    static int been_here = 0;

    if (!been_here) {

	been_here = 1;

	/* allocate shared task info */
	ti = (struct taskinfo *) DXAllocateZero(sizeof(struct taskinfo));
	if (!ti)
	    return ERROR;

	/* create the locks */
	if (!DXcreate_lock(&(ti->task_lock), "task DXlock"))
	    return ERROR;
	if (!DXcreate_lock(&(ti->undone_lock), "undone DXlock"))
	    return ERROR;
	if (!DXcreate_lock(&(ti->done_flag), "extra tasks lock"))
	    return ERROR;

	/* initialize them */
	DXlock(&(ti->done_flag), 0);	/* DXunlock to signal all tasks done */
	DXlock(&(ti->task_lock), 0);	/* DXunlock to start task execution */

	/* allocate initial local task structure */
	lti.alloc = 1000;
	lti.tasks = (struct task *)
	    DXAllocateLocal(lti.alloc * sizeof(struct task));

        /*  One-time initialization  */
        ti->tasks = NULL;
        ti->ntasks = 0;
        ti->undone = 0;

    }

    /* initialize */
    ti->rc = OK;

    return OK;
}


/*
 * Record each task in the task array
 */

Error
DXAddTask(Error(*proc)(Pointer), Pointer arg, int size, double work)
{
    struct task *t;
    
    /* get a task block t */
    if (ti->tasks) {

	/* add to list of tasks generated by other tasks */
	t = (struct task *) DXAllocate(sizeof(struct task));
	if (!t)
	    return ERROR;

    } else {

	/* initial tasks generated by master */
	if (lti.ntasks >= lti.alloc) {
	    int n = lti.alloc*3/2;
	    Pointer p = DXReAllocate((Pointer)(lti.tasks),
				   n*sizeof(struct task));
	    if (!p)
		return ERROR;
	    lti.alloc = n;
	    lti.tasks = (struct task *) p;
	}
	t = lti.tasks + lti.ntasks;
	lti.ntasks++;

    }

    /* fill it in */
    t->proc = proc;
    t->arg = size==0? arg : (char *) memcpy(DXAllocate(size), arg, size);
    t->size = size;
    t->work = work;

    /* add to queue iff this is an extra task */
    if (ti->tasks) {
	if (ti->ntasks || ti->first)	/* NB: if this is the only task, we */
	    DXlock(&ti->task_lock, 0);	/* already have DXlock (see one_task) */
	if (ti->last) {
	    t->next = ti->last->next;
	    ti->last->next = t;
	} else
	    t->next = NULL;
	if (!ti->first)
	    ti->first = t;
	ti->last = t;
	DXunlock(&ti->task_lock, 0);

	DXlock(&ti->undone_lock, 0);
	ti->undone += 1;
	DXunlock(&ti->undone_lock, 0);
    } else
	t->next = NULL;

    return OK;
}

Error DXAddLikeTasks(PFE func, Pointer arg, int size, double work, int repeat)
{
    return(DXAddTask(func, arg, size, work));
}

/*
 * Do one task.  Argument indicates whether to block
 * if we can't get the task DXlock or just return.
 */

static
Error
one_task(int block)
{
    struct task *t;
    int delete;

    if (block)				/* get DXlock w/ blocking, */
	DXlock(&(ti->task_lock), 0);
    else				/* or get DXlock w/o blocking */
	if (!DXtry_lock(&(ti->task_lock), 0))
	    return OK;
    DXsyncmem();				/* make sure we're in sync */

    if (ti->ntasks) {			/* are there more sorted tasks? */
	ti->ntasks -= 1;		/* yes, remove it */
	t = &(ti->tasks[ti->ntasks]);	/* get the next task */
        delete = 0;			/* master tasks do not get deleted */
    } else if (ti->first) {		/* are there more extra tasks */
	DXlock(&ti->extra_lock, 0);	/* DXlock the queue */
	t = ti->first;			/* get the next one */
	ti->first = t->next;		/* remove from queue */
	if (ti->last == t)
	   ti->last = NULL;
	DXunlock(&ti->extra_lock, 0);	/* DXunlock the queue */
	delete = 1;			/* remember to delete it */
    }
    if (ti->ntasks || ti->first)	/* if there are more tasks, */
	DXunlock(&(ti->task_lock), 0);	/* give someone else a turn */

    DXMarkTimeLocal("start task");	/* record the time */
    if (!t->proc(t->arg))		/* do the task */
	ti->rc = ERROR;			/* return error if anyone fails */
    DXMarkTimeLocal("end task");		/* record the time */

    if (t->size)			/* if we allocated the arg block, */
	DXFree(t->arg);			/* free it */
    if (delete)				/* if we allocated the task block, */
        DXFree(t);			/* free it */
    DXsyncmem();				/* make sure we're in sync */

    DXlock(&(ti->undone_lock), id);	/* DXlock the undone count */
    if (--(ti->undone)==0)		/* decrement it */
	DXunlock(&(ti->done_flag), 0);	/* signal if all done */
    DXunlock(&(ti->undone_lock), id);	/* DXunlock the undone count */

    return OK;
}


/*
 * XXX - clean this up
 */

#if ibmpvs
#define slave() fork()
#define master() fork()
#if OPTIMIZED
#define PIN (!nopin)
#else
#define PIN 0
#endif
#else
/* this isn't going to work correctly on an mp-sgi.  the new parm
 *  to memfork is supposed to be the child number.
 */
#define slave() DXmemfork(1)		/* slaves */
#define master() fork()			/* master */
#define PIN 0
#endif

Error
DXExecuteTaskGroup()
{
    static int been_here = 0, nopin = 0;
    int i;
    int master;

    if (!been_here) {			/* create workers */

	been_here = 1;			/* once only */
	nopin = getenv("NOPIN")? 1 : 0;	/* don't fork parent: for gdb */
	DXProcessors(0);			/* make nprocs valid */

	for (id=1; id<nprocs; id++) {	/* nprocs-1 workers: */
	    pids[id] = slave();		/* fork the slave */
	    if (pids[id]==0) {		/* in child */
		ti->ready[id] = 1;	/* we're ready */
		for (;;)		/* loop forever, */
		    one_task(1);	/* do a task, blocking for each */
	    }
	}				/* this loop set id for each proc, */
	id = 0;				/* but we're still processor 0 */

#if !ibmpvs
        if (nprocs>1 || PIN) {		/* in multi-processor case, */
	    pids[0] = master();		/* fork the master */
	    if (pids[0]>0) {		/* in parent */
#if DXD_HAS_OS2_CP
		for (i=0; i<nprocs; i++)/* kill everyone */
		    DosKill(pids[i]);
#else
#if defined(intelnt)
		for (i=0; i<nprocs; i++)/* kill everyone */
		    TerminateProcess((HANDLE)pids[i],-1);

#else
#if DXD_HAS_BSD_WAIT
	        union wait status;
#else
         int status;
#endif
		wait(&status);		/* wait for child to die */
		for (i=0; i<nprocs; i++)/* kill everyone */
		    kill(pids[i], SIGKILL);
		while (wait(&status)>=0)/* wait for all children to die */
		    continue;		
#endif 
#endif    /*   DXD_HAS_OS2_CP    */
		exit(0);		/* and exit */
	    }
	}
#endif

    }

    /* If master task group, sort the tasks and copy them to global memory */
    if (lti.ntasks > 0) {
       master = 1;
       tasksort(lti.tasks, lti.ntasks);
       ti->tasks = (struct task *) DXAllocate(lti.ntasks * sizeof(struct task));
       if (!ti->tasks)
           return ERROR;
       memcpy(ti->tasks, lti.tasks, lti.ntasks * sizeof(struct task));

       ti->ntasks = lti.ntasks;        /* number of tasks */
       ti->undone = lti.ntasks;        /* number of tasks not yet done */
       lti.ntasks = 0;                 /* no more tasks here */
    }
    else if (ti->first)
       master = 0;
    else
       return OK;                      /* No tasks to start  */

    DXunlock(&(ti->task_lock), 0);	/* start task execution */
    while (ti->ntasks > 0 || ti->first){/* while there are new tasks to start,*/
	one_task(0);			/* do a task, but don't block */
	DXqflush();			/* flush its messages, if any */
    }

    /*  If master, wait for all tasks to finish  */
    if (master) {
       DXlock(&(ti->done_flag), 0);    /* wait for all tasks done */
       DXFree((Pointer)ti->tasks);     /* free allocated task storage */
       ti->tasks = NULL;               /* just in case */
    }
    DXMarkTime("end parallel");		/* timing */
    return ti->rc;			/* return error if anyone failed */
}    


Error
DXAbortTaskGroup(void)
{
    /* XXX */
    lti.ntasks = 0;
    return OK;
}

/* these don't let you control which processor they run on, like the
 * exec code does.  this means you can call the routines, but they
 * don't do what you expect.
 */

Error
_dxf_ExRunOn(int pid, Error (*func)(), Pointer arg, int size)
{
    DXCreateTaskGroup();
    DXAddTask(func, arg, size, 1.0);
    return DXExecuteTaskGroup();
}

Error
_dxf_ExRunOnAll(Error (*func)(), Pointer arg, int size)
{
    int i;

    DXCreateTaskGroup();
    for (i=0; i<nprocs; i++)
        DXAddTask(func, arg, size, 1.0);
    return DXExecuteTaskGroup();
}

