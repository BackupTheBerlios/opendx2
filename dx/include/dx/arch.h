/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/* 
 * architecture dependent file. 
 */
#ifndef _DXI_ARCH_H
#define _DXI_ARCH_H 1


/* version numbers for all platforms.  always defined.
 *   if any arch needs to have a different version number,
 *   undefine and redefine these in the arch specific section.
 */
#define DXD_VERSION_STRING "04.01.0001"
#define DXD_VERSION         4
#define DXD_RELEASE         1
#define DXD_MODIFICATION    1


/* linux86
 */
#ifdef linux86

#undef  REGCMP_EXISTS
#undef DXD_LACKS_ANY_REGCMP

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
#include <sys/types.h>

/* defined for machines with msb byte order (all machines but ibmpvs) */
#undef DXD_BIGENDIAN 

/* architecture name.  always defined */
#define DXD_ARCHNAME  "linux86"

/* license manager active in this version */
#undef DXD_LICENSED_VERSION 

/* defined if we support multiprocessor version */
#define DXD_IS_MP 0

/* do we need to keep a parent wait-process around? */
#define DXD_EXEC_WAIT_PROCESS 1

/* can we use sysmp() to find out how many processors an MP machine has? */
#define DXD_HAS_SYSMP 0

/* defined if we want to get processor status window */
#define DXD_PROCESSOR_STATUS 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETDTABLESIZE    1

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* is triangle mesh swapping supported by hardware graphics API? */
/* This causes render-every to go bonkers on sgi. This does not */
/* seem to yield noticable performance gain, so I'm removing it */
/*#define DXD_HW_TMESH_SWAP_OK 1 */

/* is hardware device coordinates orientation right-handed? */
#define DXD_HW_DC_RIGHT_HANDED 1

/* is it sometimes necessary to check if a window has been destroyed? */
#define DXD_HW_WINDOW_DESTRUCTION_CHECK 1

/* is GL texture mapping supported? */
#define DXD_HW_TEXTURE_MAPPING 1

/* is special HW gamma compensation necessary? */
#define DXD_HW_SPECIAL_GAMMA_COMPENSATION 1

/* API (eg. GL) keeps its own copy of the object */
#define DXD_HW_API_DISPLAY_LIST_MEMORY 1

/* supports xwindows status display? */
#define DXD_EXEC_STATUS_DISPLAY 1

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT 1

/* program to run for remote shell */
#define RSH  "/usr/bsd/rsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT	1.0
#define DXD_GAMMA_12BIT	1.0
#define DXD_GAMMA_16BIT	1.0
#define DXD_GAMMA_24BIT	2.0

/* cannot load runtime-loadable modules after forking */
#define DXD_NO_MP_RUNTIME 1

#endif   /* linux86 */

/* silicon graphics: indigo, crimson, 280/gtx, onyx, extreme
 */
#ifdef sgi

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
#include <sys/types.h>

/* defined for machines with msb byte order (all machines but ibmpvs) */
#define DXD_BIGENDIAN 1

/* architecture name.  always defined */
#define DXD_ARCHNAME  "sgi"

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* defined if we support multiprocessor version */
#define DXD_IS_MP 1

/* do we need to keep a parent wait-process around? */
#define DXD_EXEC_WAIT_PROCESS 1

/* can we use sysmp() to find out how many processors an MP machine has? */
#define DXD_HAS_SYSMP 1

/* defined if we want to get processor status window */
#define DXD_PROCESSOR_STATUS 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETDTABLESIZE    1

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* is triangle mesh swapping supported by hardware graphics API? */
/* This causes render-every to go bonkers on sgi. This does not */
/* seem to yield noticable performance gain, so I'm removing it */
/*#define DXD_HW_TMESH_SWAP_OK 1 */

/* is hardware device coordinates orientation right-handed? */
#define DXD_HW_DC_RIGHT_HANDED 1

/* is it sometimes necessary to check if a window has been destroyed? */
#define DXD_HW_WINDOW_DESTRUCTION_CHECK 1

/* is GL texture mapping supported? */
#define DXD_HW_TEXTURE_MAPPING 1

/* is special HW gamma compensation necessary? */
#define DXD_HW_SPECIAL_GAMMA_COMPENSATION 1

/* API (eg. GL) keeps its own copy of the object */
#define DXD_HW_API_DISPLAY_LIST_MEMORY 1

/* supports xwindows status display? */
#define DXD_EXEC_STATUS_DISPLAY 1

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT 1

/* program to run for remote shell */
#define RSH  "/usr/bsd/rsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT	1.0
#define DXD_GAMMA_12BIT	1.0
#define DXD_GAMMA_16BIT	1.0
#define DXD_GAMMA_24BIT	2.0

/* cannot load runtime-loadable modules after forking */
#define DXD_NO_MP_RUNTIME 1

#endif   /* sgi */


/* hp/700-800 series 
 */
#ifdef hp700

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
typedef unsigned long	ulong;
#include <sys/types.h>

/* architecture name.  always defined */
#define DXD_ARCHNAME  "hp700"

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* defined for machines with msb byte order (all machines but ibmpvs) */
#define DXD_BIGENDIAN  1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do you need to declare the system error list explicitly? */
#define DXD_SYSERRLIST_DECL 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETHOSTBYNAME    1

/* compensate for bug in hardware window reparenting */
#define DXD_HW_REPARENT_OFFSET_X -2
#define DXD_HW_REPARENT_OFFSET_Y -3

/* Does this hardware support alpha transparency per connection? position?*/
#define DXD_HW_ALPHA_CNTNS 1
#define DXD_HW_ALPHA_POSNS 0

/* Does the X server behave correctly for a move of a Starbase window */
#define DXD_HW_XSERVER_MOVE_OK 1

/* select expects int pointers for params */
#define DXD_SELECTPTR_DEFINED  1
typedef int * SelectPtr;

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT  1

/* program to run for remote shell */
#define RSH "/usr/bin/remsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

/* system includes support for the vfork() system call */
#define DXD_HAS_VFORK 1

#endif  /* hp700 */


/* ibm risc system/6000
 */
#ifdef ibm6000

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
#include <sys/types.h>

/* architecture name.  always defined */
#define DXD_ARCHNAME  "ibm6000"

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* defined for machines with msb byte order (all machines but ibmpvs) */
#define DXD_BIGENDIAN 1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* defined if we support multiprocessor version */
#define DXD_IS_MP 1

/* do we need to keep a parent wait-process around? */
#define DXD_EXEC_WAIT_PROCESS 1

/* does this system support _system_configuration.ncpus */
#define DXD_HAS_SYSCONFIG 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do you need to declare the system error list explicitly? */
#define DXD_SYSERRLIST_DECL 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_NEEDS_SYS_SELECT_H   1
#define DXD_HAS_GETDTABLESIZE    1
#define DXD_HAS_GETHOSTBYNAME    1

/* is the SigDanger signal defined? (indicates running low on page space) */
#define DXD_HAS_SIGDANGER 1

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* is hardware device coordinates orientation right-handed? */
#define DXD_HW_DC_RIGHT_HANDED 1

/* Does the X server behave correctly for a move of a GL window */
#define DXD_HW_XSERVER_MOVE_OK 1

/* has nonstandard include file and ifdefs for the access() system call? */
#define DXD_SPECIAL_ACCESS 1

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT  1

/* program to run for remote shell */
#define RSH "/usr/bin/rsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0


#endif  /* ibm6000 */


/* sun sparc II
 */
#ifdef sun4

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
typedef unsigned long	ulong;
#include <sys/types.h>

/* architecture name.  always defined */
#define DXD_ARCHNAME  "sun4"

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* defined for machines with msb byte order (all machines but ibmpvs) */
#define DXD_BIGENDIAN 1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do you need to declare the system error list explicitly? */
#define DXD_SYSERRLIST_DECL 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETDTABLESIZE    1
#define DXD_HAS_GETHOSTBYNAME    1

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* is hardware sensitive to vertex orientation of 1st triangle in strip? */
#define DXD_HW_TMESH_ORIENT_SENSITIVE 1

/* Does the X server behave correctly for a move of a XGL window */
#define DXD_HW_XSERVER_MOVE_OK 1

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT  1

/* the system routine herror() doesn't exist on this architecture */
#define herror perror

/* program to run for remote shell */
#define RSH "/usr/ucb/rsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

/* system includes support for the vfork() system call */
#define DXD_HAS_VFORK 1

#endif  /* sun4 */


/* sun sparc solaris 
 */
#ifdef solaris

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
#include <sys/types.h>

/* architecture name.  always defined */
#define DXD_ARCHNAME  "solaris"

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* defined for machines with msb byte order (all machines but ibmpvs) */
#define DXD_BIGENDIAN 1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* defined if we support multiprocessor version */
#define DXD_IS_MP 1

/* do we need to keep a parent wait-process around? */
#define DXD_EXEC_WAIT_PROCESS 1

/* defined if we want to get processor status window */
#define DXD_PROCESSOR_STATUS 1

/* does this system support sysconf(3)? */
#define DXD_HAS_SYSCONF 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do you need to declare the system error list explicitly? */
#define DXD_SYSERRLIST_DECL 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETHOSTBYNAME    1
#define MAXFUPLIM FD_SETSIZE

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* is hardware sensitive to vertex orientation of 1st triangle in strip? */
#define DXD_HW_TMESH_ORIENT_SENSITIVE 1
 
/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT  1

/* the system routine herror() doesn't exist on this architecture */
#define herror perror

/* program to run for remote shell */
#define RSH "/usr/bin/rsh"

/* wait(int *) for solaris */
union wait{
   int status;
   };

/* bcopy,bcmp,bzero these are in /usr/ucb/libucb.a on solaris
 * this is the BSD compatibilty section and may not be there in future */
#define bcopy(s,d,n)	memcpy((void *)(d),(void *)(s),(int)(n))
#define bzero(s,n)	memset((void *)(s),0,(int)(n))
#define bcmp(s1,s2,n)	memcmp((void *)(s1),(void *)(s2),(int)(n))

/* Use sun mutex type locks unless we are using Purify which gets upset
 * about the threads library
 */
#ifdef __PURIFY__
# define DXD_USE_MUTEX_LOCKS 0
#else
# define DXD_USE_MUTEX_LOCKS 1
#endif

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

/* cannot load runtime-loadable modules after forking */
#define DXD_NO_MP_RUNTIME 1

/* system includes support for the vfork() system call */
#define DXD_HAS_VFORK 1


#endif  /* solaris */


/* data general AViiON
 */
#ifdef aviion

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef unsigned char   uchar;
typedef signed char     byte;
typedef unsigned char	ubyte;
#include <sys/types.h>

/* architecture name.  always defined */
#define DXD_ARCHNAME  "aviion"

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* defined for machines with msb byte order (all machines but ibmpvs) */
#define DXD_BIGENDIAN 1

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do you need to declare the system error list explicitly? */
#define DXD_SYSERRLIST_DECL 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETDTABLESIZE    1
#define DXD_HAS_GETHOSTBYNAME    1

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT  1

/* the system routine herror() doesn't exist on this architecture */
#define herror perror

/* program to run for remote shell */
#define RSH "/usr/bin/remsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

/* system includes support for the vfork() system call */
#define DXD_HAS_VFORK 1

#endif  /* aviion */

/* intel x86 architecture
 */
#if defined(intel) || defined(intelnt)  || defined(DXD_WIN)

#define DXD_CAN_HAVE_HW_RENDERING 1

/*
#ifdef DXD_BIGENDIAN
#undef DXD_BIGENDIAN
#endif
#define DXD_BIGENDIAN 0
*/

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef unsigned char   uchar;
typedef signed char     byte;
typedef unsigned char	ubyte;
typedef unsigned short  ushort;
typedef unsigned int    uint;
#include <sys/types.h>

#define fork() -1

/* architecture name.  always needs to be defined */
#define DXD_ARCHNAME  "intel"

/* do you need to declare the system error list explicitly? */
#define DXD_SYSERRLIST_DECL 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_WINSOCKETS_OK 1

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

#endif  /* intel */


#ifdef intelnt

/* We have to assume that DXD_WIN is for NT on Intel
   Machines, else we have to change all occurances
*/
#define	DXD_WIN	
#define DXD_POPEN_OK 1
#define RSH  "rsh"

/* supports popen() */
#define DXD_OS_NON_UNIX      1
#define DXD_HAS_WINSOCKETS   1
#define MAXHOSTNAMELEN       128
#define MAXPATHLEN           255
/*   
	work-around for EXCEED socket/ fd in display
*/
#define	EXCEED_SOCKET	1 

#define DXD_SOCKET_WINSOCKETS_OK 1

/* to port directories on PC enviroments     */
#define DXD_NON_UNIX_DIR_SEPARATOR 1
#define DXD_NON_UNIX_ENV_SEPARATOR 1

#define	_WINERROR_ 1
#define _DLGSH_INCLUDED_  1  /* for scr1, scr2 in arrayhandles.h   */

#include <windows.h>
#include <errno.h>

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef unsigned char   uchar;
typedef signed char     byte;
typedef unsigned char	ubyte;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

/* architecture name.  always needs to be defined */
#define DXD_ARCHNAME  "intelnt"

/* do you need to declare the system error list explicitly? */

#define DXD_SYSERRLIST_DECL 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

#define DXD_SELECTPTR_DEFINED 1
#define SelectPtr  fd_set*

#define DXD_HAS_GETDTABLESIZE	1
/*    #define DXD_NEEDS_SYS_SELECT_H 1     */

/* defining DXD_STANDARD_IEEE will solve some of the setjump/longjump problmes
   in _compoper.c  */
#define DXD_STANDARD_IEEE 1


#define DXD_LACKS_UNIX_UID 1


#include <string.h>
#include <stdio.h>

/* fix ioctl and socket prototypes, use send/recv for read and write */
#define BSD_SELECT 1
#include <sys/types.h>

/*  #include <sys/select.h>  : In windows.h    */

#undef	LONG
#undef	SHORT
#undef  CHAR

/* stolen from /usr/include/math.h */
/* these exist in the C++ include file complex.h  */
#define M_PI       3.1415926535897931160E0  /*Hex  2^ 1 * 1.921FB54442D18 */
#define M_SQRT2    1.4142135623730951455E0  /*Hex  2^ 0 * 1.6A09E667F3BCD */

#define herror WSAGetLastError()

/*
 * file descriptor io functions for non unix (nu) platforms
 */
/* Declarations files, required in OS2, NT */ 
#include <io.h>
#include <process.h>
#include <direct.h>

/*
 * Socket identification stuff
 */
extern  fd_set sockSet;
#define SOCK_ZERO() FD_ZERO(&sockSet)
#define SOCK_SETSOCKET(fd) FD_SET(fd,&sockSet)
#define SOCK_CLRSOCKET(fd) FD_CLR(fd,&sockSet)
#define SOCK_ISSOCKET(fd) FD_ISSET(fd,&sockSet)

int gettablesize(void);
int getopt(int,char**,char*);
int os2_select();
int 	_dxf_nu_pipe(int *fds);
FILE*	_dxf_nu_fopen(const char *filename, const char *mode);

#define fopen(file,mode) _dxf_nu_fopen(file,mode"b")
#define open(path,oflag)  _open(path,oflag|O_BINARY&(~O_CREAT),0)
#define creat(path,mode) _open(path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, mode)

#define close(fd) \
	if(SOCK_ISSOCKET(fd))  \
	{	\
		SOCK_CLRSOCKET(fd);	\
		closesocket(fd);	\
	}	\
	else	\
	_close(fd);


#define lseek(fd,offset,whence)	\
	(SOCK_ISSOCKET(fd) ? \
	 errno = EBADF,-1 : \
	 _lseek(fd,offset,whence))


#define read(fd,buff,count) \
	(SOCK_ISSOCKET(fd) ? \
	 _dxf_os2_recv(fd,(char *)buff,count,0) : \
	 _read(fd,buff,count))

#define write(fd,buff,count) \
	(SOCK_ISSOCKET(fd) ? \
	 _dxf_os2_send(fd,(char *)buff,count,0) : \
	 _write(fd,buff,count))

#define wait(status)  cwait(status, status, 0)
#define getpid() _getpid()

#define dup2(old,new)	\
	(SOCK_ISSOCKET(new)  || SOCK_ISSOCKET(old) ? \
	 errno = EBADF,-1 : \
	 _dup2(old,new))


#define pipe(fds)	_dxf_nu_pipe(fds)
#define chdir(path)  _chdir(path)
#define getcwd(buffer,size)  _getcwd(buffer,size)
#define srand48(seed)  srand(seed)
#define lrand48() ((rand() * RAND_MAX) + rand())
#define drand48() ((double)lrand48()/((double)RAND_MAX*(double)RAND_MAX))
#define trunc(value) ((float)((int)(value)))
#define rint(value) ((float)((int)((value) + 0.5)))
#define isatty(fd) _isatty(fd)
#define S_ISDIR(x) ((x) & (S_IFDIR))



#undef  select	/* this is also defined in tcpip/include/sys/select.h */
#define select(count,rmask,wmask,emask,timeout)  \
	os2_select(count,rmask,wmask,emask,timeout)

#define fork	DXWinFork

#define herror WSAGetLastError

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

#define bcopy(s,d,n)	memcpy((void *)(d),(void *)(s),(int)(n))
#define bzero(s,n)		memset((void *)(s),0,(int)(n))
#define bcmp(s1,s2,n)	memcmp((void *)(s1),(void *)(s2),(int)(n))


/* these are #defined in winerr.h, which cause problems
 * with our enum of ERROR_INVALID_DATA, and the scr1 & scr2 are
 * used as local variables in the arrayhandles.h code.
 */
#ifdef ERROR_INVALID_DATA
#undef ERROR_INVALID_DATA
#endif 

#ifdef scr1
#undef scr1
#endif 

#ifdef scr2
#undef scr2
#endif 


#endif  /*   intelnt  */


#ifdef os2

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef unsigned char   uchar;
typedef signed char     byte;
typedef unsigned char	ubyte;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

/* architecture name.  always needs to be defined */
#define DXD_ARCHNAME  "os2"

/* do you need to declare the system error list explicitly? */

#define DXD_OS_NON_UNIX      1
#define DXD_SYSERRLIST_DECL 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

#define DXD_SELECTPTR_DEFINED 1
#define SelectPtr  fd_set*

#define DXD_HAS_GETDTABLESIZE	1
#define DXD_NEEDS_SYS_SELECT_H 1

#define DXD_HAS_OS2_CP 1
#define DXD_HAS_IBM_OS2_SOCKETS 1
#define DXD_LACKS_UNIX_UID 1
#define DXD_OS2_SYSCALL 1


/* defining DXD_STANDARD_IEEE will solve some of the setjump/longjump problmes
   in _compoper.c */
#define DXD_STANDARD_IEEE 1

#include <string.h>
#include <stdio.h>

/* fix ioctl and socket prototypes, use send/recv for read and write */
#define BSD_SELECT 1
#include <types.h>
#include <sys/select.h>

#define INCL_DOS
#include <os2.h>
#undef	LONG
#undef	SHORT
#undef  CHAR


/* stolen from /usr/include/math.h */
/* these exist in the C++ include file complex.h on os2 */
#define M_PI       3.1415926535897931160E0  /*Hex  2^ 1 * 1.921FB54442D18 */
#define M_SQRT2    1.4142135623730951455E0  /*Hex  2^ 0 * 1.6A09E667F3BCD */


#define herror psock_errno


/*
 * file descriptor io functions for non unix (nu) platforms
 */
/* Declarations files, required in OS2 */ 
#include <io.h>
#include <process.h>
#include <direct.h>

/*
 * Socket identification stuff
 */
extern  fd_set sockSet;
#define SOCK_ZERO() FD_ZERO(&sockSet)
#define SOCK_SETSOCKET(fd) FD_SET(fd,&sockSet)
#define SOCK_CLRSOCKET(fd) FD_CLR(fd,&sockSet)
#define SOCK_ISSOCKET(fd) FD_ISSET(fd,&sockSet)

int gettablesize(void);
int getopt(int,char**,char*);
int os2_select();
int 	_dxf_nu_pipe(int *fds);
FILE*	_dxf_nu_fopen(const char *filename, const char *mode);

#define fopen(file,mode) _dxf_nu_fopen(file,mode"b")
#define open(path,oflag) \
	_open(path,oflag|O_BINARY&(~O_CREAT),0)
#define creat(path,mode) \
	_open(path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, mode)
#define close(fd) \
	(SOCK_ISSOCKET(fd) ? \
	 SOCK_CLRSOCKET(fd),soclose(fd) : \
	 _close(fd))
#define lseek(fd,offset,whence)	\
	(SOCK_ISSOCKET(fd) ? \
	 errno = EBADF,-1 : \
	 _lseek(fd,offset,whence))
#define read(fd,buff,count) \
	(SOCK_ISSOCKET(fd) ? \
	 UxRecv(fd,(char *)buff,count,0) : \
	 _read(fd,buff,count))
#define write(fd,buff,count) \
	(SOCK_ISSOCKET(fd) ? \
	 UxSend(fd,(char *)buff,count,0) : \
	 _write(fd,buff,count))
#define wait(status) \
	_wait(status)
#define getpid() \
	_getpid()
#define dup2(old,new)	\
	(SOCK_ISSOCKET(new)  || SOCK_ISSOCKET(old) ? \
	 errno = EBADF,-1 : \
	 _dup2(old,new))
#define pipe(fds)	\
	_dxf_nu_pipe(fds)
#define chdir(path) \
	_chdir(path)
#define getcwd(buffer,size) \
	_getcwd(buffer,size)
#define srand48(seed) \
	srand(seed)
#define lrand48() \
	((rand() * RAND_MAX) + rand())
#define drand48() \
	((double)lrand48()/((double)RAND_MAX*(double)RAND_MAX))
#define trunc(value) \
	((float)((int)(value)))
#define rint(value) \
	((float)((int)((value) + 0.5)))
#define isatty(fd) \
	_isatty(fd)
#define S_ISDIR(x) \
	((x) & (S_IFDIR))
#undef  select	/* this is also defined in tcpip/include/sys/select.h */
#define select(count,rmask,wmask,emask,timeout) \
	os2_select(count,rmask,wmask,emask,timeout)
#define fork() (-1)

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

#endif  /* os2 */

/* Dec Alpha AXP OSF/1
 */
#ifdef alphax

/* enough typedefs so byte,ubyte,short,ushort,int and uint are defined */
typedef signed char     byte;
typedef unsigned char	ubyte;
#include <sys/types.h>

/* architecture name.  always defined */
#define DXD_ARCHNAME  "alphax"

/* supports full IEEE standard floating point, including under/overflow */
#define DXD_STANDARD_IEEE 0

/* license manager active in this version */
#define DXD_LICENSED_VERSION 1

/* supports popen() */
#define DXD_POPEN_OK 1

/* do the printf-type routines return a pointer or a count? */
#define DXD_PRINTF_RETURNS_COUNT 1

/* socket-specific ifdefs */
#define DXD_SOCKET_UNIXDOMAIN_OK 1
#define DXD_HAS_GETDTABLESIZE    1

#define DXD_IS_MP 1
#define DXD_EXEC_WAIT_PROCESS 1
#define DXD_HAS_SYSCONF 1

/* hardware rendering is an option? */
#define DXD_CAN_HAVE_HW_RENDERING 1

/* can you use rlimit to stop the exec from creating a huge core file? */
#define DXD_HAS_RLIMIT 1

/* is hardware device coordinates orientation right-handed? */
#define DXD_HW_DC_RIGHT_HANDED 1

/* supports xwindows status display? */
#define DXD_EXEC_STATUS_DISPLAY 1

/* compiler apparently doesn't parse \a as alert */
#define DXD_NO_ANSI_ALERT 1

/* can use the crypt system call for data encryption */
#define DXD_HAS_CRYPT 1

/* program to run for remote shell */
#define RSH  "/usr/bin/rsh"

/* system includes are in /usr/include/sys and /usr/include/unistd.h exists */
#define DXD_HAS_UNIX_SYS_INCLUDES 1
#define DXD_HAS_UNISTD_H 1


/* fixed type sizes, if different from standard */
typedef signed char    int8;
typedef unsigned char  uint8;
typedef short          int16;
typedef unsigned short uint16;
typedef int            int32;
typedef unsigned int   uint32;
typedef long           int64;
typedef unsigned long  uint64;

typedef float          float32;
typedef double         float64;

#define DXD_FIXEDSIZES 1 

/* default values for gamma correction */
#define DXD_GAMMA_8BIT  2.0
#define DXD_GAMMA_12BIT	2.0
#define DXD_GAMMA_16BIT	2.0
#define DXD_GAMMA_24BIT 2.0

#endif   /* alphax */



/* if standard IEEE floating point, these are the constants.  the
 *  pvs is slightly different in that it can't handle underflow
 *  or overflow floats without hardware traps.
 */

/* defined in one place for all supported architectures */
#define DXD_MAX_BYTE            127
#define DXD_MIN_BYTE           -128

#define DXD_MAX_UBYTE           255

#define DXD_MAX_SHORT         32767
#define DXD_MIN_SHORT        -32768

#define DXD_MAX_USHORT        65535

#define DXD_MAX_INT      2147483647
#define DXD_MIN_INT     -2147483648

#define DXD_MAX_UINT     4294967295

/* same whether denormalized numbers are supported nor not */
#define DXD_MAX_FLOAT       ((float)3.40282346638528860e+38)
#define DXD_FLOAT_EPSILON   ((float)1.1920928955078125e-7)
#define DXD_MAX_DOUBLE      1.7976931348623157e+308
#define DXD_DOUBLE_EPSILON  2.2204460492503131e-16

#if DXD_STANDARD_IEEE
#define DXD_MIN_FLOAT       ((float)1.40129846432481707e-45)
#define DXD_MIN_DOUBLE      4.94065645841246544e-324
#else   /* denormalized numbers cause traps on i860 */
#define DXD_MIN_FLOAT       ((float)1.1754943508222875e-38)
#define DXD_MIN_DOUBLE      2.2250738585072014e-308
#endif

#ifndef DXD_HW_REPARENT_OFFSET_X
#define DXD_HW_REPARENT_OFFSET_X 0
#endif

#ifndef DXD_HW_REPARENT_OFFSET_Y
#define DXD_HW_REPARENT_OFFSET_Y 0
#endif

#ifndef DXD_HW_XSERVER_MOVE_OK
#define DXD_HW_XSERVER_MOVE_OK 0
#endif

#ifndef DXD_SELECTPTR_DEFINED
typedef void * SelectPtr;
#endif

/* fixed type sizes */
#ifndef DXD_FIXEDSIZES
 
typedef signed char    int8;
typedef unsigned char  uint8;
typedef short          int16;
typedef unsigned short uint16;
typedef int            int32;
typedef unsigned int   uint32;

typedef float          float32;
typedef double         float64;

#define DXD_FIXEDSIZES 1 

#endif

#if defined(DXD_ENABLE_SOCKET_POINTERS) && (defined(DXD_HAS_IBM_OS2_SOCKETS) || defined(DXD_HAS_WINSOCKETS))
/*
 * Socket FILE pointer stuff 
 *
 * In OS2 and perhaps other operating systems sockets are implemented 
 * as a layered product. This means that fdopen does not work for creating 
 * a stream (file pointer) from a socket file descriptor. 
 *
 * The code below defines an SFILE (socket file pointer) union which can
 * passed to the the macros below. (This list can be expanded
 * as needed.) The source for the functions which are called is in os2.c
 * The macros and supporting functions provide stream like buffered io
 * for sockets.
 *
 * To use the SFILE points in c source, replace references to FILE with SFILE,
 * #define DXD_ENABLE_SOCKET_POINTERS (before including dx/dx.h) and be sure
 * to check that all functions using the resulting socket pointer have been
 * redefined below.
 *
 * XXX Currently this is only implemented for os2 and only for read only
 * sockets.
 * 
 */
#ifdef DXD_HAS_WINSOCKETS
#include <winsock.h>
#else
#include <sys/socket.h>
#endif

typedef struct SOCKETS {
    unsigned long	_count;		/* avoid _count field */
    unsigned long	isasocket;
    char		buffer[BUFSIZ];
    char		*nextchar;
    unsigned long	fileno;
} DX_SOCKET;
	
typedef union SFILES {
	FILE	file;
	DX_SOCKET	socket;
} SFILE;


/*
 * Socket identification stuff
 */
#define SOCK_ISSOCKET_SFILE(sfile) ((sfile)->socket.isasocket == SOCKET_MAGIC_NUMBER) 
#define SOCKET_MAGIC_NUMBER 0xFA1CEFD
	

/*
 * file POINTER io functions for non unix (nu) platforms
 */

#define fileno(sfile) \
	(SOCK_ISSOCKET_SFILE(sfile) ? \
	 (sfile)->socket.fileno : \
	 _dxf_nu_fileno(&(sfile)->file))
#define fdopen(fd, mode) \
	(SOCK_ISSOCKET(fd) ? \
	 _dxf_sock_fdopen(fd,mode) : \
	 _fdopen(fd,mode))
#define fclose(sfile) \
	_dxf_nu_fclose(sfile)
#define GETC(sfile) \
	(SOCK_ISSOCKET_SFILE(sfile) ? \
	 _dxf_sock_getc(&(sfile)->socket) : \
	 getc(&(sfile)->file))
#ifdef	DXD_HAS_WINSOCKETS
#define CHAR_READY(sfile) \
	(SOCK_ISSOCKET_SFILE(sfile) ? \
	 ((sfile)->socket._count > 0) : \
	 ((sfile)->file._cnt > 0))
#else
#define CHAR_READY(sfile) \
	(SOCK_ISSOCKET_SFILE(sfile) ? \
	 ((sfile)->socket._count > 0) : \
	 ((sfile)->file._count > 0))
#endif

int 	_dxf_nu_fileno(FILE* file);
int 	_dxf_nu_fclose(SFILE* file);

DX_SOCKET*	_dxf_sock_fdopen(int fd, char* mode);
int 	_dxf_sock_getc(SOCKET *file);

#else /* defined(DXD_ENABLE_SOCKET_POINTERS) && DXD_HAS_IBM_OS2_SOCKETS */

/*
 * if the code is being compiled on an architecture which will not use the 
 * SFILE structure, map it back to the default FILE.
 */
#define SFILE FILE

#ifdef linux86
#define CHAR_READY(fp) ((fp)->_IO_read_ptr < (fp)->_IO_read_end)
#else
#define CHAR_READY(fp) ((fp)->_cnt > 0)
#endif

#define GETC(file) getc(file)

#endif

#if !defined(DXD_HAS_IBM_OS2_SOCKETS) && !defined(DXD_HAS_WINSOCKETS)
#define IOCTL ioctl
#endif

#if DXD_HAS_IBM_OS2_SOCKETS
/*
 * OS2 sockets require 4 parameters (unix requires 3) so the code now calls
 * IOCTL which expand to one of the following depending on the use of 
 * OS2 sockets.
 */

#define IOCTL(fd,cmd,buf) \
	(SOCK_ISSOCKET(fd) ? \
	 ioctl(fd,cmd,(char *)buf, \
              (cmd == FIONREAD || cmd == FIONBIO) ? sizeof (int) : 0) : \
	 -1)

#endif
#ifdef	DXD_HAS_WINSOCKETS
#define IOCTL(fd,cmd,buf) \
	(SOCK_ISSOCKET(fd) ? \
	 ioctlsocket(fd,cmd,(char *)buf, \
              (cmd == FIONREAD || cmd == FIONBIO) ? sizeof (int) : 0) : \
	 -1)


#endif

#endif  /* whole file _DXI_ARCH_H   */

