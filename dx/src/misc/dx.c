/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*  DX script - C version	*/
/*  F. Suits   1/97		*/

#include <dxconfig.h>
#include <dx/arch.h>

#ifdef DXD_WIN
#include <windows.h>
#endif

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(HAVE_ERRNO_H)
#include <errno.h>
#endif

#if defined(HAVE_PROCESS_H)
#include <process.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DXD_WIN
#define EXE_EXT ".exe"
#define DXD_ARCHNAME "intelnt"
#define DIRSEP "\\"
#define PATHSEP ";"
#else
#define EXE_EXT ""
#define DIRSEP "/"
#define PATHSEP ":"
#endif

#ifndef DXD_ARCHNAME
#define DXD_ARCHNAME "unix"
#endif

#define SCRIPTVERSION DXD_VERSION_STRING

#define IBM_ID 1
#define HUMMBIRD_ID 2

#define SMALLSTR 50
#define MAXARGS 200
#define MAXNAME 256
#define MAXENV  1024
#define MAXPARMS 200

#if defined(HAVE__SPAWNVP) && !defined(HAVE_SPAWNVP)
#define spawnvp _spawnvp
#endif

#define IfError(s)		\
    if (rc != ERROR_SUCCESS) {	\
	strcpy(errstr, s);	\
	goto error;		\
    }

#define IfError2(s, t, u)			\
    if (rc != ERROR_SUCCESS) {			\
	sprintf(errstr, "%s %s %s", s, t, u);	\
	goto error;				\
    }

#define ErrorGoto(s) {		\
	strcpy(errstr, s);	\
	goto error;		\
    }

#define ErrorGoto2(s, t, u) {			\
	sprintf(errstr, "%s %s %s", s, t, u);	\
	goto error;				\
    }

#define KILLSEMI(s) {							\
	int kk;								\
	while ((kk = strlen(s)) && ((s[kk-1] == ';') || (s[kk-1] == ' ')))	\
	    s[kk-1] = '\0';						\
    }

typedef char smallstr[SMALLSTR];
typedef char envstr[MAXENV];
typedef char namestr[MAXNAME];
typedef char valuestr[MAXNAME];

namestr	parm[MAXPARMS];

int	p =		0;
int	numparms =	0;

int	exonly =	0;
int	uionly =	0;
int	startup =	0;
int	dxdataset =	0;
int	seecomline =	0;
int	echo =		0;
int	help =		0;
int	morehelp =	0;
int	showversion =	0;
int	prompter =	0;
int	tutor =		0;
int	builder =	0;
int	wizard = 	0;
int	portset =	0;
int	dxregister =	0;

envstr		cmd =		"";
envstr		outenv =	"";
envstr		pipestr =	"";
envstr		path =		"";

envstr		dxargs =	"";
smallstr	uimode =	"";
smallstr	exmode =	"";
namestr		exhost =	"";
namestr		cdto =		"";
namestr		exmem =		"";
namestr 	uimem =		"";
namestr		exprocs =	"";
namestr 	uiflags =	"";
namestr 	errmsg =	"";
namestr 	display =	"";
smallstr 	uilog =		"";
smallstr 	exlog =		"";
smallstr 	uicache =	"";
smallstr 	excache =	"";
smallstr 	extrace =	"";
smallstr 	uitrace =	"";
smallstr 	exread =	"";
smallstr 	uiread =	"";
smallstr 	extime =	"";
smallstr 	uitime =	"";
smallstr 	exhilite =	"";
smallstr 	uihilite =	"";
smallstr 	exlic =		"";
namestr 	FileName =	"";
namestr 	dxroot =	"";
namestr 	dxrootreg =	"";
namestr 	dxexroot =	"";
namestr 	dxuiroot =	"";
namestr 	exceeddir =	"";
namestr 	exceeduserdir =	"";
namestr		xnlspath =	"";
namestr		xapplresdir =	"";
namestr		xkeysymdb =	"";
namestr 	dxexec =	"";
namestr 	dxmdf =		"";
namestr 	exmdf =		"";
namestr 	uimdf =		"";
namestr 	dxui =		"";
envstr 		dxdata =	"";
envstr	 	dxmacros =	"";
envstr 		dxmodules =	"";
namestr 	uirestrict =	"";
namestr	 	prompterflags =	"";
namestr		licensekey =	"";
namestr		dxhwmod =	"";
smallstr	port = 		"";
smallstr	host =		"";
smallstr	dx8bitcmap =	"";
namestr		dxinclude =	"";
smallstr	dxcolors =	"";
smallstr	exarch = 	"";
smallstr	uiarch =	"";
namestr		curdir =	"";
namestr		dxexecdef = 	"";
namestr		dxmode =	"";
namestr		motifbind = 	"DX*officialmascot: fred";
envstr		exflags = 	"";
namestr		exproc = 	"";
namestr		exerrlvl = 	"";
namestr		exdist =	"";
namestr		exoutdb = 	"";
namestr		uidepth =	"";
namestr		uiproc =	"";
namestr		uioutdb =	"";
namestr		xparms =	"";
namestr		installdate =	"";
namestr		xservername =	"";
namestr		xserverversion= "";
namestr		thishost = 	"localhost";
smallstr 	uidebug =	"";
namestr		username =	"";
namestr		userco =	"";

envstr		teststr = 	"";
namestr		msgstr =	"";
namestr		errstr =	"";
envstr		argstr =	"";

int getenvstr(char *name, char *value);
int putenvstr(char *name, char *value);
int regval(int get, char *name, int co, char *value, int size, int *word);
int initrun();
int getparms(int argc, char **argv);
int fillparms(char *str, int *n);
int configure();
int buildcmd();
int launchit();
int shorthelp();
int longhelp();
int d2u(char *s);
int u2d(char *s);

int main(int argc, char **argv)
{
    initrun();
    getparms(argc, argv);
    parseparms();
    configure();
    buildcmd();
    if (!echo)
	launchit();
    exit(0);
}

int d2u(char *s)
{
    int i;
    for (i=0; s && *s && (i<strlen(s)); i++)
	if (s[i] == '\\')
	    s[i] = '/';
}

int u2d(char *s)
{
    int i;
    for (i=0; s && *s && (i<strlen(s)); i++)
	if (s[i] == '/')
	    s[i] = '\\';
}


int getenvstr(char *name, char *value)
{
    char *s;

    s = getenv(name);
    if (s)
	strcpy(value, s);

    return ((s && *s) ? 1 : 0);
}

/*  In Windows, the name/value pair must be separated by = 	*/
/*  with no blanks on either side of =.  Null values would have */
/*  name=\0 to unset them in the environment.			*/
int putenvstr(char *name, char *value)
{
    char s[1000];
    char *p, *q;
    int rc;
    int len;
    int newlen;

    if (!*name)
	return 0;

    for(p = name; *p == ' '; p++);
    for(q = &name[strlen(name)-1]; *q == ' ' && q != p; q--);

    len = (int)(q-p)+1;
    strncpy(s, p, len);
    s[len] = '\0';
    strcat(s, "=");

    /* All env params except path should be Unix style */
#ifdef DXD_WIN
    if (strcasecmp(s, "path="))
	d2u(value);
#endif

    for(p = value; *p == ' '; p++);
    if(strlen(p)) {
	for(q = &value[strlen(value)-1]; *q == ' ' && q != p; q--);
	if (*p != ' ') {
	    newlen = strlen(s);
	    len = (int)(q-p)+1;
	    strncat(s, p, len);
	    s[len+newlen] = '\0';
	}
    }

#ifdef CHECK_ENV
    printf("%s\n", s);
#endif

    p = malloc(strlen(s) + 1);
    strcpy(p, s);
    
    rc = putenv(p);
    if (echo)
	printf("%s\n", s);
    return (!rc ? 1 :0);
}

/*  The following queries the registry for various paths that,	*/
/*  among other things, allow dx and exceed to start without 	*/
/*  either being in the path.  But they must be added to the	*/
/*  beginning of the path in order for them to run, and all	*/
/*  children must convey this down.				*/
int regval(int get, char *name, int co, char *value, int size, int *word)
{
#ifdef DXD_WIN
    char key[500];
    int valtype;
    int sizegot = size;
    HKEY hkey[10];
    long rc;
    int i, k=0;
    DWORD options;

    if (get) {
	options = KEY_QUERY_VALUE;
	strcpy(value, "");
	*word = 0;
    } else {
	options = KEY_SET_VALUE;
    }

    options = KEY_QUERY_VALUE;

    strcpy(key, "SOFTWARE");

    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	options, &hkey[k++]);

    if (co == IBM_ID)
	strcat(key, "\\IBM");
    else
	strcat(key, "\\Hummingbird");
    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	options, &hkey[k++]);
    IfError2("Error opening registry", key, "- Software not present or incorrectly installed");

    if (co == IBM_ID)
	strcat(key, "\\IBM Visualization Data Explorer");
    else
	strcat(key, "\\Exceed");
    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	options, &hkey[k++]);
    IfError2("Error opening registry", key, "- Software not present or incorrectly installed");

    if (!get)
	options = KEY_SET_VALUE;
    strcat(key, "\\CurrentVersion");
    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	options, &hkey[k++]);
    IfError2("Error opening registry", key, "- Software not present or incorrectly installed");

    if (get) {
	rc = RegQueryValueEx(hkey[k-1], (LPTSTR) name, (LPDWORD) 0, 
	    (LPDWORD) &valtype, (LPBYTE) value, &sizegot);
	IfError2("Query value failed on registry value", name, "");

	for (i=k; i > 0; i--) {
	    rc = RegCloseKey(hkey[i-1]);
	    IfError2("CloseKey failed on registry value", name, "");
	}

	switch(valtype) {
	    case REG_DWORD:
		*word = *((int *)value); 
		value = "";
		break;
	    case REG_SZ:
		break;
	    default:
		return 0;
	}
	return 1;
    } else {
	rc = RegSetValueEx((HKEY)hkey[k-1], (LPCSTR)name, (DWORD)0, 
	     (DWORD)REG_SZ, (CONST BYTE *)value, (DWORD)strlen(value)+1);
	IfError("Registration key installation failed");

	for (i=k; i > 0; i--) {
	    rc = RegCloseKey(hkey[i-1]);
	    IfError("CloseKey failed");
	}
	return 1;
    }

error:
    printf("%s: rc = %d\n", errstr, rc);
    return 0;
#endif
}

static int keyformat(char *k)
{
    int i;
    char buf[25];
    char *p;

    for (i=0, p=k; *p && i<20; p++) {
	if (isalpha(*p))
	    buf[i++] = tolower(*p);
	if (isdigit(*p))
	    buf[i++] = *p;
	if (i==5 || i==10 || i==15)
	    buf[i++] = ' ';
    }
    buf[i] = '\0';
    if (strlen(buf) != 20)
	return 0;
    strcpy(k, buf);
    return 1;
}

int initrun()
{
    int keydata;

    strcpy(exhost, thishost);

#if defined(USE_REGISTRY)

    if (!(regval(1, "PathName", HUMMBIRD_ID, exceeddir, sizeof(exceeddir), &keydata) 		&&
	regval(1, "UserDir", HUMMBIRD_ID, exceeduserdir, sizeof(exceeduserdir), &keydata) 	&&
	regval(1, "Description", HUMMBIRD_ID, xservername, sizeof(xservername), &keydata) 	&&
	regval(1, "Version", HUMMBIRD_ID, xserverversion, sizeof(xserverversion), &keydata))) 
	printf("If Exceed is installed on this machine, please make sure it is available\n"
	       "to you as a user.  Otherwise, make sure another X server is installed and running.\n");

    if (!(regval(1, "DXROOT", IBM_ID, dxrootreg, sizeof(dxrootreg), &keydata) 		&&
	regval(1, "InstallDate", IBM_ID, installdate, sizeof(installdate), &keydata) 	&&
	regval(1, "UserName", IBM_ID, username, sizeof(username), &keydata) 		&&
	regval(1, "CompanyName", IBM_ID, userco, sizeof(userco), &keydata) 		&&
	regval(1, "LicenseKey", IBM_ID, licensekey, sizeof(licensekey), &keydata)))
	printf("Data Explorer does not appear to be correctly installed on this machine.\n"
	       "Execution will be attempted anyway, and if it fails, please try reinstalling DX.\n");

#endif (USE_REGISTRY)

    keyformat(licensekey);
    strcpy(exarch, DXD_ARCHNAME);
    strcpy(uiarch, DXD_ARCHNAME);
    putenvstr("ARCH", DXD_ARCHNAME);
    startup = 1;
    getenvstr("DXARGS", dxargs);
    getcwd(curdir, sizeof(curdir));
    getenvstr("DXROOT", dxroot);
    getenvstr("DXDATA", dxdata);
    getenvstr("DXMACROS", dxmacros);
    getenvstr("DXMODULES", dxmodules);
    getenvstr("DXMDF", dxmdf);
    getenvstr("DXINCLUDE", dxinclude);
    getenvstr("DXCOLORS", dxcolors);
    getenvstr("DXEXEC", dxexec);
    getenvstr("DXUI", dxui);
    getenvstr("DISPLAY", display);

    if (!*dxroot)
	strcpy(dxroot, dxrootreg);

    /* fill envargs */

    return 1;
}

#define notset(s) (s && !*s)

#define setifnot(s, v)		\
    if notset(s) {		\
	strcpy(s, v);		\
    }

/*  Unfortunately I messed up and switched v/s and s/v so the	*/
/*  following is confusing, but correct.			*/
#define setenvpair(v, s)	\
    if (s && *s)		\
	putenvstr(s, v);


int configure()
{
    envstr path0;

    setifnot(dxexroot, dxroot);
    sprintf(dxexecdef, "%s\\bin_%s\\dxexec%s", dxexroot, exarch, EXE_EXT);
    setifnot(dxexec, dxexecdef);
    setifnot(exmode, "-r");
    setifnot(exhilite, "-B");

    setifnot(dxuiroot, dxroot);
    if (notset(dxui))
	sprintf(dxui, "%s%sbin_%s%sdxui%s", dxuiroot, DIRSEP, uiarch, DIRSEP, EXE_EXT);
	
    setifnot(uimode, "-edit");
    setifnot(cdto, curdir);



#ifdef DXD_WIN
    getenvstr("Path", path0);
    sprintf(path, "%s\\bin;%s;%s", dxroot, exceeddir, path0);
    sprintf(xnlspath, "%s\\lib", dxroot);
    sprintf(xapplresdir, "%s", exceeduserdir);
    /* sprintf(xapplresdir, "%s\\ui", dxroot); */
    sprintf(xkeysymdb, "%s\\lib\\keysyms.dx", dxroot);
    setenvpair(xnlspath,	"XNLSPATH");
    setenvpair(xapplresdir,	"XAPPLRESDIR");
    //setenvpair(xkeysymdb,	"XKEYSYMDB");  GDA
    setenvpair("",		"HOME");
    setenvpair(path,		"Path");
#endif

    /*  The following logic is specific to the PC, where the	*/
    /*  the sample data and macro paths are automatically set	*/
    /*  if neither is specified.  This allows the samples not	*/
    /*  to have hardcoded paths in the pc environment (they	*/
    /*  are sed'd out).  Unix needs different logic.		*/

    strcpy(path0, dxmacros);
    KILLSEMI(path0);
    d2u(path0);
    sprintf(teststr, "%s/samples/macros", dxroot);
    d2u(teststr);
    if (!*path0 || !strcasecmp(teststr, path0))
	sprintf(dxmacros, "%s/samples/macros", dxroot);
    else
	sprintf(dxmacros, "%s;%s/samples/macros", path0, dxroot);
    setenvpair(dxmacros,	"DXMACROS");

    strcpy(path0, dxdata);
    d2u(path0);
    KILLSEMI(path0);
    sprintf(teststr, "%s/samples/data", dxroot);
    d2u(teststr);
    if (!*path0 || !strcasecmp(teststr, path0))
	sprintf(dxdata, "%s/samples/data;%s", dxroot, dxroot);
    else
	sprintf(dxdata, "%s;%s/samples/data;%s", path0, dxroot, dxroot);
    setenvpair(dxdata,		"DXDATA");

    setenvpair(dxmodules,	"DXMODULES");
    setenvpair(dxinclude,	"DXINCLUDE");
    setenvpair(dxmdf,		"DXMDF");
    setenvpair(dxcolors,	"DXCOLORS");
    setenvpair(dx8bitcmap,	"DX8BITCMAP");

    if (!*display || !strcasecmp(display, "localhost:0") || !strcasecmp(display, "localpc:0"))
	strcpy(display, ":0.0");
    setenvpair(display,		"DISPLAY");
    setenvpair("1", "DXNO_BACKING_STORE");
    setenvpair("1", "DXFLING");

    putenvstr("DXROOT", dxroot);
    if (strcasecmp(dxroot, dxexroot))
	setenvpair(dxexroot, "DXEXECROOT");
    if (strcasecmp(dxroot, dxuiroot))
	setenvpair(dxuiroot, "DXUIROOT");
    if (strcmp(exhost, thishost))
	setenvpair(exhost, "DXHOST");
}

int buildcmd()
{
    envstr tmp;
    int keydata;
    char tmpstr[100];

#ifdef DXD_WIN
    u2d(dxroot);
    u2d(dxexec);
    u2d(dxui);
    u2d(cdto);
    d2u(prompterflags);
    d2u(argstr);
    d2u(uimdf);
    d2u(uiflags);
    d2u(exmdf);
    if (*FileName)
	d2u(FileName);
#endif

    if (uionly && exonly)
	ErrorGoto("-uionly and -execonly are mutually exclusive");

    if (!strcmp(uimode, "-java") && !*FileName) 
	ErrorGoto("-program name required with -java flag");

    if (dxregister) {
	printf("Registered to: %s of %s\n", username, userco);
	printf("Current registration key: %s\n\n", licensekey);
	printf("You may obtain a registration key by e-mailing your name,\n");
	printf("your company name, the operating system (NT or 95), and\n");
	printf("the type of registration (trial, beta, node-locked, floating)\n");
	printf("to dxsupp@watson.ibm.com, or by calling 914-784-6694\n\n");
	printf("Enter new registration key or <rtn> to cancel:\n");
	fgets(tmpstr, sizeof(tmpstr), stdin);
	if (!*tmpstr) {
	    printf("Registration left unchanged\n");
	    exit(0);
	}
	keyformat(tmpstr);
	if (strlen(tmpstr) != 20) {
	    printf("Improper registration key ... aborting\n");
	    exit(0);
	}
	regval(0, "LicenseKey", IBM_ID, tmpstr, strlen(tmpstr), &keydata);
	regval(1, "LicenseKey", IBM_ID, tmpstr, sizeof(tmpstr), &keydata);
	printf("Registration key changed to: %s\n", tmpstr);
	exit(0);
    }

    if (showversion) {
#ifdef DXD_WIN
	printf("Open Visualization Data Explorer: Registered to %s of %s\n", username, userco);
	if (*xservername) {
	    printf("X server found: %s\n", xservername);
	    printf("X server version: %s\n", xserverversion);
	}
#endif
	printf("Open Visualization Data Explorer Script, version %s (%s, %s)\n", SCRIPTVERSION, __TIME__, __DATE__);
	sprintf(cmd, "%s -v", dxexec);
	launchit();
	sprintf(cmd, "%s -version", dxui);
	launchit();
	exit(0);
    }

    if (tutor) {
	sprintf(cmd, "%s%sbin_%s%stutor%s", dxroot, DIRSEP, uiarch, DIRSEP, EXE_EXT);

    } else if (prompter) {
	if (*FileName) {
	    strcat(prompterflags, " -file ");
	    strcat(prompterflags, FileName);
	}
	sprintf(cmd, "%s%sbin_%s%sprompter%s %s", dxroot, DIRSEP, uiarch, DIRSEP, EXE_EXT, prompterflags);

    } else if (startup) {
	sprintf(cmd, "%s%sbin_%s%sstartupui%s %s", dxroot, DIRSEP, uiarch, DIRSEP, EXE_EXT, argstr);

    } else if (builder) {
	sprintf(cmd, "%s%sbin_%s%sbuilder%s %s", dxroot, DIRSEP, uiarch, DIRSEP, EXE_EXT, FileName);
	/* sprintf(cmd, "%s%sbin_%s%sbuilder -xrm %s %s", dxroot, DIRSEP, uiarch, DIRSEP, motifbind, FileName); */

    } else if (exonly) {
	printf("Starting DX executive\n");
	sprintf(exflags, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s",
	    exmode, excache, exlog, exread, exmem, exproc,
	    exerrlvl, extrace, exhilite, extime, exdist,
	    exoutdb, exlic, exmdf);
	sprintf(cmd, "%s %s ", dxexec, exflags);
	if (*FileName) {
#ifdef DXD_WIN
	    u2d(FileName);
#endif
	}

    } else {
	printf("Starting DX user interface\n");
	sprintf(tmp, " %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", 
	uimode, uidepth, uidebug, uimem, uiproc, uilog, uicache,
	uiread, uitrace, uitime, uioutdb, uihilite, uimdf, xparms,
	uirestrict);
	strcat(uiflags, tmp);
	if (portset) {
	    strcat(uiflags, " -port ");
	    strcat(uiflags, port);
	}
	if (*FileName) {
	    strcat(uiflags, " -program ");
	    strcat(uiflags, FileName);
	}
	if (uionly)
	    strcat(uiflags, " -uionly");
	if (wizard)
	    strcat(uiflags, " -wizard");
#ifndef DXD_WIN 
	if (*cdto) {
	    strcat(uiflags, " -directory ");
	    strcat(uiflags, cdto);
	}
#endif
	if (strcmp(dxexec, dxexecdef)) {
	    strcat(uiflags, " -exec ");
	    strcat(uiflags, dxexec);
	}

	sprintf(cmd, "%s %s", dxui, uiflags);
	/* sprintf(cmd, "%s %s -xrm %s", dxui, uiflags, motifbind); */

    }

    if (seecomline || echo)
	printf("%s\n", cmd);

    return 1;

error:
    printf("%s\n", errstr);
    return 1;
}

int launchit()
{
#define BUFFSIZE 2048
    int rc;
    char *args[100];
    char *s;
    int i;
    FILE *f, *p;

    char buf[BUFFSIZE];

    u2d(cdto);
    chdir(cdto);
    if (exonly && *FileName) {
	f = fopen(FileName, "r");
	if (!f)
	    ErrorGoto2("File", FileName, "not found");
	p = popen(cmd, "wt");
	if (!p)
	    ErrorGoto2("Error spawning exec using", cmd, "");
	while (fgets(buf, BUFFSIZE, f))
	    fputs(buf, p);
	pclose(p);
	fclose(f);
    }
    else
    {
	for (i=0, s=cmd; *s; s++) {
	    for ( ; *s && *s == ' '; s++)
		;
	    if (!*s)
		break;
	    for (args[i++]=s; *s && (*s != ' '); s++)
		;
	    if (!*s)
		break;
	    *s = '\0';
	}
	args[i] = NULL;

#if defined(HAVE_SPAWNVP)
	if (strcmp(exmode, "-r") || showversion)
	    rc = spawnvp(_P_WAIT, cmd, &args[0]);
	else
	    rc = spawnvp(_P_OVERLAY, cmd, &args[0]);
	if (rc < 0)
	{
	    rc = errno;
	    perror("error");
	}
#else
	rc = execvp(args[0], args);
#endif
    }
    return 1;
error:
    printf("%s\n", errstr);
    return 0;
}

int getparms(int argc, char **argv)
{
    int i;
    int n = 0;
    int readpipe = 0;
    char c;
    int bytesread, bytesavail;

    /* fill parms array, first with DXARGS values	*/
    /* then with command line options			*/
    /* then with pipe args				*/
    /* so they will have priority given to last ones in	*/

    /* -pipeargs is necessary evil since I couldn't get	*/
    /* Windows to do a non-blocking peek at stdin to	*/
    /* see if anything is there.  -pipeargs makes it	*/
    /* explicit, anyway.				*/

    fillparms(dxargs, &n);

    for (i=1; i<argc; i++) {
	strcpy(parm[n], argv[i]);
	if (!strcmp(parm[n], "-pipeargs"))
	    readpipe = 1;
	else
	{
	    strcat(argstr, parm[n]);
	    strcat(argstr, " ");
	    n++;
	}
    }

    if (readpipe) {
	for (i=0; (EOF != (c=getchar())); i++)
	    pipestr[i] = c;
	pipestr[i] = '\0';
	fillparms(pipestr, &n);
    }

    numparms = n;

    return 1;
}

/*  This fills the parm array with tokens that have their	*/
/*  leading and trailing blanks removed.  In Windows, filepaths	*/
/*  may contain spaces if they were passed in as quoted strings	*/
/*  and the shell may have removed the quotes, leaving interior	*/
/*  blanks.							*/
int fillparms(char *s, int *n)
{
    int i;
    char *p, *q, *dest;

    for (p = s; *p; p++) 
	if (*p == '\t' || *p == '\n' || *p == '\f')
		*p = ' ';

    for (p = s; *p; p = q) {			/* start next */
	dest = parm[*n];
	for ( ; *p == ' '; p++)			/* skip to nonblank */
	    ;
	for (q = p; *q && *q != ' '; q++)	/* find token end */
	    ;
	if (p == q)				/* no more tokens */
	    return 1;
	strncpy(dest, p, (int)(q-p));		/* load it */
	dest[(int)(q-p)] = '\0';
	(*n)++;
    }

    return 1;
}


/*  Below is a slew of macros.  Note that some would be very	*/
/*  unhappy if a c-style semicolon were used after them, while	*/
/*  others wouldn't mind.					*/

/*  Note also that  a few automatically advance the pointer, 	*/
/*  while others do not.					*/

/*  The leading - is implicit in the conditionals, but must be	*/
/*  explicit in the startswith() query.				*/

#define advance 		\
    p++;			\
    s = parm[p];

#define is(str)			\
    if (!strcmp(s, "-" #str)) {

#define startswith(str)		\
    if (!strncmp(s, #str, strlen(#str))) {

#define isregexpr		\
    (s[strlen(s)-1] == '*')

#define isor(str)		\
    if (!strcmp(s, "-" #str) ||

#define or(str)			\
    !strcmp(s, "-" #str) ||

#define rosi(str)		\
    !strcmp(s, "-" #str)) {

#define next			\
    } else

#define islast			\
    (p >= numparms)

#define last(str)		\
    if islast {			\
	strcpy(errmsg, str);	\
	goto error;		\
    }				\
    advance;

#define lastoff(str)		\
    last("-" #str ": missing parameter, must be on or off");

#define check(str)					\
    if ((p >= numparms-1) || (*parm[p+1] == '-')) {	\
	strcpy(errmsg, str);				\
	goto error;					\
    }							\
    advance;

#define set(val)		\
    strcpy(val, s);

#define add(val)		\
    strcat(val, " ");		\
    strcat(val, s);

#define add2(val1, val2)	\
    add(val1)			\
    add(val2)

#define argadd(what, val)		\
    is(what)				\
	strcat(val, " -" #what);	\
    next

#define eq(val)			\
    if (!strcmp(s, #val)) {

#define eqon			\
    if (!strcmp(s, "on")) {

#define eqoff			\
    if (!strcmp(s, "off")) {

#define neither(str)		\
    } else {			\
	strcpy(errmsg, str);	\
	goto error;		\
    }

#define neitheroff(str)		\
    neither("-" #str ": bad parameter, must be on or off")

#define nextisswitch		\
    (*parm[p+1] == '-')

#define skipwarn(val)							\
    is(val)								\
	strcpy(msgstr, "ignoring option -" #val  " and its value, ");	\
	advance;							\
	strcat(msgstr, s);						\
	printf("%s\n", msgstr);						\
    next

#define skipwarn0(val)					\
    is(val)						\
	strcpy(msgstr, "ignoring option -" #val);	\
	printf("%s\n", msgstr); 			\
    next

#define skip0(val)					\
    is(val)						\
    next

#define skipnowarn(val)							\
    is(val)								\
	advance;							\
    next

/*  Here's the script, which amounts to a long chain of if-else's	*/
int parseparms()
{
    char *s;

    for (p=0; p<numparms; ) {

	s = parm[p];

	is(host)
	    check("-host: missing host name");
	    set(exhost);
	next

	is(local)
	    strcpy(exhost, thishost);
	next

	skip0(queue)

	skipwarn(connect)

	is(directory)
	    check("-directory: missing directory name");
	    set(cdto);
	next

	is(memory)
	    check("-memory: missing parameter, must give number of Megabytes");
	    strcpy(exmem, " -M");
	    strcat(exmem, s);
	    strcpy(uimem, "-memory");
	    add(uimem);
	next

	is(processors)
	    check("-processors: missong parameter, must give number of processors");
	    strcpy(exprocs, " -p");
	    add(exprocs);
	next

	/*  -port is handled slightly differently from on Unix		*/
	/*  The Unix script doesn't handle it explicitly, but the ui	*/
	/*  understands it.  I couldn't find an equivalent because	*/
	/*  -uionly prevented the ui from trying to connect, while	*/
	/*  !-uionly forced the ui to spawn the server, which has been	*/
	/*  started manually.						*/
	is(port)
	    check("-port: missing port number");
	    portset = 1;
	    set(port);
	next

	isor(image) or(edit) or(java) rosi(kiosk)
	    strcpy(uimode, s);
	    exonly = 0;
	    strcpy(exmode, "-r");
	    startup = 0;
	next

	is(wizard)
	    wizard = 1;
	next

	is(menubar)
	    strcpy(uimode, "-kiosk");
	    exonly = 0;
	    strcpy(exmode, "-r");
	    startup = 0;
	next

	argadd(execute, uiflags)

	argadd(execute_on_change, uiflags)

	argadd(suppress, uiflags)

	is(xrm)
	    check("-xrm: missing resource value");
	    strcpy(xparms, "-xrm");
	    add(xparms);
	next

	argadd(synchronous, uiflags)

	is(display)
	    check("-display: missing X name");
	    set(display);
	next

	is(log)
	    lastoff(log);
	    eqon
		strcpy(exlog, "-l");
		strcpy(uilog, "-log on");
	    next eqoff
		strcpy(exlog, "");
		strcpy(uilog, "-log off");
	    neitheroff(log);
	next

	is(cache)
	    lastoff(cache);
	    eqon
		strcpy(excache, "");
		strcpy(uicache, "-cache on");
	    next eqoff
		strcpy(excache, "-c");
		strcpy(uicache, "-cache off");
	    neitheroff(cache);
	next

	is(trace)
	    lastoff(trace);
	    eqon
		strcpy(extrace, "-T");
		strcpy(uitrace, "-trace on");
	    next eqoff
		strcpy(extrace, "");
		strcpy(uitrace, "-trace off");
	    neitheroff(trace);
	next

	is(readahead)
	    lastoff(readahead);
	    eqon
		strcpy(exread, "");
		strcpy(uiread, "-readahead on");
	    next eqoff
		strcpy(exread, "-u");
		strcpy(uiread, "-readahead off");
	    neitheroff(readahead);
	next

	is(timing)
	    lastoff(timing)
	    eqon
		strcpy(extime, "-m");
		strcpy(uitime, "-timing on");
	    next eqoff
		strcpy(extime, "");
		strcpy(uitime, "-timing off");
	    neitheroff(timing);
	next

	is(highlight)
	    lastoff(highlight)
	    eqon
		strcpy(exhilite, "-B");
		strcpy(uihilite, "-highlight on");
	    next eqoff
		strcpy(exhilite, "");
		strcpy(uihilite, "-highlight off");
	    neitheroff(highlight);
	next

#ifdef DXD_WIN 
	is(license)
	    check("-license: missing parameter");
	    eq(runtime)
		strcpy(exlic, "-Lruntime");
		strcat(uiflags, " -forceLicense runtime");
#if 0
	    next eq(develop)
		strcpy(exlic, "-Ldevelop");
		strcat(uiflags, " -forceLicense develop");
	    next eq(timed)
		strcat(uiflags, " -forceLicense timed");
#endif
	    next
		{
		    sprintf(errmsg, "-license: parameter \'%s\' not recognized", s);
		    /* goto error; */
		}
	next
#endif

#ifdef DXD_WIN
	skipnowarn(processors)
#else
	/* Need Unix handling here */
#endif

	is(optimize)
	    check("-optimize: missing parameter");
	    eq(memory)
		putenvstr("DXPIXELTYPE", "DXByte");
		putenvstr("DXDELAYEDCOLORS", "1");
	    next eq(precision)
		putenvstr("DXPIXELTYPE", "DXFloat");
		putenvstr("DXDELAYEDCOLORS", "");
	    next
		{
		    sprintf(errmsg, "-optimize: parameter \'%s\' not recognized", s);
		    goto error;
		}
	next

	is(script)
	    exonly = 1;
	    strcpy(exmode, "-R");
	    startup = 0;
	    if (islast)
		goto done;
	    if (!nextisswitch) {
		advance;
		set(FileName);
	    }
	next

	is(program)
	    check("-program: missing program name");
	    set(FileName);
	next

	is(cfg)
	    check("-cfg: missing configuration file");
	    strcat(uiflags, "-cfg");
	    add(uiflags);
	next

	is(uionly)
	    uionly = 1;
	    startup = 0;
	next

	isor(exonly) rosi(execonly)
	    exonly = 1;
	    startup = 0;
	next

	is(dxroot)
	    check("-dxroot: missing directory name");
	    set(dxroot);
	next

	isor(execroot) rosi(exroot)
	    check("-execroot: missing directory name");
	    set(dxexroot);
	next

	is(uiroot)
	    check("-uiroot: missing directory name");
	    set(dxuiroot);
	next

	is(exec)
	    check("-exec: missing filename");
	    set(dxexec);
	next

	is(mdf)
	    check("-mdf: missing filename");
	    set(dxmdf);
	    strcat(exmdf, " -F");
	    add(exmdf);
	    strcat(uimdf, " -mdf");
	    add(uimdf);
	next

	is(dxmdf)
	    add(uimdf);
	    check("-dxmdf: missing filename");
	    add(uimdf);
	next

	is(uimdf)
	    check("-uimdf: missing filename");
	    strcat(uimdf, " -uimdf");
	    add(uimdf);
	next

	is(ui)
	    check("-ui: missing filename");
	    set(dxui);
	next

	is(data)
	    check("-data: missing directory list");
	    set(dxdata);
	next

	is(macros)
	    check("-macros: missing directory list");
	    set(dxmacros);
	next

	is(modules)
	    check("-modules: missing directory list");
	    set(dxmodules);
	next

	is(include)
	    check("-include: missing directory list");
	    set(dxinclude);
	next

	is(colors)
	    check("-colors: missing file name");
	    set(dxcolors);
	next

	is(8bitcmap)
	    set(dx8bitcmap);
	    if (!strcmp(dx8bitcmap, "private"))
		strcpy(dx8bitcmap, "-1.0");
	    else if (!strcmp(dx8bitcmap, "shared"))
		strcpy(dx8bitcmap, "1.0");
	next

#if 0
	skipwarn(hwrender)
#endif
	is(hwrender)
	    check("-hwrender: missing parameter, must be gl or opengl");
	    eq(opengl)
		putenvstr("DXHWMOD", "DXHwddOGL.o");
	    next eq(gl)
		putenvstr("DXHWMOD", "DXHwdd.o");
	    next
		{
		    sprintf(errmsg, "-hwrender: parameter \'%s\' not recognized", s);
		    goto error;
		}
	next

	is(verbose)
	    seecomline = 1;
	next

	is(uidebug)
	    set(uidebug);
	next

#ifdef DXD_WIN
	skipwarn0(outboarddebug)
#else
	/* do Unix stuff */
#endif

	is(echo)
	    echo = 1;
	next

#ifdef DXD_WIN
	skipwarn0(remoteecho)
#else
	/* do Unix stuff */
#endif

	isor(help) or(shorthelp) rosi(h)
	    shorthelp();
	next

	isor(morehelp) rosi(longhelp)
	    longhelp();
	next

	is(version)
	    showversion = 1;
	next

	is(prompter)
	    prompter = 1;
	next

	is(startup)
	    startup = 1;
	next

	isor(tutor) rosi(tutorial)
	    tutor = 1;
	    startup = 0;
	next

	is(builder)
	    builder = 1;
	    startup = 0;
	next

	startswith(-no)
	    add(uirestrict);
	next

	argadd(limitImageOpions, uirestrict)

	argadd(metric, uiflags)

	is(restrictionLevel)
	    add(uirestrict);
	    check("-restrictionLevel: missing level");
	    add(uirestrict);
	next

	is(appHost)
	    add(uiflags);
	    check("-appHost: missing host");
	    add(uiflags);
	next

	is(appPort)
	    add(uiflags);
	    check("-appPort: missing port");
	    add(uiflags);
	next

	is(file)
	    check("-file: missing input filename");
	    set(FileName);
	next

	is(full)
	    add(prompterflags);
	next

	is(view)
	    add(uiflags);
	    check("-view: missing input filename");
	    add(uiflags);
	next

#ifdef DXD_WIN
	startswith(&)
	    sprintf(msgstr, "ignoring option: %s --- & used only on Unix systems\n", s);
	    printf(msgstr);
	next

	is(register)
	    dxregister=1;
	next
#endif

	startswith(-)
	    strcpy(errmsg, "Unrecognized parameter: ");
	    strcat(errmsg, s);
	    goto error;
	next

	{
	    if (*FileName) {
		sprintf(errmsg, "input filename already set to \'%s\'; \'%s\' unrecognized", FileName, s);
		goto error;
	    }
	    set(FileName);
	}
	advance;
    }

done:
    return 1;

error:
    printf("%s\n", errmsg);
    exit(1);
}


int shorthelp()
{
    printf(


"command line parameters:\n"
" -program filename    start UI with this network\n"
" -image               start DX with an image window as the anchor window \n"
" -edit                start DX with an editor window as the anchor window \n"
" -menubar             start DX with a small menubar as the anchor window \n"
" -startup             start DX with an initial startup panel (default) \n"
"\n"
" -uionly              start the UI only (no exec)\n"
" -script filename     start the exec only, in script mode, running this script\n"
" -script              start the exec only, in script mode\n"
"\n"
" -host hostname       start executive on this machine\n"
" -memory #Mbytes      set the amount of memory the exec uses\n"
"\n"
" -macros pathlist     directory list to search for UI macros\n"
" -data pathlist       directory list to search for data files\n"
"\n"
" -prompter            start the DX Data Prompter\n"
" -builder             start the DX Module Builder\n"
" -tutor               start the DX Tutorial\n"
" -register            register your copy of DX\n"
"\n"
" -morehelp            print longer help with information about other options\n"
 

    );

    exit(0);
}

int longhelp()
{
    printf(


"command line parameters:\n"
" -host hostname       start executive on this machine               \n"
" -local               start executive on the current machine (default)\n"
"\n"
" -program filename    start UI with this network\n"
" -script filename     run exec only, in script mode, with this script\n"
" -script              run exec only, in script mode\n"
"\n"
" -image               start DX with an image window as the anchor window \n"
" -edit                start DX with the VP Editor as the anchor \n"
" -menubar             start DX with a small menubar as the anchor window \n"
" -startup             start DX with an initial dialog (default) \n"
"\n"
" -uionly              start the UI only (no exec)\n"
" -execonly            start the exec only (no UI) in remote mode\n"
" -connect host:port   start a distributed exec only (no UI)\n"
"\n"
" -prompter            start the DX Data Prompter\n"
" -full                start the Full Data Prompter\n"
" -file filename       start the Data Prompter with this header file\n"
"\n"
" -builder             start the DX Module Builder\n"
" -tutor               start the DX Tutorial\n"
"\n"
" -suppress            do not open control panels at startup in image mode\n"
" -execute             execute the program automatically at startup\n"
" -execute_on_change   go into execute_on_change mode at startup\n"
"\n"
" -optimize [memory|precision]\n"
"                      select whether to minimize memory usage or to produce \n"
"                      more color-accurate images.  When memory is optimized, \n"
"                      image objects are generated with 24 bits/pixel instead \n"
"                      of 96, and ReadImage will produce delayed color images \n"
"                      if supported by the format. (default = precision)\n"
"\n"
" -memory #Mbytes      set the amount of memory the exec uses\n"
" -processors #proc    set the number of processors the exec uses \n"
"                      (SMP versions only)\n"
" -log [on|off]        executive and ui logging: (default = off)\n"
" -cache [on|off]      executive cache: (default = on)\n"
" -trace [on|off]      executive trace: (default = off)\n"
" -readahead [on|off]  executive readahead: (default = on)\n"
" -timing [on|off]     module timing: (default = off)\n"
" -highlight [on|off]  node execution highlighting: (default = on)\n"
" -directory dirname   cd to this directory before starting exec\n"
" -display hostname:0  set X display destination\n"
" -metric              have the UI use metric units when possible\n"
"\n"
" -exec filename       execute this user executive\n"
" -mdf filename        use this user .mdf file\n"
"\n"
" -key <64bit hex>     16 character hexidecimal (64 bit) number that is used\n"
"		      to encode and decode .net files.\n"
" -encode              Encode a .net file into a binary format with a key \n"
"                      that must be specified with the -key option.   \n"
"                      For example, \n"
"                        dx -encode -key 193495946952abed foo.net \n"
"                      The resulting file can only be decoded by the DX\n"
"                      user interface when using the same -key option.\n"
"                      For example, \n"
"                        dx -key 193495946952abed bar.net \n"
"\n"
" -dxroot dirname      dx root directory; defaults to /usr/lpp/dx\n"
"\n"
" -macros pathlist     directory list to search for UI macros\n"
" -data pathlist       directory list to search for data files\n"
" -include pathlist    directory list to search for script files\n"
" -modules pathlist    directory list to search for outboard modules\n"
"\n"
" -colors filename     replace default color names/RGB values file\n"
" -8bitcmap [private|shared|0-1|-1]\n"
"                      private/shared colormap error threshold (default=0.1)\n"
"                      -1 is equivalent to private.\n"
" -hwrender [gl|opengl]  \n"
"                      override default hardware rendering library on platforms\n"
"                      where both are supported.  (default = opengl).\n"
"\n"
" -license <type>      force a specific license for either the UI or executive.\n"
"                      type should be one of:\n"
"    runtime           force a run-time license (UI or executive)\n"
"    timed             force a timed (limited function) license (UI only)\n"
"    develop           force a developer license (UI or executive) (default)\n"
"\n"
" -verbose             echo command lines before executing\n"
" -echo                echo the command lines without executing them\n"
" -outboarddebug       let user start outboard modules by hand\n"
" -version             show version numbers of dxexec, dxui, dx.exe, and X server\n"
" -synchronous         force synchronization of X events between dx and the x server\n"
"\n"
" -help                print a short help message\n"
" -morehelp            print this help message\n"
"\n"
"environment variables:\n"
" DXHOST               sets hostname for -host\n"
"\n"
" DXPROCESSORS         sets number of processors for multiprocessor DX\n"
" DXMEMORY             sets memory limit in megabytes\n"
" DXAXESMAXWIDTH       sets the maximum number of digits in axes tick labels\n"
"                      before a switch to scientific notation is made\n"
" DXDEFAULTIMAGEFORMAT Sets the image type to either 24-bit color or floating\n"
"                      point color (96-bit) images depending on the value\n"
"                      DXByte (24-bit) or DXFloat (96-bit)\n"
" DXDELAYEDCOLORS      If set to anything other than 0, enables ReadImage to\n"
"                      created delayed color images if the image is stored in\n"
"                      a tiff byte-with-colormap format or a gif image\n"
" DX_NESTED_LOOPS      For faces, loops, and edges data, if set, allows loops\n"
"                      other than the enclosing loop for a face to be listed\n"
"                      first, with a consequent decrease in performance\n"
" DXPIXELTYPE          Sets the image type to either 24-bit color or floating\n"
"                      point (96-bit) color.  This affects the behavior of\n"
"                      Render and ReadImage.  This can be set to either DXByte\n"
"                      or DXFloat (default).\n"
" DX_USER_INTERACTOR_FILE Specifies a file containing user interactors for use by\n"
"                      the SuperviseState and SuperviseWindow modules\n"
"\n"
" DXEXEC               sets filename for -exec\n"
" DXMDF                sets filename for -mdf\n"
"\n"
" DXMACROS             sets pathlist for -macros\n"
" DXDATA               sets pathlist for -data\n"
" DXINCLUDE            sets pathlist for -include\n"
" DXMODULES            sets pathlist for -modules\n"
"\n"
" DXCOLORS             sets filename for -colors\n"
" DX8BITCMAP           sets threshold for -8bitcmap\n"
"\n"
" DXGAMMA              sets gamma correction for displayed images. Default is 2.\n"
" DXGAMMA_8BIT\n"
" DXGAMMA_12BIT\n"
" DXGAMMA_24BIT        sets the gamma correction factor for the windows with \n"
"                      the indicated window depth.  Overrides the value set \n"
"                      by DXGAMMA.\n"
"\n"
" DXHWMOD              specifies the name of the hardware rendering library \n"
"                      to use when more than one is supported. Should be\n"
"                      either DXhwdd.o or DXhwddOGL.o\n"
"\n"
" DXTRIALKEY           specifies the trial license key, and overrides the\n"
"                      trial license file.\n"
" DXTRIALKEYFILE       specifies the name of the expiration file containing\n"
"                      the trial license key. \n"
"                      (default = $DXROOT/expiration)\n"
"\n"
" DXROOT               sets directory for -dxroot\n"
"\n"
" DXARGS               prepends these args to the command line\n"
"\n"
"command line parameters override environment variables.\n"
"If conflicting parameters are given, the last one has precedence.\n"
"Also, there are some other less frequently used command line options\n"
"that are not documented here.  See the User's Guide for a complete\n"
"list of options.\n"
"\n"


    );

    exit(0);
}
