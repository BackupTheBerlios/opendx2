//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// new.C -								    //
//                                                                          //
// Redefines the standard void*new(long) operator.			    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/new.C,v 1.1 1999/03/24 15:17:49 gda Exp $
 */


#include <stdio.h>
#include "defines.h"

void *operator new(size_t l)
{
//    ASSERT(l != 0);

    if (l == 0)
    {
	printf ("void *operator new(size_t): Allocating 0 bytes.\n"
		"                            Allocate 1 byte instead.\n");
	l = 1;
    }

#if defined(MALLOC_DEBUG) && !defined(__PURIFY__)
#ifdef sun4
    malloc_verify();
#endif
#endif

    void *r = (void *)MALLOC(l);

    if (!r) {
	printf("Can't allocate %d bytes...aborting!\n",l);
	fflush(stdout);
	abort();
    }

    return r;
}
