/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dpexec/crc.h,v 1.4 2000/08/11 15:28:10 davidt Exp $
 */

#include <dxconfig.h>


#ifndef	__EX_CRC_H
#define	__EX_CRC_H

typedef uint32 			EXCRC;

#define	EX_INITIAL_CRC		0xffffffff

EXCRC	_dxf_ExCRCByte		(EXCRC crc, unsigned char     v);
EXCRC	_dxf_ExCRCInt		(EXCRC crc, int      v);
EXCRC	_dxf_ExCRCFloat		(EXCRC crc, double   v);
EXCRC	_dxf_ExCRCDouble	(EXCRC crc, double   v);
EXCRC	_dxf_ExCRCString	(EXCRC crc, char    *v);

EXCRC	_dxf_ExCRCByteV 	(EXCRC crc, unsigned char *v, int tsize, int n);
EXCRC	_dxf_ExCRCByte0 	(EXCRC crc, unsigned char    *v);
EXCRC	_dxf_ExCRCIntV		(EXCRC crc, int     *v, int n);
EXCRC	_dxf_ExCRCFloatV	(EXCRC crc, float   *v, int n);
EXCRC	_dxf_ExCRCDoubleV	(EXCRC crc, double  *v, int n);

#endif	/* __EX_CRC_H */

