/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/rq.h,v 1.6 2002/03/21 21:14:41 rhh Exp $
 */

#include <dxconfig.h>

#ifndef	__EX_RQ_H
#define	__EX_RQ_H

#include "utils.h"

void		_dxf_ExRQEnqueue	(PFI func, Pointer arg, int repeat,
				 long gid, 	/* Group ID (used)	*/
				 int JID,	/* JOB (pinned proc) or 0 */
				 int highpri);	/* run this NOW		*/
void		_dxf_ExRQEnqueueMany	(int n, PFI func[], Pointer arg[], int repeat[],
				 long gid, 	/* Group ID (used)	*/
				 int JID, 	/* JOB (pinned proc) or 0 */
				 int highpri);	/* run this NOW		*/
int    _dxf_ExRQDequeue	(long gid);	/* Group ID (or 0)	*/
int    _dxf_ExRQPending(void);
Error  _dxf_ExRQInit (void);

#endif	/* __EX_RQ_H */
