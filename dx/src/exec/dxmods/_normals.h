/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/_normals.h,v 1.1 1999/03/24 15:18:24 gda Exp $
 */

typedef enum 
{
    NORMALS_MANHATTAN,
    NORMALS_AREA
} NormalsType;

typedef struct
{
    NormalsType	type;
    float	parameter;
} NormalsArg;


