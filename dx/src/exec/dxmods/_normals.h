/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/_normals.h,v 1.3 1999/05/10 15:45:20 gda Exp $
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


