/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#include <string.h>
#include "stringClass.h"

char *
DXGetString(String s)
{
    CHECK(s, CLASS_STRING);
    return s->string ? s->string : s->shortstr;
}

Error
_dxfString_Delete(String s)
{
    if (s->string)
	DXFree(s->string);
    return OK;
}

#define SHAREDSTRINGS 1

static String
_NewString(char *s, struct string_class *class)
{
    int n;
    String o;

    if (!s)
	return NULL;

#if SHAREDSTRINGS
    o = (String)_dxfstringobject(s, 0);
    if (o)
	return o;
#endif

    o = (String) _dxf_NewObject((struct object_class *)class);
    if (!o)
	return NULL;

    n = strlen(s)+1;
    if (n <= IMBEDDED) {
	o->string = NULL;
	memcpy(o->shortstr, s, n);
    } else {
	o->string = DXAllocate(n);
	if (!o->string) {
	    DXDelete((Object)o);
	    return NULL;
	}
	memcpy(o->string, s, n);
    }

    return o;
}

String
DXNewString(char *s)
{
    return _NewString(s, &_dxdstring_class);
}

Object
_dxfString_Copy(String old, enum copy copy)
{
    if (copy==COPY_DATA)
	DXErrorReturn(ERROR_BAD_PARAMETER, "copying data is not implemented");
    return (Object)old;
}

String DXMakeString(char *s)
{
    return (Object)DXNewString(s);
}
