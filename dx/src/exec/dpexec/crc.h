/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

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

