/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


/* real entry point, calls DXmain() immediately */
extern DXmain(int argc, char **argv, char **envp);
#ifdef	DXD_WIN
#include "dx/arch.h"
#endif

#ifdef	DXD_HAS_WINSOCKETS
#include <stdio.h>
#include <winsock.h>
fd_set	sockSet;
SOCKET PASCAL FAR socket (int af, int type, int protocol);
#endif



main (argc, argv, envp)
    int		argc;
    char	**argv;
    char	**envp;
{
#ifdef  DXD_WIN
#ifdef _X86_
    HCLXtInit(); 
#endif
#endif

#if  defined(DXD_HAS_WINSOCKETS)
    {
	WSADATA wsadata;
	int i;

	i = WSAStartup(MAKEWORD(1,1),&wsadata);
	if(i != 0)
	{
	}
    }
#endif
    return DXmain(argc, argv, envp);
}

