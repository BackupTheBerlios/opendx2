/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/getset.c,v 1.1 1999/03/24 15:18:28 gda Exp $
 */

#include <string.h>
#include <dx/dx.h>

#define LOCAL 			1
#define GLOBAL 			0
#define DFLT_GLOBAL             2

#define SET_OBJECT		in[0]
#define SET_LINK		in[1]
#if 0
#define SET_TRIGGER_ALWAYS	in[2]
#endif
#if 1
#define SET_KEY			in[2]
#endif

static Error Set(Object *in, Object *out, int flag);

m_Set(Object *in, Object *out)
{
    if(DXLoopFirst())
        DXWarning("#5260", "Set", "Set", "Set");
    return(Set(in, out, DFLT_GLOBAL));
}

m_SetGlobal(Object *in, Object *out)
{
    return(Set(in, out, GLOBAL));
}

m_SetLocal(Object *in, Object *out)
{
    return(Set(in, out, LOCAL));
}

static Error Set(Object *in, Object *out, int flag)
{
    char   *key = NULL, *get_modid = NULL;
    char   *set_modid = NULL;
#if 0
    int    triggerAlways = 0;
#endif
    int    trigger;
    Object old = NULL;

    if (SET_LINK)
    {
#if 0
	if (SET_TRIGGER_ALWAYS)
	{
	    if (! DXExtractInteger(SET_TRIGGER_ALWAYS, &triggerAlways) ||
		triggerAlways < 0 || triggerAlways > 1)
	    {
		DXSetError(ERROR_BAD_PARAMETER, "#10070", "trigger");
		goto error;
	    }
	}
#endif

	if (DXGetObjectClass((Object)SET_LINK) != CLASS_STRING)
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10200", "link");
	    goto error;
	}

	get_modid = DXGetString((String)SET_LINK);
        if(DXLoopFirst()) {
            char *cp;
            int len1, len2;
            cp = strrchr(get_modid, '/');
            if(cp == NULL) 
                cp = get_modid;
            else cp++;
            if(flag == LOCAL) {
                char *get_modid2;
                len1 = strlen("GetLocal:");
                if(strncmp(cp, "GetLocal:", len1) != 0) {
                    DXSetError(ERROR_BAD_PARAMETER,"#10760", "SetLocal", "GetLocal");
                    goto error;
                }
                set_modid = DXGetModuleId();
                get_modid2 = DXCopyModuleId(get_modid);
                cp = strrchr(get_modid2, '/');
                *cp = '\0';
                cp = strrchr(set_modid, '/');
                *cp = '\0';
                if(strcmp(set_modid, get_modid2) != 0) {
                    DXSetError(ERROR_INVALID_DATA, "#10762");
                    DXFreeModuleId((Pointer)set_modid);
                    DXFreeModuleId((Pointer)get_modid2);
                    goto error;
                }
                else {
                    DXFreeModuleId((Pointer)set_modid);
                    DXFreeModuleId((Pointer)get_modid2);
                }
            }
            else { /* global */
                len1 = strlen("GetGlobal:");
                len2 = strlen("Get:");
                if(strncmp(cp, "GetGlobal:", len1) != 0 &&
                   strncmp(cp, "Get:", len2) != 0) {
                    if(flag == GLOBAL) 
                        DXSetError(ERROR_BAD_PARAMETER,
                                   "#10760", "SetGlobal", "GetGlobal");
                    else 
                        DXSetError(ERROR_BAD_PARAMETER, "#10760", 
                         "Set is now an alias for SetGlobal; SetGlobal", "GetGlobal");
                    goto error;
                }
            }
        }
    }

#if 1
    if (SET_KEY)
    {
	if (DXGetObjectClass((Object)SET_KEY) != CLASS_STRING)
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10200", "key");
	    goto error;
	}

	key = DXGetString((String)SET_KEY);
    }
    else
#endif
	key = get_modid;
    
    if (! key)
    {
#if 0
	DXSetError(ERROR_BAD_PARAMETER, "#10764", "either link or key");
#else
	DXSetError(ERROR_BAD_PARAMETER, "#10764", "link");
#endif
	goto error;
    }

    old = DXGetCacheEntry(key, 0, 0);

    trigger = !old || (DXGetObjectTag(old) != DXGetObjectTag(SET_OBJECT));

    if (trigger)
    {
	if (! DXSetCacheEntry(SET_OBJECT, CACHE_PERMANENT, key, 0, 0))
	    goto error;
    
#if 0
	if (triggerAlways)
	    DXReadyToRun(get_modid);
	else
#endif
	    DXReadyToRunNoExecute(key);
    }

    DXDelete(old);
    return OK;

error:
    out[0] = NULL;
    DXDelete(old);
    return ERROR;
}

#define GET_OBJECT		in[0]
#define GET_RESET		in[1]
#if 1
#define GET_KEY			in[2]
#endif

static Error Get(Object *in, Object *out, int flag);

m_GetLocal(Object *in, Object *out)
{
    return(Get(in, out, LOCAL));
}

m_GetGlobal(Object *in, Object *out)
{
    return(Get(in, out, GLOBAL));
}

m_Get(Object *in, Object *out)
{
    if(DXLoopFirst())
        DXWarning("#5260", "Get", "Get", "Get");
    return(Get(in, out, GLOBAL));
}

static Error Get(Object *in, Object *out, int flag)
{
    char *key = NULL, *modid = NULL;
    int  reset = 0;

    key = modid = (char *)DXGetModuleId();
    if (! modid)
	goto error;
    
    if(flag == LOCAL && DXLoopFirst())
        reset = 1;
    else if (GET_RESET)
    {
	if (! DXExtractInteger(GET_RESET, &reset) ||
	    reset < 0 || reset > 1)
	{
	    DXSetError(ERROR_BAD_PARAMETER, "#10070", "reset");
	    goto error;
	}
    }

#if 1
    if (GET_KEY)
    {
	key = DXGetString((String)GET_KEY);
    }
#endif

    if (reset)
    {
	out[0] = GET_OBJECT;
	DXSetCacheEntry(NULL, CACHE_PERMANENT, key, 0, 0);
    }
    else
    {
	out[0] = DXGetCacheEntry(key, 0, 0);
	if (out[0])
	    DXDelete(out[0]);
	else
	    out[0] = GET_OBJECT;
    }
    
    out[1] = (Object)DXNewString(modid);
    
    DXFreeModuleId((Pointer)modid);

    return OK;

error:
    DXFreeModuleId((Pointer)modid);
    out[0] = NULL;
    out[1] = NULL;
    return ERROR;
}
