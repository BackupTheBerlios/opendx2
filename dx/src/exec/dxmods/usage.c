/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>




#include <dx/dx.h>

int
m_Usage(Object *in, Object *out)
{
    char *s;

    if (!DXExtractString(in[0], &s))
	DXErrorReturn(ERROR_BAD_PARAMETER, "nothing to print specified");
    
    if (strcmp(s, "memory")==0) {
	int how = 0;
	if (in[1] && !DXExtractInteger(in[1], &how))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad how");
 	DXPrintAlloc(how);
	
    } else if (strcmp(s, "memory small")==0) {
	int how = 0;
	if (in[1] && !DXExtractInteger(in[1], &how))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad how");
 	DXPrintAlloc(how|0x10);

    } else if (strcmp(s, "memory large")==0) {
	int how = 0;
	if (in[1] && !DXExtractInteger(in[1], &how))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad how");
 	DXPrintAlloc(how|0x20);

    } else if (strcmp(s, "memory local")==0) {
	int how = 0;
	if (in[1] && !DXExtractInteger(in[1], &how))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad how");
 	DXPrintLocalAlloc(-1, how);

#if 1    /* this code is in mem.c */
    } else if (strcmp(s, "memory info")==0) {
#ifndef	DXD_WIN
 	DXPrintMemoryInfo ();
#endif
#endif

#if 0
    } else if (strcmp(s, "time")==0) {
	char *msg = "";
	if (in[1] && !DXExtractString(in[1], &msg))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad message");
	DXPrintTime(msg);
#endif

#if 0
    } else if (strcmp (s, "visual memory") == 0) {
	int how = 0;
	if (in[1] && !DXExtractInteger(in[1], &how))
	    DXErrorReturn(ERROR_BAD_PARAMETER, "bad how");
	DXVisualizeMemory (how);
#endif
    } else {
	DXSetError(ERROR_BAD_PARAMETER, "don't know how to print %s", s);
	return ERROR;
    }

    return OK;
}














