/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



/* on an MP machine, this file defines the lock routines.  on all other
 * machines, there are stubs at the end of this file which do nothing,
 * so this file doesn't need to be edited for single processor architectures.
 */
#include <dx/dx.h>


#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#include <stdlib.h>

#ifdef DEBUGGED
#    define STATUS_LIGHTS 1
#endif
#ifdef STATUS_LIGHTS
#include "../dpexec/status.h"
#include "../dpexec/utils.h"
#endif


#if alphax
#define lockcode

#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/mman.h>

int _dxf_initlocks(void)
{
    return OK;
}

int DXcreate_lock(lock_type *l, char *name)
{
    if(!msem_init(l, MSEM_UNLOCKED))
        DXErrorReturn(ERROR_INTERNAL, "Error creating lock");

    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    if(DXtry_lock(l, 0)) {
       msem_remove(l);
       return OK;
    }
    else
       DXErrorReturn(ERROR_INTERNAL, "attempt to destroy locked lock");
}

int DXlock(lock_type *l, int who)
{
    if(msem_lock(l, 0) != 0)
        DXErrorReturn(ERROR_INTERNAL, "Failed attempt to lock lock");

    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    if(msem_lock(l, MSEM_UNLOCKED) != 0)
        return ERROR;

    return OK;
}

int DXunlock(lock_type *l, int who)
{
    if(msem_unlock(l, 0) != 0)
        DXErrorReturn(ERROR_INTERNAL, "Failed to unlock lock");
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}
#endif

/*
 * Locks using Sun's MUTEX
 */
#if DXD_USE_MUTEX_LOCKS && !defined(lockcode)

#define lockcode

#include <synch.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

/*
 * Strangely, with the mutex locks, we've got to replace sleep().
 * Sleep in libthreads.a from Solaris 2.3 doesn't work if you replace
 * the signal handler.  It exits the second time it's called.  The
 * following program quits when compiled cc -o x x.c -lthreads:
 * 
 * #include <unistd.h>
 * #include <stdlib.h>
 * #include <signal.h>
 * 
 * #define SLEEP_LOCKED 1
 * 
 * void main()
 * {
 *     int i;
 *     void (*s)(int) = SIG_IGN;
 * 
 *     for (i = 0; i < 10; ++i) {
 * 	s = signal(SIGALRM, SIG_IGN);
 * 	printf("signal returns 0x%08x\n", s);
 * 	signal(SIGALRM, s);
 * 	printf("sleep(%d)\n", SLEEP_LOCKED);
 * 	sleep(SLEEP_LOCKED);
 * 	printf("finish sleep(%d)\n", SLEEP_LOCKED);
 *     }
 *     printf("exiting thrsig\n");
 * }
 */
static void sleeper(int sig)
{
}
uint sleep(uint secs)
{
    void (*s)(int);

    if (secs == 0)
	return 0;
    s = signal(SIGALRM, sleeper);
    alarm(secs);
    pause();
    signal(SIGALRM, s);

    return 0;
}
    

int _dxf_initlocks(void)
{
    return OK;
}


int DXcreate_lock(lock_type *l, char *name)
{
    lwp_mutex_t *mp = (lwp_mutex_t*) l;
    lwp_mutex_t template = SHAREDMUTEX;
    *mp = template;
    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    return OK;
}

static void wakeupAndSleep(int thing)
{
    signal(SIGALRM, wakeupAndSleep);
}

int DXlock(lock_type *l, int who)
{
    lwp_mutex_t *mp = (lwp_mutex_t*) l;
    int sts;
    struct itimerval tv;
    struct itimerval otv;
    void (*oldSignal)(int);

    if ((sts = _lwp_mutex_trylock(mp)) != 0) {
	if (sts == EBUSY) {
#ifdef STATUS_LIGHTS
	    int old_status = get_status();
	    set_status(PS_DEAD);
#endif
	    oldSignal = signal(SIGALRM, wakeupAndSleep);
	    tv.it_value.tv_sec = 1;
	    tv.it_value.tv_usec = 0;
	    tv.it_interval.tv_sec = 1;
	    tv.it_interval.tv_usec = 0;
	    setitimer(ITIMER_REAL, &tv, &otv);
	    if ((sts = _lwp_mutex_lock(mp)) != 0) {
		/* Cancel timer */
		setitimer(ITIMER_REAL, &otv, NULL);
		signal(SIGALRM, oldSignal);

		DXSetError(ERROR_UNEXPECTED, strerror(sts));
#ifdef STATUS_LIGHTS
		set_status(old_status);
#endif
		return ERROR;
	    }
	    else {
		/* Cancel timer */
		setitimer(ITIMER_REAL, &otv, NULL);
		signal(SIGALRM, oldSignal);
#ifdef STATUS_LIGHTS
		set_status(old_status);
#endif
	    }
	}
	else {
	    DXSetError(ERROR_UNEXPECTED, strerror(sts));
	    return ERROR;
	}
    }
    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    lwp_mutex_t *mp = (lwp_mutex_t*) l;
    int sts;
    if ((sts = _lwp_mutex_trylock(mp)) != 0) {
	if (sts != EBUSY) {
	    DXSetError(ERROR_UNEXPECTED, strerror(sts));
	}
	return ERROR;
    }
    return OK;
}

int DXunlock(lock_type *l, int who)
{
    lwp_mutex_t *mp = (lwp_mutex_t*) l;
    int sts;
    if ((sts = _lwp_mutex_unlock(mp)) != 0) {
	if (sts != EBUSY) {
	    DXSetError(ERROR_UNEXPECTED, strerror(sts));
	}
	return ERROR;
    }
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}

#endif
/*
 * Real locks for PVS using OS locks
 */

#if ibmpvs && !defined(lockcode)

#include <sys/svs.h>

#define lockcode

#define LOCKED 0
#define UNLOCKED 1
#define WHO (who+1)


Error _dxf_initlocks(void)
{
    return OK;
}

int DXcreate_lock(lock_type *l, char *name)
{
    simple_lock_init(l);
    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    return OK;
}

int DXlock(lock_type *l, int who)
{
#if DEBUGGED
    int v;
    simple_lock(l, WHO);
    if ((v= *l) != WHO) {
	DXWarning("DXlock %x didn't take (expected %d, saw %d)",l,WHO,v);
    }
    return OK;
#else
    simple_lock(l, WHO);
    return OK;
#endif
}

int DXtry_lock(lock_type *l, int who)
{
#if DEBUGGED
    int v;
    if (simple_try_lock(l, WHO)) {
	if ((v= *l) != WHO) {
	    DXWarning("DXtry_lock %x didn't take (expected %d, saw %d)", l,WHO,v);
	}
	return OK;
    } else
	return ERROR;
#else
    return simple_try_lock(l, WHO);
#endif
}


int DXunlock(lock_type *l, int who)
{
#if DEBUGGED
    if (*l != WHO) {
	DXWarning("invalid DXunlock of %x (expected %d, saw %d)", l, WHO, *l);
    }
#endif
    simple_unlock(l);
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    return fetch_and_add(p, value);
}

#endif /* ibmpvs */



/*
 * real MP locks for '6000, for the SMP
 */

#if ibm6000 && !defined (lockcode)

#define lockcode

#define LOCKED    0
#define UNLOCKED  1
#define DEADLOCK -1

int _dxf_initlocks(void)
{
    return OK;
}

int DXcreate_lock(lock_type *l, char *name)
{
    *l = UNLOCKED;
    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    if (*l == LOCKED)
       DXErrorReturn(ERROR_INTERNAL, "attempt to destroy locked lock");
    if (*l == DEADLOCK)
       DXErrorReturn(ERROR_INTERNAL, "attempt to destroy destroyed lock");
    *l = DEADLOCK;
    return OK;
}

int DXlock(lock_type *l, int who)
{
    while (cs(l, UNLOCKED, LOCKED)) {
	int v = *l;
	if (v!=UNLOCKED && v!=LOCKED)
	    DXErrorReturn(ERROR_INTERNAL, "bad lock");
	usleep(500 /* microseconds */);    /* spin loop waiting for lock */
    }
    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    if (cs(l, UNLOCKED, LOCKED))
       return ERROR;
    else
       return OK;
}

int DXunlock(lock_type *l, int who)
{
    if (*l == DEADLOCK)
       DXErrorReturn(ERROR_INTERNAL, "attempt to unlock destroyed lock");
    *l = UNLOCKED;
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}

#endif



/*
 * Real locks for sgi MP
 */

#if sgi && !defined(lockcode)

#define lockcode

#if !OLDLOCKS

#include <ulocks.h>

static usptr_t *usptr = NULL;
#define L (*(ulock_t*)l)

/* a pool of real locks */
#define N 16
ulock_t pool[N];

/* manipulating a software lock */
#define CONS(pool,value)  (((pool)<<8) | 0xE | (value))
#define POOL(l)	  	  (((*l)>>8)&0xFF)
#define LOCKPOOL(l)	  ussetlock(pool[POOL(l)])
#define UNLOCKPOOL(l)	  usunsetlock(pool[POOL(l)])
#define LOCK(l)		  ((*l) |= 1)
#define UNLOCK(l)	  ((*l) &= ~1)
#define LOCKED(l)	  ((*l) & 1)
#define VALID(l)	  ((((*l)&~0xFFFF)==0) && (((*l)&0xE)==0xE))

int _dxf_initlocks(void)
{
    static int been_here = 0;
    static char tmp[] = "/tmp/loXXXXXX";
    char *mktemp();
    int i;

    if (!been_here) {
	been_here = 1;
	mktemp(tmp);
	usconfig(CONF_INITUSERS, 64);
	usptr = usinit(tmp);
	if (!usptr)
	    DXErrorReturn(ERROR_NO_MEMORY, "Can't create us block for locks");
	unlink(tmp);

	/* create a pool of N real locks */
	for (i=0; i<N; i++) {
	    pool[i] = usnewlock(usptr);
	    if (!pool[i])
		DXErrorReturn(ERROR_NO_MEMORY, "can't create lock pool");
	}
    }

    return OK;
}

int DXcreate_lock(lock_type *l, char *name)
{
    static int been_here = 0;
    int i;

    if (!been_here) {
	been_here = 1;
	if (!_dxf_initlocks())
	    return NULL;
    }

    i = ((((int)(l))>>4) ^ (((int)(l))>>12) ^ (((int)(l))>>20)) & (N-1);
    /*DXMessage("new lock off of pool id %d", i);*/
    *l = CONS(i, 0);

    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    *l = -1;
    return OK;
}

int DXlock(lock_type *l, int who)
{
    if (!VALID(l))
	DXErrorReturn(ERROR_BAD_PARAMETER, "bad lock");
    for (;;) {
	while (LOCKED(l))
	    sginap(0);
	LOCKPOOL(l);
	if (LOCKED(l))
	    UNLOCKPOOL(l);
	else
	    break;
    }
    LOCK(l);
    UNLOCKPOOL(l);
    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    if (!VALID(l))
	DXErrorReturn(ERROR_BAD_PARAMETER, "bad lock");
    if (LOCKED(l))
	return ERROR;
    LOCKPOOL(l);
    if (LOCKED(l)) {
	UNLOCKPOOL(l);
	return ERROR;
    }
    LOCK(l);
    UNLOCKPOOL(l);
    return OK;
}

int DXunlock(lock_type *l, int who)
{
    if (!VALID(l))
	DXErrorReturn(ERROR_BAD_PARAMETER, "bad lock");
    LOCKPOOL(l);
    UNLOCK(l);
    UNLOCKPOOL(l);
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}

#else /* !NEWLOCKS */

#include <ulocks.h>

static usptr_t *usptr = NULL;
#define L (*(ulock_t*)l)

int _dxf_initlocks(void)
{
    static int been_here = 0;
    static char tmp[] = "/tmp/loXXXXXX";
    char *mktemp();

    if (!been_here) {
	been_here = 1;
	mktemp(tmp);
	usconfig(CONF_INITUSERS, 64);
	usptr = usinit(tmp);
	if (!usptr)
	    DXErrorReturn(ERROR_NO_MEMORY, "Can't create us block for locks");
	unlink(tmp);
    }
    return OK;
}

int DXcreate_lock(lock_type *l, char *name)
{
    static int been_here = 0;

    if (!been_here) {
	been_here = 1;
	if (!_dxf_initlocks())
	    return NULL;
    }

    L = usnewlock(usptr);
    if (!L)
	return NULL;
    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    if (!DXtry_lock(l, 0))
	DXErrorReturn(ERROR_INTERNAL, "Attempt to destroy a locked lock");
    usfreelock(L, usptr);
    return OK;
}

int DXlock(lock_type *l, int who)
{
    ussetlock(L);
    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    return uscsetlock(L, _USDEFSPIN);
}

int DXunlock(lock_type *l, int who)
{
    usunsetlock(L);
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}

#endif /* NEWLOCKS */
#endif /* sgi */



/*
 * fake locks for UP machines
 */

#if !defined(lockcode)

#define LOCKED 0
#define UNLOCKED 1

int _dxf_initlocks(void)
{
    return OK;
}

int DXcreate_lock(lock_type *l, char *name)
{
    *l = UNLOCKED;
    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    if (*l==LOCKED)
	DXErrorReturn(ERROR_INTERNAL, "attempt to destroy locked lock");
    return OK;
}

int DXlock(lock_type *l, int who)
{
    if (*l==LOCKED)
	DXErrorReturn(ERROR_INTERNAL, "attempt to lock locked lock");
    *l = LOCKED;
    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    if (*l==UNLOCKED){
	*l = LOCKED;
	return OK;
    }
    else
	return ERROR;
}

int DXunlock(lock_type *l, int who)
{
    *l = UNLOCKED;
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}

#endif





#if defined(DXD_WIN_SMP)  && defined(THIS_IS_COMMENTED)

/*
	Define this to enable DXD_WIN    SMP . 
	This locking is not well tested



#define lockcode   1
*/




#define LOCKED 1
#define UNLOCKED 2

#define	DX_MAX_LOCKS	128


struct DXWinLock
{
    int     ISLocked;
    int     ByWhom;
    int    *dxLockPtr;
    int     ThreadID;
    HANDLE  thisMutex, thisEvent;
} ;

static struct DXWinLock  DXLocks[DX_MAX_LOCKS];

HANDLE	evLock, evUnlock, evHandle[10];

static int GetLockID(int *l)
{
     int i, id, tid;

    id = -1;
    tid = DXGetPid();
    for(i = 0; i < DX_MAX_LOCKS; i++)
    {
	if (DXLocks[i].dxLockPtr == l)
	    return i;
    }
    return -1;
}
static int IsLocked(int *l)
{
     int i;

    i = GetLockID(l);
    if(i == -1)
	    return 0;
    else
	    return 1;

    if (DXLocks[i].dxLockPtr == l)
    {
	if(DXLocks[i].ISLocked == LOCKED)
	    return 1;
	else
	    return 0;
    }
    printf("Error in IsLock() %c \n", 7);
    return 0;
}
static int GetFreeLock(int *l)
{
    int i;
    static int IamHere = 0;

    i = DXGetPid();
    while(IamHere)
	Sleep(i);

    IamHere = 1;
    for(i = 0; i < DX_MAX_LOCKS; i++) {
    	if (DXLocks[i].dxLockPtr == NULL) {
    	    DXLocks[i].dxLockPtr = l;
    	    IamHere = 0;
    	    return i;
    	}
    }
    //  DXErrorReturn(ERROR_INTERNAL, "DX_MAX_LOCKS reached ");
    IamHere = 0;
    return -1;

}

int _dxf_initlocks(void)
{
    static int been_here = 0;
    int i;

    if(!been_here)
    {
    	been_here = 1;
    	for(i = 0; i < DX_MAX_LOCKS; i++) {
    	    DXLocks[i].ISLocked = UNLOCKED;
    	    DXLocks[i].ByWhom = -1;
    	    DXLocks[i].dxLockPtr = NULL;
    	    DXLocks[i].thisMutex = NULL;
    	    DXLocks[i].thisMutex = CreateMutex(NULL, FALSE, NULL);
    	    DXLocks[i].thisEvent = CreateEvent(NULL, 0, 1000, NULL);
    	    SetEvent(DXLocks[i].thisEvent);
    	}
	evLock = CreateEvent(NULL, 0, 1000, NULL);
	evUnlock = CreateEvent(NULL, 0, 1000, NULL);

	SetEvent(evLock);
	SetEvent(ev1c UnlLock);

	for (i = 0; i < 10; i++) {
	    evHandle[i] = CreateEvent(NULL, 0, 1000, NULL);
	    SetEvent(evHandle[i]);
	}
    }

    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    //	if (*l==LOCKED)
//		DXErrorReturn(ERROR_INTERNAL, "attempt to destroy locked lock");
    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
     int id;

    /*  if (*l==UNLOCKED){   */
    if(!IsLocked(l)) {
	/*  *l = LOCKED;   */
	DXlock(l, who);
	return OK;
    }
    else
	return ERROR;
}
int DXcreate_lock(lock_type *l, char *name)
{
    int i;
     static  int IamHere = 0;

    return OK;

    /*
    tid = DXGetPid();
    while(IamHere)
	 Sleep(tid);

    IamHere = 1;

    i = GetFreeLock();
    if(i >= 0)
    {
	DXLocks[i].ISLocked = UNLOCKED;
	DXLocks[i].dxLockPtr = l;
    }
    else
    {
	printf("Error in DXcreate_lock()  \n");
	return ERROR;
    }
    *l = UNLOCKED;
    IamHere = 0;
    return OK;
    */
}

int DXlock(int *l, int who)
{
    int tid, id, j, i;
    static int IamHere = 0;

    /*
    i = DXGetPid();
    while(IamHere)
	    Sleep(i);
    */
    Sleep(i);
    WaitForSingleObject(evLock, i);
    ResetEvent(evLock);

    tid = IamHere = DXGetPid();

    id = GetLockID(l);
    while (IsLocked(l))
    {
	 /*  locked by myself     */
    	if(tid == DXLocks[id].ThreadID)
    	{
    	    printf("RELOCK COND unlocking %d %d  %c \n", who, *l, 7);
    	    IamHere = 0;
    	    return OK;
    	}

    	/*  locked by someone else     WAIT   */
    	i = WaitForSingleObject(DXLocks[id].thisEvent, tid*10);
    }

    id = GetFreeLock(l);

    ResetEvent(DXLocks[id].thisEvent);

    DXLocks[id].ThreadID = tid;
    DXLocks[id].ByWhom = who;
    DXLocks[id].ISLocked = LOCKED;
    DXLocks[id].dxLockPtr = l;

    *l = LOCKED;

    IamHere = 0;
    return OK;

    
}


int DXunlock(int *l, int who)
{
    int id, tid;
    static short IamHere = 0;

    tid = DXGetPid();
    while(IamHere)
	 Sleep(tid);

    tid = IamHere = DXGetPid();;


    id = GetLockID(l);
    if(id < 0) {
    	printf("Error in Unlock %c \n", 7);
    	IamHere = 0;
    	return ERROR;
    }

    if(tid == DXLocks[id].ThreadID) {
    	//  CloseHandle(DXLocks[id].thisMutex);
    	//  DXLocks[id].thisMutex = NULL;
    	DXLocks[id].dxLockPtr = NULL;
    	DXLocks[id].ThreadID = 0;
    	DXLocks[id].ByWhom = 0;
    	DXLocks[id].ISLocked = UNLOCKED;
    	ReleaseMutex(DXLocks[id].thisMutex);
        SetEvent(DXLocks[id].thisEvent);
    }
    else {
	    printf("Someone trying to unlock me %c \n", 7);
    }
    IamHere = 0;
    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
     int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}

#endif     /*     DXD_WIN     */
