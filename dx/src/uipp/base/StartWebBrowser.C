/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999,2002                              */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/


#if defined(macos)
#include <ApplicationServices/ApplicationServices.h>
#endif

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

int _dxf_StartWebBrowserWithURL(char *URL) {

#if defined(macos)
    CFStringRef urlStr = CFStringCreateWithCString(NULL, URL, kCFStringEncodingASCII);
    CFURLRef inURL = CFURLCreateWithString(NULL, urlStr, NULL);
    OSStatus oss = LSOpenCFURLRef( inURL, NULL);
    return !oss;
#endif

    char *webApp = getenv("DX_WEB_BROWSER");
    if(webApp) {
    	char *launchStr = new char[strlen(URL) + strlen(webApp) + strlen(" -remote 'openURL()' ") +3];
    	strcpy(launchStr, webApp);
    	strcat(launchStr, " -remote 'openURL(");
    	strcat(launchStr, URL);
    	strcat(launchStr, ")'");
    	int ret = system(launchStr);
    	delete launchStr;
	return !ret;
    }

}