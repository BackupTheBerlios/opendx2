/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999,2002                              */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if defined(macos)
#include <ApplicationServices/ApplicationServices.h>
#endif

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(HAVE_SYS_TYPES_H)
#include <sys/types.h>
#endif

#if defined(HAVE_SYS_WAIT_H)
#include <sys/wait.h>
#endif

#if defined(HAVE_SIGNAL_H)
#include <signal.h>
#endif

#if defined(HAVE_WINDOWS_H)
#include <windows.h>
#include <shellapi.h>
#include <process.h>
#endif

static int browserPID=0;
static int fd=0;

#if defined (intelnt)

#if 0
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam) {
   DWORD wndPid;

   GetWindowThreadProcessId(hwnd, &wndPid);
   if( wndPid == (DWORD)lparam ) {
//	fprintf(stderr, "Found process--rising\n");
	SetForegroundWindow( hwnd );
	SetActiveWindow( hwnd );
	return false;
   }
   else
	return true;
}
#endif

int ExecuteCommand(char *cmd,int nCmdShow)
{
   STARTUPINFO startInfo;
   int processStarted;
   unsigned long result;
   PROCESS_INFORMATION pi;
   char msgbuf[4096];

   memset(&startInfo,0,sizeof(STARTUPINFO));
   startInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEONFEEDBACK;
   startInfo.wShowWindow = nCmdShow;
   processStarted = CreateProcess(NULL,cmd,NULL,NULL,0,
      NORMAL_PRIORITY_CLASS,
      NULL,NULL,&startInfo,&pi);
   if (processStarted == 0)
      return -1;
   WaitForInputIdle(pi.hProcess, INFINITE);
//   AttachThreadInput( pi.dwThreadId, GetCurrentThreadId(), TRUE);
//   EnumWindows ( EnumWindowsProc, (LPARAM) pi.dwProcessId ); 
   result = 0;
   CloseHandle(pi.hProcess);
   CloseHandle(pi.hThread);
   return result;

}
#endif

int _dxf_StartWebBrowserWithURL(char *URL) {
    char *webApp = getenv("DX_WEB_BROWSER");

#if defined(macos)
   if(webApp) {
   	OSStatus oss;
   	CFURLRef outAppURL;
   	oss = LSGetApplicationForInfo(kLSUnknownType, kLSUnknownCreator, CFSTR("html"),
   		kLSRolesViewer, NULL, &outAppURL);
	CFStringRef urlStr = CFStringCreateWithCString(NULL, URL, kCFStringEncodingUTF8);
	CFURLRef inURL = CFURLCreateWithString(NULL, urlStr, NULL);
	CFArrayRef arRef = CFArrayCreate(NULL, (const void**)&inURL, 1, NULL);
   	LSLaunchURLSpec lurl = { outAppURL, arRef, NULL, kLSLaunchDefaults, NULL};
	oss = LSOpenFromURLSpec ( &lurl , NULL );
	CFRelease(urlStr);
	CFRelease(inURL);
	CFRelease(arRef);
	return !oss;
    }
    return 0;
#elif defined(intelnt)
    #define MAXPATH 4096
    if(webApp) {
	FILE *f;
	char CmdLine[MAXPATH];
	char fname[MAXPATH];
	char *p;

	GetTempPath(MAXPATH, fname);
	if (p = strrchr(fname, '\\'))
	    *p = 0;
	sprintf(fname, "%s%s.%s", fname, tmpnam(NULL), ".htm");
	f = fopen(fname,"wb");

	if (f == NULL)
	    return 0;
	fwrite((char *)"tempfile",1,8,f);
	fclose(f);

	HINSTANCE hinst = FindExecutable(fname, NULL, CmdLine);
	strcpy(CmdLine, "\"C:\\Program Files\\Netscape\\Communicator\\Program\\netscape.exe\"");
	if ((int)hinst > 32) {
	    strcat(CmdLine, " ");
	    strcat(CmdLine, URL);
	    ExecuteCommand(CmdLine, SW_SHOWNORMAL);
//	    ShellExecute(NULL, "open", CmdLine, URL, NULL, SW_SHOWNORMAL);
	}
	unlink(fname);
    	return hinst > (HINSTANCE)32;
    }
    return 0;
#else
    if(browserPID != 0) {
	if(waitpid(browserPID, NULL, WNOHANG)==browserPID) {
		browserPID = 0;
	} else {
	    int child = fork();
	    if (child == 0) {
		if(webApp) {
			char *openURL = new char[strlen(URL) + 25];
			//strcpy(openURL, "-remote ");
			strcpy(openURL, "openURL(");
			strcat(openURL, URL);
			strcat(openURL, ")");
			int ret = execlp(webApp, webApp, "-raise", "-remote", openURL, NULL);
            		if (!ret) fprintf(stderr, "Unable to start web browser.\n");
			delete openURL;
			exit (0);
		}
	    } else if (child > 0) {
		return 1;
	    } else {
		fprintf(stderr, "Unable to fork child.\n");
		return 0;
	    }
	}
    }
    int child = fork();
    if (child == 0) {
	if(webApp) {
    	    int ret = execlp(webApp, webApp, URL, NULL);
	    if (!ret) fprintf(stderr, "Unable to start web browser.\n");
	    exit (0);
	}
    } else if (child > 0) {
	sleep (2);
	browserPID = child;
	// Now check to see if child exists, if not, probably no browser.
	if(waitpid(child, NULL, WNOHANG)==child)
		return 0;
	else
		return 1;
    } else {
	fprintf(stderr, "Unable to fork child.\n");
	return 0;
    }
#endif

}
