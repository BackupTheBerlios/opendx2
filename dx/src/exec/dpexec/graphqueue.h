/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/graphqueue.h,v 1.5 2000/08/11 15:28:11 davidt Exp $
 */

#include <dxconfig.h>

#ifndef _GRAPHQUEUE_H
#define _GRAPHQUEUE_H

#include "graph.h"

int _dxf_ExGQInit (int ngraphs);
int _dxf_ExGQAllDone (void);
void _dxf_ExGQEnqueue (Program *func);
Program *_dxf_ExGQDequeue (void);

#if 0
extern int *gq_sort;
extern int ngraphs;
#endif

#endif /* _GRAPHQUEUE_H */
