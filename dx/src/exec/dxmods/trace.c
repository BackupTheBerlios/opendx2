/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#include <dx/dx.h>


extern void DXTraceTask(int t);
#if 0
extern Error DXTagMemory(int n);
#endif


Error
m_Trace(Object *in, Object *out)
{
    char *s;
    int how = 1;

    if (!DXExtractString(in[0], &s)) {
	DXSetError(ERROR_BAD_PARAMETER, "#10200", "`trace'");
	return ERROR;
    }
    if (in[1] && !DXExtractInteger(in[1], &how)) {
	DXSetError(ERROR_BAD_PARAMETER, "#10010", "`how'");
	return ERROR;
    }

    if (strcmp(s, "memory")==0)
	DXTraceAlloc(how);

#if 0
    else if (strcmp(s, "tag memory")==0)
	DXTagMemory(how);
#endif

    else if (strcmp(s, "objects")==0)
	_dxfTraceObjects(how);

    else if (strcmp(s, "tasks")==0)
	DXTraceTask(how);

#if 1
    else if (strcmp(s, "visual memory")==0)
	DXVisualizeMemory(how, 0);
#endif

#if 0
    else if (strcmp(s, "dump memory")==0)
	DXMemoryDump(how);
#endif

    else if (strcmp(s, "time")==0) {
        if (how==0)
            DXPrintTimes();
	DXTraceTime(how);
    }

    else
	DXEnableDebug(s, how);

    return OK;
}
