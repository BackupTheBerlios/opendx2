/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/dxmain.h,v 1.1 2000/10/04 17:45:58 davidt Exp $
 */

#ifndef	_DXMAIN_H_
#define	_DXMAIN_H_

#include <dx/dx.h>

/* Function prototypes */

char ** _dxf_ExEnvp (void);
void  _dxf_ExInitSystemVars ();
Error _dxf_child_RQ_message(int *jobid);
Error _dxf_parent_RQ_message();
void _dxf_lock_childpidtbl();
void _dxf_update_childpid(int, int, int);
void _dxf_set_RQ_ReadFromChild1(int);
void _dxf_set_RQ_reader(int);
void _dxf_set_RQ_writer(int);

#endif /* _DXMAIN_H_ */
