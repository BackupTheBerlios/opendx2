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
#endif

static int browserPID=0;
static int fd=0;

int _dxf_StartWebBrowserWithURL(char *URL) {
    char *webApp = getenv("DX_WEB_BROWSER");

#if defined(macos)
   if(webApp) {
	CFStringRef urlStr = CFStringCreateWithCString(NULL, URL, kCFStringEncodingASCII);
	CFURLRef inURL = CFURLCreateWithString(NULL, urlStr, NULL);
	OSStatus oss = LSOpenCFURLRef( inURL, NULL);
	return !oss;
    }
    return 1;
#elif defined(intelnt)
    if(webApp) {
    HINSTANCE hinst = ShellExecute(NULL, // no parent hwnd
            NULL, // open
            URL, // topic file or URL
            NULL, // no parameters
            NULL, // folder containing file
            SW_SHOWNORMAL); // yes, show it
    return hinst > (HINSTANCE)32;
    }
    return 1;
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
