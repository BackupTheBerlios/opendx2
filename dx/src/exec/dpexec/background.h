/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/background.h,v 1.4 2000/08/11 15:28:09 davidt Exp $
 */

#include <dxconfig.h>


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
