/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#include <dxconfig.h>


/* this has to be before the ifdef, because it defines DXD_LICENSED_VERSION 
 * if this arch supports the license manager.
 */
#include <dx/dx.h>

#if 0
/* DO NOT remove the #if 0 above unless you want the time bomb to take
 * effect, in which case the executable will only work for 60 days.
 */
#define DXD_BETA_VERSION
#endif

#ifdef DXD_LICENSED_VERSION
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DXD_STLIB_INCLUDES
#endif

#ifdef DXD_BETA_VERSION
#ifndef DXD_STLIB_INCLUDES 
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#ifdef DXD_WIN
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#endif

#ifdef DXD_LICENSED_VERSION
#include "license.h"

#define NL_LIC  1
#define CON_LIC 2

static int shadow_fd_dxlic = -1;
static int shadow_fd_mplic = -1;
static int trial_file_exists  = FALSE; 
static int MPlic_tried	   = FALSE;
struct lic_info {
    int child;
    int type;
};
struct lic_info dxlic = {-1, -1};
struct lic_info mplic = {-1, -1};

extern char *crypt(char *key, char *salt);

static Error system_hostname(char *buf);
static Error checkexp(char *root, lictype ltype);
static char messagebuf[1024];

extern int _dxd_ExHasLicense;
extern int _dxd_exRemote;
extern int *_dxd_exTerminating;
extern char *_dxd_exHostName;
extern int _dxd_exRemoteSlave;

int _dxfCheckLicenseChild(int child)
{
    if ( child == dxlic.child) {
      if(dxlic.type == NL_LIC)
          return(0);
      return(child);
    }
    else if ( child == mplic.child) {
      if(mplic.type == NL_LIC)
          return(0);
      return(child);
    }
    else
        return(-1);
}

Error ExLicenseDied(int fd, Pointer junk)
{
    /* We should only be called if dxshadow dies,  */
    /* then send UNAUTHORIZED MESSAGE to UI        */
    /* or die if were in script mode 		 */
    

    DXRegisterInputHandler(NULL, fd, NULL);

    if ( fd == shadow_fd_dxlic)
      DXMessage("License Error: Exec lost DX license and is terminating\n");
    else if ( fd == shadow_fd_mplic)
      DXMessage("License Error: Exec lost MP license and is terminating\n");
    else
      DXMessage("License Error: unknown license error\n");

    _dxd_ExHasLicense = FALSE;
    if (_dxd_exRemote) {
	DXUIMessage("LICENSE","UNAUTHORIZED");
	return OK;
    }
    
    if(_dxd_exTerminating) {
        *_dxd_exTerminating = TRUE;
        return (-1);
    }
    /* when _dxd_exTerminating is NULL we are being called from the */
    /* developer's kit, just exit */
    exit(-1);
    
    /* NOTREACHED */
}

void _dxf_ExReleaseLicense()
{
    if(shadow_fd_dxlic >= 0)
        close(shadow_fd_dxlic);
    if(shadow_fd_mplic >= 0)
        close(shadow_fd_mplic);
}


Error ExGetLicense(lictype ltype, int forceNetLS)
{
    int i;
    int child;
    int pid;
    int in[2],out[2];
    char remname[256];
    char auth_msg[AUTH_MSG_LEN];
    char ckey[9];
    char c_buf[32],p_buf[32];	/* hold crypted msgs for comaparison */
    static char envbuf[32];	/* static 'cause it goes into the env */
    char salt[3];
    time_t timenow;
   
 
    char *root = getenv ("DXEXECROOT");
    if (root == NULL) 
	root = getenv ("DXROOT");
    if (root == NULL)
	root = "/usr/lpp/dx";

    if (ltype == MPLIC) {
	MPlic_tried = TRUE;
	forceNetLS = FALSE;
    }
    

    strcpy(messagebuf,"");

    if (checkexp (root, ltype))    /* check for an old syle trial license */
	return OK;
    else if ( ltype == MPLIC && trial_file_exists )  /* don't try to get an MP floating lic if DX lic */ 
	return ERROR;				/* is a uniprocessor nodelocked */  
	
    /* didn't find a trial license so spawn the NetLS licensing process */
    
    /* Set up two pipes */
    if (pipe(in) < 0) {
	perror("pipe(in)");
	exit (-1);
    }
    if (pipe(out) < 0) {
	perror("pipe(out)");
	exit (-1);
    }
    
    timenow = time(NULL);
    
    sprintf(envbuf,"_DX_%d=", getpid());
    sprintf(c_buf,"%x", timenow);
    strcat(envbuf, c_buf+4);
    putenv(envbuf);
   
#if DXD_HAS_VFORK
    /* if it's available, use vfork() so we don't copy the entire data
     * segment when forking - we are going to exec right away
     * anyway so we aren't going to use anything from the data seg.
     */
    pid = vfork();
#else
    pid = fork();
#endif
    child = 0xFFFF & pid;       /* force "child id" to be < 4 hex chars */
	
    if (pid == 0) {	/* Child */
	char arg1[32], arg3[32];
		
	if (in[1])
	    close (in[1]);
	if (out[0])
	    close (out[0]);
	if (dup2(in[0], 0) < 0) {
	    perror("dup2");
	    exit (-1);
	}
	if (dup2(out[1], 1) < 0) {
	    perror("dup2");
	    exit (-1);
	}
	
	/* should we close other file descriptors here ? */
	
	if (getenv("DXSHADOW")) 
	    strcpy(remname,getenv("DXSHADOW"));
	else 
	    sprintf(remname,"%s/bin_%s/dxshadow",root,DXD_ARCHNAME);

	switch (ltype) {
	    case MPLIC:	strcpy(arg1,"-mp");	break;
	    case DXLIC:	strcpy(arg1,"-dev");	break;
	    case RTLIC:	strcpy(arg1,"-rt");	break;
	    case RTLIBLIC:	strcpy(arg1,"-rtlib");	break;
	    default:    sprintf(arg1,"%d",ltype); break;
	}
	if (forceNetLS)
	    strcat(arg1,"only");

	sprintf(arg3,"%d.%d.%d", DXD_VERSION, DXD_RELEASE, DXD_MODIFICATION);
	execlp(remname, "dxshadow", arg1 , "-version", arg3 ,NULL);

	perror("Could not execute license process");
	exit (-1);
    }
    else if (pid > 0) {   /* parent */
 	int netls_type;
	const char *lic_name;
	if (in[0]) 
	    close (in[0]);
	if (out[1]) 
	    close (out[1]);

	/* wait for response from the child */
	i = read (out[0], auth_msg, AUTH_MSG_LEN);
	if (i != AUTH_MSG_LEN) {
	    perror ("License Error:Bad message read from dxshadow");
	    exit (-1);
	}
	
        if (ltype == MPLIC) 
            mplic.child = child;
        else
            dxlic.child = child;

	/* decipher license message here */
	
	child = (child < 4096) ? (child+4096)
	                       : (child);       /* forces to be 4 0x chars */
	
	strcpy(ckey, c_buf+4);
	sprintf(ckey+4, "%x", child);
	
	salt[0] = '7';
	salt[1] = 'q';
	salt[2] = '\0';
	
	strcpy(p_buf, crypt(ckey, salt));;
	
	for(i=0;i<13;i++)
	    c_buf[i] = auth_msg[(i*29)+5];
	c_buf[13] = '\0';
	
	if (strcmp(c_buf, p_buf)) {
	    /* Bad message from child */
	    perror("License Error: invalid message from license process.");
	    exit (-1);
	}

	/* valid message so we extract license type */
	for(i=0; i<8; i++)
	    c_buf[i] = auth_msg[(i*3)+37];
	
	c_buf[8] = '\0';
	sscanf(c_buf, "%x", &i);
	netls_type = 0xffff & (i^child);
	i = i >> 16;
	ltype = 0xffff & (i^child);
#if LIC_DEBUG 
	fprintf(stderr,"Received...\n"
		"c_buf = '%s', ltype = 0x%x, netls_type = 0x%x, mask = 0x%x\n",
				c_buf,ltype,netls_type,child);
#endif

   	switch (ltype) {
	    case DXLIC: lic_name = "DX development"; break;
	    case RTLIC: lic_name = "DX run-time"; break;
	    case MPLIC: lic_name = "MP"; break;
	    case RTLIBLIC: lic_name = "DX Library run-time"; break;
	    default: return FALSE; break;	/* bad license */ 
  	}

	switch (netls_type) {
	    
	  case GOT_NODELOCKED:
	   
	    if (ltype == MPLIC) {
		sprintf(messagebuf,"Exec got nodelocked %s license.",lic_name);
                mplic.type = NL_LIC;
	    } else {
		DXMessage("Exec got nodelocked %s license.", lic_name);
                dxlic.type = NL_LIC;
		_dxd_ExHasLicense = TRUE;
	    }
	    return OK;
		
	  case GOT_CONCURRENT:
	    /* do concurrent stuff here */
        
	    if (ltype == MPLIC) {
	        shadow_fd_mplic = out[0];
		sprintf(messagebuf,"Exec got concurrent use %s license.",
							lic_name);	
		/* we save message and will register input handler 
		 * in ExLicenseFinish 
		 * after it's safe to call DX routines 
		 */
                mplic.type = CON_LIC;
	    } else {
		DXMessage("Exec got concurrent use %s license.",lic_name);
	        shadow_fd_dxlic = out[0];
		DXRegisterInputHandler(ExLicenseDied,shadow_fd_dxlic,NULL);
                dxlic.type = CON_LIC;
		_dxd_ExHasLicense = TRUE;
   	    }

	    return OK;
	    
	  case GOT_NONE:
	    
	    if (ltype == MPLIC)
	      sprintf(messagebuf,"Exec could not get a %s license,"
				" running in uniprocessor mode.",lic_name);
            else 
	      DXMessage("Exec could not get a %s license.",lic_name);
	    return ERROR;
	    
	  default:
	    /* invalid license type */
	    perror("License Error: Invalid message from license process.");
	    exit (-1);
	}
    }
    else {
	perror("fork");
	exit (-1);
    }

    /* NOTREACHED */
}  


/* finish the stuff that needs to happen after DXinit */
/* this is because GetLicense(MPLIC) is called before */
/* DXinit					      */

Error ExLicenseFinish() 
{

	if(!MPlic_tried)
	  return OK;
	
	if (shadow_fd_mplic >= 0)
	  DXRegisterInputHandler(ExLicenseDied,shadow_fd_mplic,NULL);

	if(_dxd_exRemoteSlave)
	  DXMessage("Host %s:%s",_dxd_exHostName,messagebuf);
	else
	  DXMessage(messagebuf);

	return OK;
}

Error ExGetPrimaryLicense()
{
    extern lictype _dxd_exForcedLicense;
    lictype lic;
    int force;

    if (_dxd_exForcedLicense == NOLIC) {
	lic = DXLIC;
	force = FALSE;
    } else {
	lic = _dxd_exForcedLicense;
	force = TRUE;
    }
    return ExGetLicense(lic,force);
}


static Error checkexp(char *root, lictype ltype)
{
    char   key[KEY_LEN];
    char   cryptHost[HOST_LEN];
    char   cryptTime[HOST_LEN];
    char   host[HOST_LEN];
    time_t timeOut;
    int    i;
    char  *myCryptHost;
    int    host_match;
    time_t timenow;
    char   fileName[HOST_LEN];
    char  *key_location, key_location_buf[1024];
    char  *cp;
    int    suppresslicmsg = 0;
    FILE   *f;
    
    for (i = 0; i < sizeof(key); ++i)
	key[i] = '\0';
    
    if (!system_hostname(host))
	return ERROR;

    timenow = time(NULL);
    
    /* if the DXSTARTUP env var is set to one, we are running
     * with a temp oneday trial key created by the startup ui.
     * suppress the messages about a trial key or when it expires
     * so the user can't tell how we are doing this.
     */
    cp = getenv("DXSTARTUP");
    if (cp && (atoi(cp) == 1))
	suppresslicmsg++;

  if (getenv("DXTRIALKEY")) {
        char *k = getenv("DXTRIALKEY");
	key_location = "DXTRIALKEY environment variable";
        strncpy(key,k,27);
        key[27] = '\0'; /* Make sure it is terminated */
  } else {
      char *fname;
      fname = getenv("DXTRIALKEYFILE");
      if (!fname) {
          sprintf(fileName, "%s/expiration", root);
          fname = fileName;
      }
      f = fopen(fname, "r");
      if (f)  {
	sprintf(key_location_buf,"file %s",fname);	
	key_location = key_location_buf;
        fgets(key, 27, f);
        fclose(f);
      } else {
        return ERROR;
      }
  }

    if (!trial_file_exists) {
        if (ltype == MPLIC) {
	  char buf[1024];
	  sprintf(buf,"Found Data Explorer trial password in %s.\n",
							key_location);
	  if (!suppresslicmsg)
	      strcat(messagebuf,buf);
	  trial_file_exists = TRUE;
	} else {
	    if (!suppresslicmsg)
	       DXMessage("Found Data Explorer trial password in %s.",key_location);
	}
    }
    
    
    if (strlen(key) != 26) {
        if (ltype == MPLIC) 
	  strcat(messagebuf,"You are running an expired Trial version of Data Explorer.\n");
	else
	  DXMessage("You are running an expired Trial version of Data Explorer.");

	return ERROR;
    }
    
    for (i = 0; i < 13; ++i) {
	cryptHost[i] = key[2 * i];
	cryptTime[i] = key[2 * i + 1];
    }
    cryptHost[i] = key[2 * i] = '\0';
    cryptTime[i] = key[2 * i + 1] = '\0';
    


    if (ltype == MPLIC) {
    	if (cryptTime[0] != 'A' ||
	    cryptTime[10] != '9' ||
	    cryptTime[12] != 'D') {
	    strcat(messagebuf,"You are running an Expired trial version of Data Explorer.\n");
	    return ERROR;
    	}
    	if (cryptTime[1] != 'm' ||
	    cryptTime[11] != 'l' ) { 
	    strcat(messagebuf,"Single processor trial key found, MP will not be enabled.\n");
	    return ERROR;
	}
    }
    else if (cryptTime[0] != 'A' || 
	cryptTime[10] != '9' || 
	cryptTime[12] != 'D') {
	DXMessage("You are running an Expired trial version of Data Explorer.");
	return ERROR;
    }
    
    myCryptHost = crypt(host, KEY1);
    host_match = strcmp(cryptHost, myCryptHost) == 0;
    if (!host_match) {
        myCryptHost = crypt(ANYWHERE_HOSTID, KEY1);
        host_match = strcmp(cryptHost, myCryptHost) == 0;
    }
    if (!host_match) {
        if (ltype == MPLIC)
	  strcat(messagebuf,
		"you are running a trial version of Data Explorer"
		" on an unlicensed host\n");
	else
	  DXMessage("You are running a trial version of Data Explorer"
		" on an unlicensed host.");
	return ERROR;

    }
    
    if(cryptTime[1]=='s')
      sscanf(cryptTime, "As%08x95D", &timeOut); 
    else if (cryptTime[1]=='m')
      sscanf(cryptTime, "Am%08x9lD", &timeOut);
      

    timeOut ^= 0x12345678;
    
    if (timenow > timeOut) {
        if (ltype == MPLIC) { 
	  strcat(messagebuf,
	    "You are running an expired trial version of Data Explorer.\n");
	} else {
	  DXMessage("You are running an expired trial version of Data "
			"Explorer.");
    	  DXMessage("This trial key expired on %s", ctime(&timeOut));
	}
	return ERROR;
    }
    
    if (ltype != MPLIC) {
	if (!suppresslicmsg)
	    DXMessage("This trial key expires on %s", ctime(&timeOut));
        _dxd_ExHasLicense = TRUE;
    }

    return OK;
}




/* system specific way to return the hostname we use for the license
 */

#if defined(alphax)
#include <stdio.h>              /* standard I/O */
#include <errno.h>              /* error numbers */
#include <sys/socket.h>         /* socket definitions */
#include <sys/ioctl.h>          /* ioctls */
#include <net/if.h>             /* generic interface structures */
#include <sys/systeminfo.h>     /* maybe someday this will be implemented ...arg! */
#endif


#if defined(aviion) || defined(solaris) 
#include <sys/systeminfo.h>
#endif
#if defined(ibm6000) || defined(hp700)
#include <sys/utsname.h>
#endif

static Error system_hostname(char *host)
{

#if defined(ibm6000) || defined(hp700)
    struct utsname name;
#endif
#if defined(indigo) || defined(sun4) ||  defined(sgi) 
    long   name;
#endif

#if ibm6000
#define FOUND_ID 1
    uname(&name);
    name.machine[10] = '\0';
    strcpy(host, name.machine+2);
#endif
#if hp700
#define FOUND_ID 1
    uname(&name);
    name.idnumber[10] = '\0';
    strcpy(host, name.idnumber+2);
#endif
#if indigo || sgi        /* sgi does not like #if...#elif..#endif construct */
#define FOUND_ID 1
    name = sysid(NULL);
    sprintf(host, "%d", name);
    strcpy(host, host+2);
#endif
#if sun4 
#define FOUND_ID 1
    name = gethostid();
    sprintf(host, "%x", name);
#endif
#if aviion
#define FOUND_ID 1
    sysinfo(SI_HW_SERIAL,host,301);
#endif
#if solaris
#define FOUND_ID 1
    sysinfo(SI_HW_SERIAL,host,301);
    sprintf(host, "%x", atol(host));
#endif
#if alphax
#define FOUND_ID 1
    {
    char *device;
    char *dflt_devices[] = {"tu0","ln0", NULL };
    int s,i				/* On Alpha OSF/1 we use ethernet */;

    /* Get a socket */
    s = socket(AF_INET,SOCK_DGRAM,0);
    strcpy(host,"");
    if (s < 0) {
        perror("socket");
    } else {
	for (i=0, device=(char*)getenv("DXKEYDEVICE"); dflt_devices[i]; i++) {
	    static   struct  ifdevea  devea;  /* MAC address from and ioctl()*/
	    char *dev, buf[32];
	    if (!device) 
		dev = dflt_devices[i];
	    else
		dev = device;
	    strcpy(devea.ifr_name,dev);
	    if (ioctl(s,SIOCRPHYSADDR,&devea) >= 0)  {
		strcpy(host,"");
		for (i = 2; i < 6; i++){
		    sprintf(buf,"%x", devea.default_pa[i] );
		    strcat(host,buf);
		}
		break;
	    } 
	    if (device) break;
	}
	close(s);
    }
  }
#endif

#if !defined(FOUND_ID)
    /* Trial version not supported on this architecture */
    return ERROR;
#else
# undef FOUND_ID
#endif
    
    return OK;
}

#endif /* DXD_LICENSED_VERSION */


/*
 * C H E C K   B E T A   B U I L D   D A T E  
 */
#ifdef DXD_BETA_VERSION

#define DAYS_SINCE(year,cumDays) {\
int i;\
cumDays=0;\
for(i=70;i<year;i++){\
if((i&3)==0)cumDays+=366;\
else cumDays+=365;}\
}

#if defined(alphax) 
extern int getdate_err;
extern struct tm *getdate(char *string);
#endif

static char *DuplicateString(char *string)
{
    char * new_string; 

    if(string == NULL)
        return NULL;

    new_string = malloc(strlen(string) + 1);
    strcpy(new_string, string);

    return new_string;
}

void _dxf_betaTimeoutCheck()
{
#define BETA_DAYS 60
#define BETA_SECONDS (BETA_DAYS*24*60*60)

#ifdef DXD_WIN
    char achDate[64], szDay[32], szMonth[32], szYear[32];
    int iMonth, iDaysPassed;
    struct tm  *when;
    time_t now, compile_t;

    time(&now);	//	Get sec. since Jan 1 1970, midnight 00:00:00

    sprintf(achDate, "%s", __DATE__);
    sscanf(achDate, "%s%s%s", szMonth, szDay, szYear);
    iMonth = 0;
    if(strnicmp(szMonth, "Jan", 3) == 0) iMonth = 1;
    if(strnicmp(szMonth, "Feb", 3) == 0) iMonth = 2;
    if(strnicmp(szMonth, "Mar", 3) == 0) iMonth = 3;
    if(strnicmp(szMonth, "Apr", 3) == 0) iMonth = 4;
    if(strnicmp(szMonth, "May", 3) == 0) iMonth = 5;
    if(strnicmp(szMonth, "Jun", 3) == 0) iMonth = 6;
    if(strnicmp(szMonth, "Jul", 3) == 0) iMonth = 7;
    if(strnicmp(szMonth, "Aug", 3) == 0) iMonth = 8;
    if(strnicmp(szMonth, "Sep", 3) == 0) iMonth = 9;
    if(strnicmp(szMonth, "Oct", 3) == 0) iMonth = 10;
    if(strnicmp(szMonth, "Nov", 3) == 0) iMonth = 11;
    if(strnicmp(szMonth, "Dec", 3) == 0) iMonth = 12;
    
    when = localtime(&now);
    when->tm_sec = when->tm_hour = when->tm_min = 0;
    when->tm_mday = atoi(szDay);
    when->tm_mon = iMonth - 1;
    when->tm_year = atoi(szYear) - 1900;

    compile_t = mktime(when);
    if (compile_t == -1) 
	iDaysPassed = BETA_DAYS * 2;
    else
	iDaysPassed = (now - compile_t)/ (24*60*60);

    if (iDaysPassed > BETA_DAYS) {
	fprintf (stderr, "%s\n\texpired %d days after its release.\n", 
	    DXD_VERSION_STRING, BETA_DAYS);
	exit(1);
    }



#else  /* DXD_WIN */

#if defined(ibm6000) || defined(sun4)
#define NO_GETDATE
#endif

#if !defined(NO_GETDATE) || !defined(sun4)
#define NORMAL_TIMEZONE_CONVERSION 
#endif

#ifndef NORMAL_TIMEZONE_CONVERSION
/*			       J   F   M    A    M    J    J    A    S    O    N*/ 
static int yday[11] =       { 31, 28, 31,  30,  31,  30,  31,  31,  30,  31,  30 };
static int cum_yday[11]; /* { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 }; */
#endif

    struct tm *comp_time = NULL;
    time_t today = time (NULL);
    char *compile_date = __DATE__;
    char *compile_time = __TIME__;
    char date_mask[512];
    char date_time[128];
    int abort_the_run = FALSE;
    int hours, minutes;
    int seconds = 0;
    int days;
#ifndef NORMAL_TIMEZONE_CONVERSION
    int i;
    int current_year = localtime(&today)->tm_year;
#endif
#if !defined(NO_GETDATE)
    /*
     * If the user has a DATEMSK, then save it for later restoration
     */
    const char *od = getenv("DATEMSK");
    char *old_datemsk = NULL;
    const char *cp = getenv("DXROOT");
    char *dx; 
    int len;
    char date_file[512];
    char* admin_problem = NULL;
    struct stat statb;
#else
    struct tm tmstruct;
#endif
#ifdef DEBUG
	int diff_seconds;
	int diff_days;
	int diff_hours;
	int diff_minutes;
#endif

    /*
     * just in case
     */
    if (getenv("TCHK_BAIL_OUT")) return ;

#ifndef NORMAL_TIMEZONE_CONVERSION
    cum_yday[0] = yday[0];
    for (i=1; i<11; i++) {
	if ((i==1) && (current_year%4))
	    cum_yday[i] = cum_yday[i-1] + yday[i] + 1;
	else
	    cum_yday[i] = cum_yday[i-1] + yday[i];
    }
#endif

#if !defined(NO_GETDATE)
    if ((od) && (od[0])) old_datemsk = DuplicateString((char *)od);

    /* Make the DATEMSK environment variable point to the format file
     * which we'll store in the dx tree.
     */
    if ((!cp) || (!cp[0]))  cp = "/usr/lpp/dx";

    dx = DuplicateString((char *)cp); 
    len = strlen(dx);
    if (dx[len-1] == '/') dx[len-1] = '\0';
    sprintf (date_file, "%s/ui/date.fmt", dx);
    sprintf (date_mask, "DATEMSK=%s", date_file);
    /*
     * Check for the date.fmt file.  If it's not found this scheme will fail.
     * The root cause of the problem is an improperly set DXROOT, so tell the
     * user.  The ui won't start.
     */
    if (stat (date_file, &statb) == -1) 
	admin_problem = "Your DXROOT environment variable is set incorrectly.";
    free(dx);
#endif

    sprintf (date_time, "%s %s EDT", compile_date, compile_time);

#ifdef NO_GETDATE
    comp_time = &tmstruct;
    /* I don't know of a way to determine if strptime() succeeded or not. */
    strptime(date_time, "%b %d %Y %H:%M:%S", comp_time);
#ifndef NORMAL_TIMEZONE_CONVERSION
    timelocal(comp_time);
#endif
#else
    /* This is a leak, but without the DuplicateString, putenv trashes the environ */
    putenv (DuplicateString(date_mask)); 
    comp_time = getdate (date_time);

    /*
     * Retry the time conversion because some systems don't recognize the time
     * zone EST5EDT.  I don't know why that is.  It isn't necessary to use the
     * time zone.  It provide slightly better accuracy so that a better customer
     * can't continue to run an hour or two after the real expiration.  The real
     * reason for using the timezone in the time calculation is to make it easy
     * to test the code.
     */
    if ((!comp_time) && (admin_problem == NULL)) {
	sprintf (date_time, "%s %s", compile_date, compile_time);
	comp_time = getdate (date_time);
	if (!comp_time)
	    admin_problem = "System time / compile time comparison failed.";
    }
#endif

    if (!comp_time)
	abort_the_run = TRUE;
    else {


#ifdef NORMAL_TIMEZONE_CONVERSION
	DAYS_SINCE(comp_time->tm_year,days); 
	days+= comp_time->tm_yday;
	hours = (days * 24) + comp_time->tm_hour - (1* (comp_time->tm_isdst>0));
#else
	DAYS_SINCE(comp_time->tm_year,days); 
	days+= (comp_time->tm_mon?cum_yday[comp_time->tm_mon-1]: 0) + comp_time->tm_mday;
	hours = (days * 24) + comp_time->tm_hour;
#endif
	minutes = (hours * 60) + comp_time->tm_min;
#ifdef NORMAL_TIMEZONE_CONVERSION
	seconds = minutes * 60 + comp_time->tm_sec + (int)timezone;
#else
	seconds = minutes * 60 + comp_time->tm_sec - (int)comp_time->tm_gmtoff;
#endif
	if ((today - seconds) > BETA_SECONDS) {
	    abort_the_run = TRUE;
	}
#ifdef DEBUG
	diff_seconds = today-seconds;
	diff_days = diff_seconds/86400;
	diff_seconds-= diff_days * 86400;
	diff_hours = diff_seconds/3600;
	diff_seconds-= diff_hours*3600;
	diff_minutes = diff_seconds/60;
	diff_seconds-= diff_minutes*60;
	fprintf(stdout, "%s age(days H:M:S): %d %d:%d:%d\n",
	    DXD_VERSION_STRING, diff_days, diff_hours, diff_minutes, diff_seconds);
#endif
    }
    if (abort_the_run) {
#if !defined(NO_GETDATE)
	if (admin_problem) {
	    fprintf (stderr, "Beta licensing failed for \n%s\n\t%s\n", 
		DXD_VERSION_STRING, admin_problem);
	} else
#endif
	fprintf (stderr, "%s\n\texpired %d days after its release.\n", 
	    DXD_VERSION_STRING, BETA_DAYS);
	exit(1);
    }


#ifndef NO_GETDATE
    /*
     * Restore DATEMSK
    */
    if (old_datemsk) {
	putenv(old_datemsk);
	/* free(old_datemsk); */
    }
#endif

#endif	/* DXD_WIN */

#undef BETA_DAYS
#undef BETA_SECONDS
}

#else
void _dxf_betaTimeoutCheck()
{
}
#endif

#ifdef DXD_WIN

char _dxd_PCLicenseType = 't';
int  _dxd_PCHardwareRenderingOK = 1;
int  _dxd_PCLoadModsOK = 1;

#include <windows.h>
#include <math.h>

static int getregval(char *name, char *value)
{
    char key[500];
    int valtype;
    unsigned long sizegot = 500;
    int word;
    char errstr[200];
    HKEY hkey[10];
    long rc;
    int i, k=0;

#define iferror(s)		\
    if (rc != 0) {		\
	strcpy(errstr, s);	\
	goto error;		\
    }

    strcpy(value, "");
    word = 0;
    strcpy(key, "SOFTWARE");

    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	KEY_QUERY_VALUE, &hkey[k++]);

    strcat(key, "\\IBM");
    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	KEY_QUERY_VALUE, &hkey[k++]);
    iferror("Error opening key");

    strcat(key, "\\IBM Visualization Data Explorer");
    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	KEY_QUERY_VALUE, &hkey[k++]);
    iferror("Error opening key");

    strcat(key, "\\CurrentVersion");
    rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR) key, 0,
	KEY_QUERY_VALUE, &hkey[k++]);
    iferror("Error opening key");

    rc = RegQueryValueEx(hkey[k-1], (LPTSTR) name, (LPDWORD) 0, 
	(LPDWORD) &valtype, (LPBYTE) value, &sizegot);
    iferror("Query value failed");

    for (i=k; i > 0; i--) {
	rc = RegCloseKey(hkey[i-1]);
	iferror("CloseKey failed");
    }

    switch(valtype) {
	case REG_DWORD:
	    word = *((int *)value); 
	    value = "";
	    break;
	case REG_SZ:
	    break;
	default:
	    return 0;
    }

    return 1;

error:
    fprintf(stderr, "%s: rc = %d\n", errstr, rc);
    return 0;
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

static int getuserinforeg(char *username, char *userco, char *keystr)
{
    *username = '\0';
    *userco = '\0';
    *keystr = '\0';
    getregval("UserName", username);
    getregval("CompanyName", userco);
    getregval("LicenseKey", keystr);
    keyformat(keystr);
    return 1;
}

static int gettimenow(int *m, int *d, int *y)
{
    SYSTEMTIME t;
    GetSystemTime(&t);
    *m = t.wMonth;
    *d = t.wDay;
    *y = t.wYear;
    return 1;
}

static int addtotime(int *m, int *d, int *y)
{
    int mm, dd, yy;

    gettimenow(&mm, &dd, &yy);
    *y += yy;
    *m += mm;
    if (*m>12) {
	*y += (*m-1)/12;
	*m = *m%12 + 1;
    }
    *d += dd;
    if (*d > 28) {
	(*m)++;
	*d = *d%31;
    }
    if (*m>12) {
	*y += (*m-1)/12;
	*m = *m%12 + 1;
    }
    return 1;
}

static int getnumusersfromkey(char *keystr, int *num)
{
    int numcode;

    keyformat(keystr);
    sscanf(&keystr[6], "%02d", &numcode);

    if      (numcode < 50)
	*num =    1 +   1*(numcode -  0);
    else if (numcode < 60)
	*num =   55 +   5*(numcode - 50);
    else if (numcode < 70)
	*num =  120 +  20*(numcode - 60);
    else if (numcode < 74)
	*num =  350 +  50*(numcode - 70);
    else if (numcode < 79)
	*num =  600 + 100*(numcode - 74);
    else 
	*num = 1500 + 500*(numcode - 79);

    return 1;
}

static int genkey(char *keystr, char *username, char *userco,
		    int m, int d, int y, int numusers, char lictype)
{
    char *p, *q;
    unsigned int key, key1, key2, key3, prime;
    int i;
    int numcode;
    char data[500];

    data[0] = (char)(m + (int)'a');
    if (d > 20)
	data[0] = (char)((int)data[0] + 13);
    data[1] = (char)(d%20 + (int)'b');
    data[2] = (char)((y - 1994)/10 + (int)'g');
    data[3] = (char)((y - 1994)%10 + (int)'m');
    if (!lictype)
	lictype = 't';
    data[4] = lictype;

    if      (numusers <   50)
	numcode =  0 + (numusers -    1) /   1;
    else if (numusers <  120)
	numcode = 50 + (numusers -   55) /   5;
    else if (numusers <  350)
	numcode = 60 + (numusers -  120) /  20;
    else if (numusers <  600)
	numcode = 70 + (numusers -  350) /  50;
    else if (numusers < 1500)
	numcode = 74 + (numusers -  600) / 100;
    else
	numcode = 79 + (numusers - 1500) / 500;

    if (numcode > 99)
	numcode = 99;
    if (numcode <  0)
	numcode =  0;

    q = &data[5];
    for (p=username; *p; p++)
	if (!isspace(*p) && !ispunct(*p))
	    *(q++) = tolower(*p);
    for (p=userco; *p; p++)
	if (!isspace(*p) && !ispunct(*p))
	    *(q++) = tolower(*p);

    if (numcode) {
	sprintf(q, "%02d", numcode);
	q += 2;
    }

    *q = '\0';

    key = 99;
    key = key * 100 + 99;
    key = key * 100 + 83;

    prime = 4999;
    prime = prime * 1000 + 999;

    for (i = 0, p=data; *p; p++, i++)
	key += (*p * (i + key)) * prime;

    key %=   10000000000;
    key1 = key/100000000;
    key2 = key%100000000;
    key2 /= 10000;
    key3 = key%10000;
    sprintf(keystr, "%c%c%c%c%c %02d%02d %04d %04d", data[0],
		data[1], data[2], data[3], data[4], numcode, key1, key2, key3);
    return 1;
}

static int getdatefromkey(char *keystr, int *m, int *d, int *y)
{
    *m = (int)keystr[0] - (int)'a';
    *d = (int)keystr[1] - (int)'b';
    if (*m > 12) {
	*m -= 13;
	*d += 20;
    }
    if (*d < 1)
	*d = 1;
    if (*d > 31)
	*d == 31;
    *y = ((int)keystr[2] - (int)'g') * 10 +
		(int)keystr[3] - (int)'m' + 1994;
    return 1;
}

static int isexpired(char *keystr)
{
    int m, d, y;
    int ms, ds, ys;

    gettimenow(&ms, &ds, &ys);
    getdatefromkey(keystr, &m, &d, &y);
    if (ys > y)
	return 1;
    if (ys == y && ms > m)
	return 1;
    if (ys == y && ms == m && ds > d)
	return 1;
    return 0;
}

static void PCBadLicenseTimeout()
{
    /*  Make this 80 so that ui tends to time out first */
    Sleep(80*1000);
    printf("Trial time period ended.  Exiting program.\n");
    ExitProcess(0);
}

static void InstallTimeout()
{
    LPDWORD PCTimeoutThreadID;
    static int beenhere=0;

    if (beenhere)
	return;
    beenhere = 1;

    printf("Allowing 60 second trial period.\n");
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) PCBadLicenseTimeout,
		    (LPVOID) NULL, 0, (LPVOID) &PCTimeoutThreadID);
    return;
}

void PCGetLicense()
{
    char username[200];
    char userco[200];
    char keystrreg[100];
    char keystr[100];
    char lictype;
    int m;
    int d;
    int y;
    int num;
    int expired;

    getuserinforeg(username, userco, keystrreg);
    if (strlen(username) + strlen(userco) < 6) {
	fprintf(stderr, "Improper registration: short username and company\n");
	return;
    }
    if (!keyformat(keystrreg)) {
	fprintf(stderr, "Improper registration: registration key is not in proper format: %s\n",
			    keystrreg);
	return;
    }
    fprintf(stderr, "Registered to %s of %s\n", username, userco);
    getdatefromkey(keystrreg, &m, &d, &y);
    getnumusersfromkey(keystrreg, &num);
    lictype = keystrreg[4];
    genkey(keystr, username, userco, m, d, y, num, lictype);

    if (strcmp(keystr, keystrreg)) {
	fprintf(stderr, "Improper registration: key does not match user setup\n");
	InstallTimeout();
	return;
    }

    expired = isexpired(keystrreg);
    if (expired) {
	fprintf(stderr, "Registration expired %d/%d/%d\n", m, d, y);
	InstallTimeout();
	return;
    }

    /* Don't show expire date if license isn't beta or trial */
    if (lictype == 'b' || lictype == 't') {
	fprintf(stderr, "Registration expires %d/%d/%d\n", m, d, y);
    }

    if (num > 1)
	fprintf(stderr, "Allows %d concurrent users.\n", num);

    if (lictype == 'p') {
	_dxd_PCHardwareRenderingOK = 0;
	_dxd_PCLoadModsOK = 0;
    } else if (lictype == 'h') {
	_dxd_PCLoadModsOK = 0;
    }

    return;
}

#endif
