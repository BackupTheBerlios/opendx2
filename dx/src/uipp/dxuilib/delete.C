//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// delete.C -								    //
//                                                                          //
// Redefines the standard delete operator.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/delete.C,v 1.1 1999/03/24 15:17:49 gda Exp $
 */


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
