/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


#if 0
These access methods are specifically used to operate on dictionary entries
which are user-variable definitions.
#endif

#ifndef __VARIABLE_H
#define __VARIABLE_H

#include "d.h"

int	_dxf_ExVariableInsert(char *name, EXDictionary dict, EXObj obj);
int	_dxf_ExVariableDelete(char *name, EXDictionary dict);
EXObj	_dxf_ExVariableSearch(char *name, EXDictionary dict);
void    _dxf_ExGVariableSetStr(char *var, char *val);
char *  _dxf_ExGVariableGetStr(char *var);

Error   _dxf_ExUpdateGlobalDict (char *name, Object obj, 
                                 int cause_execution);
EXObj   _dxf_ExGlobalVariableSearch (char *name);
Error   DXSetIntVariable(char *name, int val, int sync, 
                         int cause_execution);
Error   DXSetVariable(char *name, Object obj, int sync, 
                      int cause_execution);

extern EXDictionary _dxd_exGlobalDict;

#endif /* __VARIABLE_H */
