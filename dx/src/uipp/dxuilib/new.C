/*  Open Visualization Data Explorer Source File */



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
