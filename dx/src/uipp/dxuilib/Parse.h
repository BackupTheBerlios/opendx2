/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/* uinparse.h - module header file					     */
/* Contains parser action routines.					     */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Parse.h,v 1.1 1999/03/24 15:17:44 gda Exp $
 */

#ifndef _uinparse_h
#define _uinparse_h


#include <stdio.h>
#include "defines.h"

#if defined(__cplusplus) || defined(c_plusplus)
class Network;
#else
typedef struct _Network_ Network;
#endif


/***
 *** Functions:
 ***/

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif
extern
void ParseComment(char* comment);

extern
void ParseFunctionID(char* name);

extern
void ParseArgument(char* name, const boolean isVarname);

extern
void ParseLValue(char* name);

extern
void ParseStringAttribute(char* name, char *value);

extern
void ParseIntAttribute(char* name, int value);


extern
void ParseRValue(char* name);

extern
void ParseEndOfMacroDefinition();

extern
void yyerror(char *, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _uinparse_h */
