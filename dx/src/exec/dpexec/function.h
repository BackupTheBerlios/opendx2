/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "utils.h"

Error _dxf_ExFunctionDone ();
Error DXAddModuleV (char *name, PFI func, int flags, int nin, char *inlist[],
                    int nout, char *outlist[], char *exec, char *host);
Error DXAddModule (char *name, ...);

#endif /* _FUNCTION_H */
