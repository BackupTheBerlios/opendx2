/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _LEX_H
#define _LEX_H

#include "parse.h"
#include "sfile.h"

#define LINEFEED 10

#define YYLMAX_1        4000            /* max string/identifer length */
#define YYLMAX          (YYLMAX_1 + 1)

typedef struct _cmdBuf
{
    char *buf;
    struct _cmdBuf *next;
} CmdBuf;

extern SFILE       *yyin; /* from lex.c */

Error _dxf_ExInitLex();
void  _dxf_ExFlushNewLine();
void  _dxf_ExLexInit();
void  _dxf_ExUIPacketActive(int id, int t, int n);
void  _dxf_ExLexError();
void  _dxf_ExUIFlushPacket();
int   ExCheckParseBuffer();
int   yylex();
void  yygrabdata(char *buffer, int len);

#endif /* _LEX_H */
