/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



#ifndef	_STATUS_H
#define	_STATUS_H

#if DXD_PROCESSOR_STATUS

#include "config.h"

#define PS_MIN		0		/* this must be first and 0 */
#define	PS_NONE		1
#define	PS_EXECUTIVE	2
#define PS_PARSE	3
#define PS_GRAPHGEN	4
#define PS_GRAPHQUEUE	5
#define PS_RUN		6
#define	PS_RECLAIM	7
#define PS_JOINWAIT	8
#define	PS_NAPPING	9
#define	PS_DEAD		10
#define	PS_MAX		11		/* this must be last */

extern Error _dxf_ExInitStatus	(int n, int flag);
extern void _dxf_ExCleanupStatus	(void);

extern int		*_dxd_exProcessorStatus;

#define	set_status(_s)	if (_dxd_exProcessorStatus) _dxd_exProcessorStatus[_dxd_exMyPID] = (_s)
#define	get_status() \
		(_dxd_exProcessorStatus ? _dxd_exProcessorStatus[_dxd_exMyPID] : PS_NONE)
#else
#define	set_status(_s)   FALSE
#define	get_status()     FALSE
#endif

#endif	/* _STATUS_H */
