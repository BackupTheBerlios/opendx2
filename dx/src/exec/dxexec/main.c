/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>

/* real entry point, calls DXmain() immediately */
extern DXmain(int argc, char **argv, char **envp);

#if defined(intelnt) || defined(WIN32)
#include <dx/arch.h>
#include <windows.h>
#endif

#if defined(DX_NATIVE_WINDOWS)
extern int DXInitializeWindows(HINSTANCE);
int errno;
#endif

#if defined(HAVE_WINSOCK_H)
#include <winsock.h>
#endif

void sig(int s)
{
    fprintf(stderr, "%d: signal %d caught\n", getpid(), s);
    abort();
}


#if defined(DX_NATIVE_WINDOWS) && defined(_WINDOWS)

/* The following creates memory that won't be freed. */
char * WideToAnsi(LPCWSTR wstr) {
	char *cvtval;
	int len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, 
		wstr, -1, NULL, 0, NULL, NULL);
	cvtval = (char *) DXAllocate (len + 1);
	len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, 
		wstr, -1, cvtval, len, NULL, NULL);
	if(!len) {
		printf("Error converting argv.\n");
	}
	return cvtval;
}

char **argv = NULL;
char **envp = NULL;
int argc = 0;
int 
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nShowCmd)

#else

int 
main (argc, argv, envp)
    int		argc;
    char	**argv;
    char	**envp;
#endif

{
#if defined(DX_NATIVE_WINDOWS) && defined(_WINDOWS)
	LPWSTR *wargv; int i;
#endif
#if defined(intelnt) || defined(WIN32)
    {
		WSADATA wsadata;
		int i;

		i = WSAStartup(MAKEWORD(1,1),&wsadata);
		if (i!=0) {
			MessageBox(NULL, TEXT("Unable to initalize executive networking. Now exiting."),
				TEXT("Network Error"), MB_OK | MB_ICONERROR);
			exit (1);
		}
    }
#endif

#if defined(DX_NATIVE_WINDOWS) && defined(_WINDOWS)
	wargv = CommandLineToArgvW( GetCommandLineW(), &argc );
	for(i=0; i < argc; i++)
		argv[i] = WideToAnsi(wargv[i]);
	if (!DXInitializeWindows(hInstance)) {
			MessageBox(NULL, TEXT("Could now initialize windows. Now exiting."),
				TEXT("DXInit Error"), MB_OK | MB_ICONERROR);
		return 0;
	}
#elif defined(DX_NATIVE_WINDOWS) && defined(_CONSOLE)
	if (!DXInitializeWindows(GetModuleHandle(NULL))) {
			MessageBox(NULL, TEXT("Could now initialize windows. Now exiting."),
				TEXT("DXInit Error"), MB_OK | MB_ICONERROR);
		return 0;
	}
#endif

    signal(SIGSEGV, sig);

    return DXmain(argc, argv, envp);
}


#if 0

int WINAPI
WinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nShowCmd)
   {
	char **argv = NULL, *buf = NULL; 
	int argc = 0;
	
	if (lpCmdLine)
	{
		int i;
		char *s, *d;
		d = buf = malloc(strlen(lpCmdLine)+1);
		
		argc = 0;
		s = lpCmdLine;
		while (*s)
		{
			if (*s == '"')
			{	
		       while (*s && *s != '"')
			   	   *d++ = *s++;
				
			   if (! *s)
			   {
					fprintf(stderr, "unmatched quote\n");
					return 0;
			   }

			   s++;
			   s++;
			   d++;
			   *d++ = '\0';
			   argc++;
			}
			else 
			{
				while (*s && (*s == ' ' || *s == '\t'))
				    s++;

				if (*s)
				{
					while (*s && *s != ' ' && *s != '\t')
						*d++ = *s++;

					*d++ = '\0';
					argc++;
				}
			}
		}
	    argc += 1;
		argv = malloc((argc+1)*sizeof(char *));

		argv[0] = "dxexec.exe";

		for (i = 1, d = buf; i < argc; i++)
		{
			argv[i] = d;
			while (*d++);
		}

		argv[argc] = '\0';
	}
 
	{
		int hCrt;
		FILE *hf;
		
		AllocConsole();

		hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "w");
		*stdout = *hf;
	    setvbuf(stdout, NULL, _IONBF, 0);
		
		hCrt = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "w");
		*stderr = *hf;
		setvbuf(stderr, NULL, _IONBF, 0);

        hCrt = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
		hf = _fdopen(hCrt, "r");
		*stdin = *hf;
        setvbuf(stdin, NULL, _IONBF, 0);
	}

 	if (!DXInitializeWindows(hInstance))
		return 0;

	fprintf(stdout, "%d 0x%08lx", _fileno(stdin), (int)stdin);
	return 	DXmain(argc, argv, NULL); 

}

#endif

