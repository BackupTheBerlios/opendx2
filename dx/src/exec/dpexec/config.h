/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>



#ifndef	_CONFIG_H
#define	_CONFIG_H

#include <stdio.h>

#define MAXPROCESSORS		128

#define MAXSHMSEGMENTS		32
#define MAXSEMAPHORES		128

#define MAXINCLUDES		32
#define	MAXDIMS			32
#define MAXARGS			128

#define GBUFSIZE		128

#define	MAXGRAPHS		1

/* buffer size for sending/receiving parse trees */
#define PTBUFSIZE		1024  

#define	DXDIR			"/usr/lpp/dx"
#define	DXRC			".dxrc"
#define	SYSDXRC			"dxrc"

extern int _dxd_exDebug;		/* debugging enabled */
extern int _dxd_exMyPID;		/* processor number for current processor */
extern int _dxd_exPPID;		/* processor number for parent processor */
extern int *_dxd_exTerminating;	/* flag set when dx is exiting */
extern int _dxd_exRemote;       /* connected remotely to UI */
extern char *_dxd_exHostName;   /* name of host program is running on */ 
extern int _dxd_exRemoteSlave;  /* am I running as a slave to another exec? */
extern int _dxd_exSwapMsg;      /* do we need to swap msg from peer? */
extern int _dxd_exMasterfd;     /* slave to master file descriptor */
extern int _dxd_exSlaveId;      /* slave id number, 0 = master */
extern int _dxd_exDebugConnect; /* manually start up remote connections */
extern int _dxd_exRemoteUIMsg;  /* msgs will display on remote slave */
extern int *_dxd_exNSlaves;     /* number of slaves connected */
extern int *_dxd_extoplevelloop;/* number of slaves connected */

#endif	/* _CONFIG_H */
