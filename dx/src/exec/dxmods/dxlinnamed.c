/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>




#include <stdio.h>
#include <dx/dx.h>

extern Error DXRegisterForNotification(char *, Pointer);
extern Error DXNotifyRegistered(char *);
extern Error DXGetVariable(char *, Object *);
extern Error DXSetVariable(char *, Object);
extern Error _dxf_ExRunOn(int, Error(*)(Object *), Pointer, int);

#define NAME	in[0]
#define DEFAULT	in[1]
#define RESULT	out[0]

static Error _getv(Object *args)
{
    char *name;

    if (DXExtractString(args[0], &name))
	if (! DXGetVariable(name, &args[1]))
	    args[1] = NULL;
    
    return OK;
}
       
static Error _setv(Object *args)
{
    char *name;

    if (DXExtractString(args[0], &name))
	if (! DXSetVariable(name, args[1]))
	    args[1] = NULL;
    
    return OK;
}
       

int
m_DXLInputNamed(Object *in, Object *out)
{
    char *name;
    Object *args = DXAllocate(2*sizeof(Object));
    Pointer modid;

    if (! DXExtractString(NAME, &name))
    {
	DXSetError(ERROR_BAD_PARAMETER, "name");
	return ERROR;
    }

    args[0] = NAME;
    args[1] = NULL;

    if (! _dxf_ExRunOn(1, _getv, (Pointer)args, 0))
    {
	DXSetError(ERROR_INTERNAL, "_getv");
	return ERROR;
    }

    if (args[1])
	RESULT = args[1];
    else
	RESULT = DEFAULT;

    modid = DXGetModuleId();

    if (! DXRegisterForNotification(name, modid))
	return ERROR;

    DXFreeModuleId(modid);

    DXFree((Pointer)args);

    return OK;
}

#define VALUE	in[1]

int
m_SetDXLInputNamed(Object *in, Object *out)
{
    char *name;
    Object *args = DXAllocate(2*sizeof(Object));

    if (! DXExtractString(NAME, &name))
    {
	DXSetError(ERROR_BAD_PARAMETER, "name");
	return ERROR;
    }

    args[0] = NAME;
    args[1] = VALUE;

    if (! _dxf_ExRunOn(1, _setv, (Pointer)args, 0))
    {
	DXSetError(ERROR_INTERNAL, "_setv");
	return ERROR;
    }

    DXNotifyRegistered(name);

    DXFree((Pointer)args);

    return OK;
}
