/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#ifndef _CACHE_H_
#define _CACHE_H_

#if 0
These access methods are specifically used to operate on dictionary entries
that are associated with the recipe cache. These are the only access methods
which will be available from the modules.
#endif

#include "d.h"
#include "graph.h"

#define EXTAG(tag) ((tag) | 0x80000000)
typedef struct pathtag
{
    char        *cpath;                 /* module path name             */
    uint32      reccrc;                 /* cache tag                    */
    int         outnbr;                 /* nth output of module         */
    int         modnbr;                 /* nth instance of module       */
    int         entry_inuse;
} pathtag;

int _dxf_ExCacheInit(void);
uint32 _dxf_ExGenCacheTag(char *function, int key, int n, uint32 *in);

int _dxf_ExCacheInsert(gvar *obj);

int _dxf_ExCacheDelete(uint32 key);

gvar *_dxf_ExCacheSearch(uint32 key);

Error _dxf_ExCacheFlush(int all);

extern EXDictionary _dxd_exCacheDict;

#endif /* _CACHE_H_ */
