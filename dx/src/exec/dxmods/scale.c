/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/scale.c,v 1.3 1999/05/10 15:45:30 gda Exp $
 */

#include <dxconfig.h>



#include <dx/dx.h>


int
m_Scale(Object *in, Object *out)
{
    Vector v;

    out[0] = NULL;

    if(!in[0]) {
	DXSetError(ERROR_BAD_PARAMETER, "#10000", "input");
	return NULL;
    }

    if(!in[1]) {
	out[0] = (Object)DXNewXform(in[0], DXScale(1.0, 1.0, 1.0));
	return (out[0] ? OK : ERROR);
    }

    /* either a 3D vector or a single scalar */
    if(DXExtractParameter(in[1], TYPE_FLOAT, 3, 1, (Pointer)&v))
        ;
    else if(DXExtractFloat(in[1], (float *)&v)) {  /* returns with v.x set */
        v.y = v.x;
        v.z = v.x;
    } else {
        DXSetError(ERROR_BAD_PARAMETER, 
		 "%s must be a scalar or a 3-vector",
		 "scale");
	return NULL;
    }

        
    /* if scale factors are all zero, the object will disappear - which
     *  might be the intent, but put out a warning anyway.
     */
    if((v.x == 0.0) && (v.y == 0.0) && (v.z == 0.0))
        DXWarning("scaling by 0, output will be single point");
    
    out[0] = (Object)DXNewXform(in[0], DXScale(v.x, v.y, v.z));

    return(out[0] ? OK : ERROR);
}




