/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#if 0
These access methods are used to operate on dictionary entries which are
macro and function definitions.  The macro definitions are actually stored
as parse trees to facilitate their inclusion upon execution.  Function
definitions are stored as a pointer to a function.  Each of the definitions
are wrapped in a parse node to store additional information such as
number of inputs and their names and number of outputs and their names.
#endif

#ifndef __MACRO_H
#define __MACRO_H

#include "d.h"

Error	_dxf_ExMacroInit	(void);
int	_dxf_ExMacroInsert	(char *name, EXObj obj);
int	_dxf_ExMacroDelete	(char *name);
EXObj	_dxf_ExMacroSearch	(char *name);

extern	EXDictionary	_dxd_exMacroDict;

#endif /* __MACRO_H */
