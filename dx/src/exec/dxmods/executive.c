/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>



/***
MODULE:
 Executive
SHORTDESCRIPTION:
 Execute an executive command
CATEGORY:
 Debugging
INPUTS:
    input;     String;  (none); Command to be executed
    input;     Object;  (none); Command-dependent
REPEAT: 1
OUTPUTS:
END:
***/

#include <string.h>
#include <dx/dx.h>

/* prototypes for things in command.c */
extern Error _dxf_ExExecCommand(Object *in);

Error m_Executive(Object *in, Object *out)
{
    return (_dxf_ExExecCommand (in));
}
