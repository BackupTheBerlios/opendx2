/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/log.h,v 1.6 2004/06/03 16:27:16 davidt Exp $
 */

#include <dxconfig.h>

#ifndef _LOG_H
#define _LOG_H

#define LOG_FATAL	0
#define LOG_ERROR	1
#define LOG_WARNING	2
#define LOG_STATUS	3
#define LOG_INFO	4
#define LOG_VERBOSE	5

#define LOG_APPEND	0x8000
#define LOG_MASK	0x7fff

int _dxf_ExLogOpen();
void _dxf_ExLogClose();
int lprintf(int type, char *format, ...);
void _dxf_ExQMessage(int type, int graphId, int len, char *buf);
void _dxf_ExLogError (int errnum);

#endif /* _LOG_H */
