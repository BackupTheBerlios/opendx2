/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/config.h,v 1.5 2000/08/11 15:28:10 davidt Exp $
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>

#include "utils.h"
#include "context.h"
#include "license.h"
#include "distp.h"
#include "cache.h"
#include "sfile.h"

#define MAXPROCESSORS           128

#define MAXSHMSEGMENTS          32
#define MAXSEMAPHORES           128

#define MAXINCLUDES             32
#define MAXDIMS                 32
#define MAXARGS                 128

#define GBUFSIZE                128

#define MAXGRAPHS               1

/* buffer size for sending/receiving parse trees */
#define PTBUFSIZE               1024

#define DXDIR                   "/usr/local/dx"
#define DXRC                    ".dxrc"
#define SYSDXRC                 "dxrc"

/*
 * This is a list of all the global variables declared within one file
 * but made available to others.
 *
 */

/* Declared in dxmain.c */

extern Context      *_dxd_exContext;
extern char         *_dxd_exHostName;		/* name of host program is running on */
extern int          *_dxd_exNSlaves;		/* number of slaves connected */
extern SFILE        *_dxd_exSockFD;
extern int          *_dxd_exTerminating;	/* flag set when dx is exiting */
extern int          *_dxd_extoplevelloop;
extern int          _dxd_exCacheOn;
extern int          _dxd_exDebug;		/* debugging enabled */
extern int          _dxd_exDebugConnect;	/* manually start up remote connections */
extern lock_type    _dxd_dphostslock;
extern int          _dxd_exIntraGraphSerialize; 
extern int          _dxd_exIsatty;
extern int          _dxd_exEnableDebug;
extern lictype      _dxd_exForcedLicense;
extern EXDictionary _dxd_exGlobalDict;
extern int          _dxd_exGoneMP;
extern int          _dxd_ExHasLicense;
extern long         _dxd_exMarkMask;
extern int          _dxd_exMasterfd;		/* slave to master file descriptor */
extern int          _dxd_exMyPID;		/* processor number of current processor */
extern int          _dxd_exParseAhead;
extern int          _dxd_exPPID;		/* processor number of parent processor */
extern int          _dxd_exRemote;		/* connected remotely to UI */
extern int          _dxd_exRemoteSlave;		/* running as a slave to another exec? */
extern int          _dxd_exRemoteUIMsg;		/* msgs will display on remote slave */
extern int          _dxd_exRshInput;
extern int          _dxd_exShowBells;
extern int          _dxd_exShowTiming;
extern int          _dxd_exSkipExecution;
extern int          _dxd_exSlaveId; 		/* slave id number, 0 = master */
extern int          _dxd_exSParseAhead;
extern int          _dxd_exSwapMsg;		/* do we need to swap msg from peer? */

typedef LIST(dphosts)     DPHOSTS;
typedef LIST(dpgraphstat) DPGRAPHSTAT;
typedef LIST(pathtag)     PATHTAG;
typedef LIST(PGassign)    PGASSIGN;
typedef LIST(SlavePeers)  SLAVEPEERS;

extern DPHOSTS      *_dxd_dphosts; 
extern DPGRAPHSTAT  _dxd_dpgraphstat;
extern PATHTAG      _dxd_pathtags;
extern PGASSIGN     _dxd_pgassign;
extern SLAVEPEERS   _dxd_slavepeers;

extern void _dxf_ExDie (char *format, ...);

/* Declared programatically in yuiif.c */
extern SFILE        *_dxd_exBaseFD; 
extern char         *_dxd_exParseMesg;
extern int          _dxd_exParseError;
extern struct node  *_dxd_exParseTree;
extern int          yydebug;

extern void         _dxf_ExBeginInput();
extern void         _dxf_ExEndInput();
extern Error        _dxf_ExParseInit (char *name, SFILE *sf);


/* Declared in optarg.c */
extern char *optarg;

#endif  /* _CONFIG_H */

