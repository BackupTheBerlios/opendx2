/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#ifdef DXD_WIN
#include <io.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h> 

#include <winsock.h>

#else
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#endif

#include <dx/dx.h>

#include "utils.h"
#if DXD_NEEDS_SYS_SELECT_H
#include <sys/select.h>
#endif

#define	MAXRIH		128
#define	MAXRCH		32

typedef struct
{
    PFE		proc;
    int		fd;
    Pointer	arg;
    PFI		check;
    int		flag;
    int		isWin;
	void	*dpy;
} _EXRIH, *EXRIH;


static int		nRIH	= 0;
static _EXRIH		handlers[MAXRIH];
static lock_type	*rih_lock;
static int		*rih_count;

static Error RIHDelete (int fd);
static Error RIHInsert (Error (*proc) (int, Pointer),
	    int fd, Pointer arg, int (*check) (int, Pointer));


typedef struct
{
    PFE		proc;
    Pointer	arg;
    int		when;
} _EXRCH, *EXRCH;

static int		nRCH	= 0;
static _EXRCH		callbacks[MAXRCH];
static lock_type	*rch_lock;
static int		*rch_count;

static Error RCHDelete (Pointer arg);
static Error RCHInsert (Error (*proc) (Pointer), Pointer arg, int when);


Error _dxf_initRIH (void)
{
/* as far as i can tell, this isn't needed anymore.  nsc 18feb94 */
    rih_lock = (lock_type *) DXAllocate (sizeof (lock_type));
    if (rih_lock == NULL)
	return (ERROR);
    if (DXcreate_lock (rih_lock, "input handlers") != OK)
	    return (ERROR);

    rih_count = (int *) DXAllocate (sizeof (int));
    if (rih_count == NULL)
	return (ERROR);
    *rih_count = 0;

    return (OK);
}


Error DXRegisterInputHandler (Error (*proc) (int, Pointer), int fd, Pointer arg)
{
    return ((proc == NULL) ? RIHDelete (fd) : RIHInsert (proc, fd, arg, NULL));
}

Error
DXRegisterInputHandlerWithCheckProc(Error(*proc)(int, Pointer),
                      int (*check)(int, Pointer), int fd, Pointer arg)
{
    return ((proc == NULL) ? RIHDelete (fd) : RIHInsert (proc, fd, arg, check));
}

int _dxf_ExCheckRIHBlock (int input)
{
    int			i;
    fd_set		fdset;
    fd_set		wfdset;
    EXRIH		r;
    int			ret	= FALSE;
    Error		rval;
    int			mval;
    int			fd;
    int			needswriting = _dxf_ExNeedsWriting();
    int			cfnd;

    for (cfnd = 0, i = 0, r = handlers; i < nRIH; i++, r++)
    {
	if (r->check)
	{
	    r->flag = (* r->check)(r->fd, r->arg);
	    if (! cfnd)
		cfnd = r->flag;
	}
	else
	    r->flag = 0;
    }

#ifdef	EXCEED_SOCKET
    _dxf_InitExceedSockets();
#endif	
    FD_ZERO (&fdset);
    if(input >= 0) {
        FD_SET  (input, &fdset);
        mval = input;
    }
    else mval = -1;

    for (i = 0, r = handlers; i < nRIH; i++, r++)
    {
	fd = r->fd;
	if (mval < fd)
	    mval = fd;
#ifdef EXCEED_SOCKET
	if(r->isWin)
	    _dxf_SetExceedFd(fd, r->dpy);
	else
	    FD_SET(fd, &fdset);
#else
	FD_SET(fd, &fdset);
#endif
	
    }

    if (needswriting) {
     FD_ZERO(&wfdset);
     if(input >= 0)
         FD_SET (input, &wfdset);
    }

    if (cfnd)
    {
	struct timeval	tv;
	tv.tv_sec  = 0;
	tv.tv_usec = 0;
	select (mval + 1, &fdset, NULL, NULL, &tv);
    }
    else
    {
	if (select (mval + 1, &fdset, 
		(fd_set *)(needswriting? &wfdset: NULL), NULL, NULL) <= 0)
	{
#ifdef	EXCEED_SOCKET
	    _dxf_InitExceedSockets();
#endif	
	    return (ret);
	}
    }
    
    if(input >= 0) {
        if (FD_ISSET(input,&fdset) || (needswriting && FD_ISSET(input,&wfdset)))
        	ret = TRUE;
    }

    for (i = 0, r = handlers; i < nRIH; i++, r++)
    {
	fd = r->fd;
	if (r->flag || FD_ISSET(fd, &fdset))
	{
	    rval = (* r->proc) (fd, r->arg);
	    ret = TRUE;
	}
    }

#ifdef	EXCEED_SOCKET
    _dxf_InitExceedSockets();
#endif	
    return (ret);
}

/* pks 10/19/93 - this version of CheckRIH does not always call Input
 * handler routine on an EOF. This should be tested again when there is
 * more time. 
 */
#if 0
int _dxf_ExCheckRIH (void)
{
    int		n;
    int		i;
    EXRIH	r;
    int		rc;
    int		fd;
    int		ret	= FALSE;
    Error	rval;

    if (nRIH <= 0)
	return (ret);

    for (i = 0, r = handlers; i < nRIH; i++, r++)
    {
	fd = r->fd;
	rc = IOCTL (fd, FIONREAD, (char *) &n);
	if (rc < 0 || n > 0)
	{
	    rval = (* r->proc) (fd, r->arg);
	    ret = TRUE;
	}
    }

    return (ret);
}
#endif
/* this used to be used for the sgi because the above ioctl was broken */
/* I believe this is fixed and no longer needed. 4/16/93 */
/* put this back in because the ioctl was saying there 
 *  were chars when there weren't 
 */ 
int _dxf_ExCheckRIH (void)
{
    int			i;
    fd_set		fdset;
    EXRIH		r;
    struct timeval	tv;
    int			ret	= FALSE;
    Error		rval;
    int			mval;
    int			fd;
    int			cfnd;

    if (nRIH <= 0)
	return (ret);

    for (cfnd = 0, i = 0, r = handlers; i < nRIH; i++, r++)
    {
	if (r->check)
	{
	    r->flag = (* r->check)(r->fd, r->arg);
	    if (! cfnd)
		cfnd = r->flag;
	}
	else
	    r->flag = 0;
    }

#ifdef	EXCEED_SOCKET
    _dxf_InitExceedSockets();
#endif	
    FD_ZERO (&fdset);
    for (i = 0, r = handlers, mval = 0; i < nRIH; i++, r++)
    {
	fd = r->fd;
	if (mval < fd)
	    mval = fd;
#ifdef EXCEED_SOCKET
	if(r->isWin)
	    _dxf_SetExceedFd(fd, r->dpy);
	else
	    FD_SET(fd, &fdset);
#else
	FD_SET(fd, &fdset);
#endif
    }

    tv.tv_sec  = 0;
    tv.tv_usec = 0;
    
    if (cfnd)
    {
	select (mval + 1, &fdset, NULL, NULL, &tv);
    }
    else if (select (mval + 1, &fdset, NULL, NULL, &tv) <= 0) {
#ifdef	EXCEED_SOCKET
	_dxf_InitExceedSockets();
#endif
	return (ret);
    }
    
    for (i = 0, r = handlers; i < nRIH; i++, r++)
    {
	fd = r->fd;
	if (r->flag || FD_ISSET(fd, &fdset))
	{
	    rval = (* r->proc) (fd, r->arg);
	    ret = TRUE;
	}
    }

#ifdef	EXCEED_SOCKET
    _dxf_InitExceedSockets();
#endif

    return (ret);
}


static Error RIHDelete (int fd)
{
    int		i;
    int		j;
    EXRIH	r;
    EXRIH	nr;

    /*
     * Look through all of the registered input handlers.  If we find the
     * one associated with this file descriptor then close up the ranks.
     */

    for (i = 0, r = handlers; i < nRIH; i++, r++)
    {
	if (r->fd == fd)
	{
	    for (j = i + 1, nr = r + 1; j < nRIH; j++, r++, nr++)
		*r = *nr;
	    nRIH--;
	    return (OK);
	}
    }

    return (OK);
}


static Error RIHInsert (Error (*proc) (int, Pointer), int fd, Pointer arg, 
			int (*check)(int, Pointer))
{
    int		i;
    EXRIH	r;

    /*
     * See if they are just changing the input handler.  If so then
     * remember the new data.
     */

    for (i = 0, r = handlers; i < nRIH; i++, r++)
    {
	if (r->fd == fd)
	{
	    r->proc  = proc;
	    r->check = check;
	    r->arg   = arg;
	    r->isWin = 0;
	    return (OK);
	}
    }

    if (nRIH >= MAXRIH)
	DXErrorReturn (ERROR_INTERNAL, "too many input handlers registered");

    /*
     * Looks like we are installing a new one.
     */

    r = &handlers[nRIH++];

    r->proc  = proc;
    r->check = check;
    r->fd    = fd;
    r->arg   = arg;
    r->isWin = 0;


#if defined(DXD_HAS_IBM_OS2_SOCKETS)  || defined(DXD_HAS_WINSOCKETS)

#ifdef	EXCEED_SOCKET
    if(!r->isWin)
	SOCK_SETSOCKET (fd);
#else
    SOCK_SETSOCKET (fd);
#endif

#endif

    return (OK);
}

/* this has a basic problem -- how do you determine something unique to
 * identify whether you are asking to replace a callback routine, or delete
 * one?  the RIH stuff has a file handle.  this has a proc and an arg block.
 * you can't use the proc address as the unique id and then tell people to
 * unregister their handler by passing in a null proc.  for now i'm using
 * the address of the arg block, but the arg block shouldn't be required.
 */
Error DXRegisterCallbackHandler (Error (*proc) (Pointer), Pointer arg, int when)
{
    return ((proc == NULL) ? RCHDelete (arg) : RCHInsert (proc, arg, when));
}

static Error RCHDelete (Pointer arg)
{
    int		i;
    int		j;
    EXRCH	r;
    EXRCH	nr;

    /*
     * Look through all of the registered callback handlers.  If we find the
     * one associated with this file descriptor then close up the ranks.
     */

    for (i = 0, r = callbacks; i < nRCH; i++, r++)
    {
	if (r->arg == arg)
	{
	    for (j = i + 1, nr = r + 1; j < nRIH; j++, r++, nr++)
		*r = *nr;
	    nRCH--;
	    return (OK);
	}
    }

    return (OK);
}


static Error RCHInsert (Error (*proc) (Pointer), Pointer arg, int when)
{
    int		i;
    EXRCH	r;

    /*
     * See if they are just changing the callback handler.  If so then
     * remember the new data.
     */

    for (i = 0, r = callbacks; i < nRCH; i++, r++)
    {
	if (r->arg == arg)
	{
	    r->proc = proc;
	    r->arg  = arg;
	    r->when = when;
	    return (OK);
	}
    }

    if (nRCH >= MAXRCH)
	DXErrorReturn (ERROR_INTERNAL, "too many callback handlers registered");

    /*
     * Looks like we are installing a new one.
     */

    r = &callbacks[nRCH++];

    r->proc = proc;
    r->arg  = arg;
    r->when = when;

    return (OK);
}

int _dxf_ExCheckRCH (int when)
{
    int			i;
    EXRCH		r;
    int			ret	= FALSE;
    Error		rval;
    int			mval;
    int			fd;

    if (nRCH <= 0)
	return (ret);

    for (i = 0, r = callbacks; i < nRCH; i++, r++)
    {
	if (r->when == when)
	    rval = (* r->proc) (r->arg);
    }

    return TRUE;
}

int
_dxf_SetExceedSocket(int fd, void *d)
{    
	int i;
	EXRIH r;
	
	for (i = 0, r = handlers; i < nRIH; i++, r++)
    	if (r->fd == fd)
		{
			r->dpy = d;
			r->isWin = 1;
			return 1;
		}
	
	return 0;
}



