/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "../base/defines.h"



#ifndef _uinparse_h
#define _uinparse_h


#include <stdio.h>

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

#if defined(macos)
#define YYINITDEPTH 10
#endif

extern
int yylineno;

extern
void ParseComment(const char* comment);

extern
void ParseFunctionID(const char* name);

extern
void ParseArgument(const char* name, const boolean isVarname);

extern
void ParseLValue(const char* name);

extern
void ParseStringAttribute(const char* name, const char *value);

extern
void ParseIntAttribute(const char* name, int value);


extern
void ParseRValue(const char* name);

extern
void ParseEndOfMacroDefinition();

extern
void yyerror(char *, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _uinparse_h */
