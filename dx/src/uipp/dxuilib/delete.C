/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "UIConfig.h"
#include "defines.h"
void operator delete(void *p)
{
//    ASSERT(p != NULL);

#if defined(MALLOC_DEBUG) && !defined(__PURIFY__)
#ifdef sun4
    malloc_verify();
#endif
#endif

    if (p == NULL)
    {
	printf("void operator delete(void*): Freeing NULL pointer\n");
    }
    else
	FREE(p);
}
