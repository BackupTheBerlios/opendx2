#ifndef	__EX_RQ_H
#define	__EX_RQ_H

#include "utils.h"


void		_dxf_ExRQEnqueue	(PFI func, Pointer arg, int repeat,
				 int gid, 	/* Group ID (used)	*/
				 int JID,	/* JOB (pinned proc) or 0 */
				 int highpri);	/* run this NOW		*/
void		_dxf_ExRQEnqueueMany	(int n, PFI func[], Pointer arg[], int repeat[],
				 int gid, 	/* Group ID (used)	*/
				 int JID, 	/* JOB (pinned proc) or 0 */
				 int highpri);	/* run this NOW		*/
int		_dxf_ExRQDequeue	(int gid);	/* Group ID (or 0)	*/

#endif	/* __EX_RQ_H */
