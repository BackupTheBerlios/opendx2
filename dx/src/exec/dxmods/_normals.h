/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/_normals.h,v 1.2 1999/05/03 14:06:29 gda Exp $
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


