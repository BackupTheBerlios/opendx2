/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dx/dx.h>
#include "utils.h"

void *_dxd_UserInteractors = NULL;
int _dxd_nUserInteractors = 0;

extern PFI DXLoadObjFile(char *, char *);

Error
_dxfLoadDefaultUserInteractors()
{
    char *fname;

    if ((fname = (char *)getenv("DX_USER_INTERACTOR_FILE")) != NULL)
	return _dxfLoadUserInteractors(fname);
    else
	return DXDefaultUserInteractors(&_dxd_nUserInteractors, &_dxd_UserInteractors);

    return OK;
}

Error
_dxfLoadUserInteractors(char *fname)
{
    char *path = (char *)getenv("DXUSERINTERACTORS");
    int (*func)() = DXLoadObjFile(fname, path);
    if (! func)
	DXWarning("unable to open user interactor file %s", fname);
    else
	(*func)(&_dxd_nUserInteractors, &_dxd_UserInteractors);

    return OK;

error:
    return ERROR;
}
