/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#include "graph.h"

typedef struct Context
{
    int userId;
    int graphId;
    Program *program;
    Program **subp;
} Context;

extern Context *_dxd_exContext;

extern void _dxfCopyContext(Context *to, Context *from);
