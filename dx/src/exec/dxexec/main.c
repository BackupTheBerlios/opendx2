/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>

#include <fcntl.h>


/* real entry point, calls DXmain() immediately */
extern DXmain(int argc, char **argv, char **envp);
#ifdef	DXD_WIN
#include "dx/arch.h"
#endif

#if defined(HAVE_WINSOCK_H)
#include <winsock.h>
#endif

main (argc, argv, envp)
    int		argc;
    char	**argv;
    char	**envp;
{
#if defined(intelnt)
    HCLXtInit(); 

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

