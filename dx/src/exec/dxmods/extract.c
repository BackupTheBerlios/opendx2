/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#include <string.h>
#include <dx/dx.h>

extern Error _dxfParmCheck(int nobjs, Object o1, char *oname1,
  	                              Object o2, char *oname2,
 	                  int nparms, Object p1, char *name1, int nullok1,
 	                              Object p2, char *name2, int nullok2,
	                  int parmlist);

extern Object _dxfDXEmptyObject(Object o);


int
m_Extract(Object *in, Object *out)
{
    char *name;

    if (!_dxfParmCheck(1, in[0], "input", NULL, NULL,
		       1, in[1], "component name", 1,
		          NULL,   NULL,            0, 0)) {
	out[0] = NULL;
	return ERROR;
    }

    if (_dxfDXEmptyObject(in[0])) {
	DXWarning("#4000", "input");
	out[0] = in[0];
	return OK;
    }

    
    if(in[1]) 
	DXExtractString(in[1], &name);
    else
	name = "data";
    

    if (!DXExists(in[0], name)) {
	out[0] = NULL;
        DXSetError(ERROR_MISSING_DATA, "#10252", "input", name);
        return ERROR;
    }


    /* extract may return a new object (if a simple field is a passed
     * in, an array is returned.)  the extract routine takes care of
     * deleting the original if necessary.
     */
    out[0] = DXCopy(in[0], COPY_STRUCTURE);
    if(!out[0])
	return ERROR;
    
    if (!(out[0] = DXExtract(out[0], name))) {
	DXDelete(out[0]);
	out[0] = NULL;
	return ERROR;
    }

    return OK;
}
