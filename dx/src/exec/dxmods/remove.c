/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dx/dx.h>

extern Error _dxfParmCheck(int nobjs, Object o1, char *oname1,
  	                              Object o2, char *oname2,
 	                  int nparms, Object p1, char *name1, int nullok1,
 	                              Object p2, char *name2, int nullok2,
	                  int parmlist);

extern Object _dxfDXEmptyObject(Object o);



int
m_Remove(Object *in, Object *out)
{
    char *old;
    int compname = 0;

    out[0] = NULL;

    if (!_dxfParmCheck(1, in[0], "input", NULL, NULL,
		       1, in[1], "component name", 0,
		          NULL,   NULL,            0, 1))
	return ERROR;


    if (_dxfDXEmptyObject(in[0])) {
	DXWarning("#4000", "input");
	out[0] = in[0];
	return OK;
    }


    /* for each component to remove... 
     */
    for (compname = 0; DXExtractNthString(in[1], compname, &old); compname++) {

	if (!DXExists(in[0], old)) {
	    DXWarning("#10252", "input", old);
	    continue;
	}
	
	if (!out[0]) {
	    out[0] = DXCopy(in[0], COPY_STRUCTURE);
	    if (!out[0])
		return ERROR;
	}

	if (!DXRemove(out[0], old))
	    goto error;

    }

    /* nothing to remove; return input unchanged */
    if (!out[0])
	out[0] = in[0];

    return OK;

  error:
    DXDelete(out[0]);
    out[0] = NULL;
    return ERROR;    
}
