/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#ifndef	_BACKGROUND_H
#define	_BACKGROUND_H

#include "parse.h"
#include "d.h"

/*
 * Externally visible functions.
 */

void	_dxf_ExBackgroundChange	(void);
void	_dxf_ExBackgroundRedo	(void);
void	_dxf_ExBackgroundCommand	(_bg comm, struct node * n);
int	_dxf_ExCheckBackground	(EXDictionary dict, int multiProc);
void	_dxf_ExCleanupBackground	(void);
Error	_dxf_ExInitBackground	(void);
int	ExBackgroundIdle	(void);

#endif	/* _BACKGROUND_H */
