/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dx/dx.h>
#include "context.h"

void _dxfCopyContext(Context *to, Context *from)
{
    memcpy(to, from, sizeof(Context));
}

