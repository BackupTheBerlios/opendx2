/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

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
