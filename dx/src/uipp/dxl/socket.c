/*  Open Visualization Data Explorer Source File */


#ifdef NON_ANSI_SPRINTF
int
_DXLsprintf(char *s, const char* format, ...)
{
    va_list ap;
    va_start(ap,format);
    vsprintf(s,(char*)format,ap);
    va_end(ap);
    return strlen(s);
}

#endif

#define DXL_QUEUE_LENGTH	1

static int socketTimeout = DXL_ACCEPT_TIMEOUT;
static int basePort = DXL_BASE_PORT;

void
DXLSetBasePort(const int port)
{
    basePort = port;
}

int
DXLGetBasePort()
{
    return basePort;
}

#if 0
static char hostname[256] = "localhost";
static char hostIsLocal = 1;

void
DXLSetHost(const char *host)
{
    strcpy(hostname, host);
    hostIsLocal = HostIsLocal(host);
}

char *
DXLGetHost()
{
    return hostname;
}

int
DXLIsHostLocal()
{
    return hostIsLocal;
}

#endif

static int nConnection = 0;
static int
_dxl_MakeConnection(DXLConnection *connection, int port, const char *host)
{
    int   local, i;
    u_short pport;
    struct sockaddr_in server;
#ifdef DXD_HAS_WINSOCKETS
    fd_set fdtmp, dxfds;
#endif

#if   !defined(DXD_IBM_OS2_SOCKETS)  && !defined(DXD_HAS_WINSOCKETS)
    if (port <= 0)
    {
	fprintf(stderr, "_dxl_MakeConnection: bad port\n");
	goto error;
    }

#endif

    if (host) {
	local = DXLIsHostLocal(host);
    } else {
	host = "localhost";
	local = 1; 
    }

    /*
     * If this is the first instance of a packet interface, then set up
     * to ignore SIGPIPE (but we watch for EPIPE).
     */
#ifndef DXD_NON_UNIX_SOCKETS
    if ((nConnection++ == 0) && (getenv("DX_NOSIGNALS") == NULL))
	signal(SIGPIPE, SIG_IGN);
#endif

/*
 * SMH  NT can't local socket AF_UNIX
 */
#ifndef DXD_NON_UNIX_SOCKETS     
    
    if (local)
    {
	int c;
	struct sockaddr_un userver;

	memset((char*)&userver, 0, sizeof(userver));
	userver.sun_family = AF_UNIX;
	sprintf(userver.sun_path, "/tmp/.DX-unix/DX%d", port);

	connection->fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (connection->fd < 0)
	    goto error;
	
	if ((c = connect(connection->fd,
		    (struct sockaddr *)&userver,
		    sizeof(userver) - sizeof(userver.sun_path) +
				      strlen(userver.sun_path))) >= 0)
	{
	    return 1;
	}
	else if (!strcmp(host, "unix"))
	{
	    perror("_dxl_MakeConnection");
	    goto error;
	}
    }


    memset((char *)&server, 0, sizeof(server));

#endif 
/*
 * SMH end bypass AF_UNIX Style socket
 */

    server.sin_family = AF_INET;
    pport = port;
    server.sin_port   = htons(pport);

    /*
     * Get host address.
     */
    if (isdigit(host[0]))
    {
#ifdef aviion
        server.sin_addr.s_addr = inet_addr().s_addr;
#else
	/*
	 * suits explicit cast of host
	 */
	server.sin_addr.s_addr = inet_addr((char*)host);  
#endif
    }
    else
    {
	struct hostent* hostp;
#ifdef DXD_OS_NON_UNIX
        if (local || !_stricmp((char*)host, "localhost") || !_stricmp((char*)host, "localPC"))
	{
	    unsigned long locaddr = inet_addr("127.0.0.1");
	    memcpy((void*)&server.sin_addr, &locaddr, sizeof(unsigned long));
	}
	else
#endif
	{
	    hostp = gethostbyname((char*)host);
	    if (hostp == NUL(struct hostent*))
	    {
		goto error;
	    }
	    memcpy((void*)&server.sin_addr, hostp->h_addr, hostp->h_length);
	}
    }
    connection->fd = socket(AF_INET, SOCK_STREAM, 0);
#ifndef DXD_WIN
    if (connection->fd < 0) 
        goto error;
#else
    if (connection->fd < 0) {
	int s_error = WSAGetLastError();
	printf("Socket error %d connecting to server\n", s_error);
	goto error;
    }
#endif

    if (connect(connection->fd, (struct sockaddr*)&server, sizeof(server)) < 0)
	goto error;

#if   defined(DXD_IBM_OS2_SOCKETS)   || defined(DXD_HAS_WINSOCKETS)
    {
#ifdef DXD_IBM_OS2_SOCKETS
	int dontblock = 1;
	if (ioctl(connection->fd, FIONBIO, (char *) &dontblock, sizeof(dontblock))<0)
	     goto error;
	if (select((int *)&connection->fd, 0, 1, 0, -1) <= 0)
	     goto error;
#endif

#ifdef DXD_HAS_WINSOCKETS
	u_long dontblock = 1;
	struct timeval  tv;
	tv.tv_usec = 5;
	tv.tv_sec = 0;
	if (ioctlsocket (connection->fd, FIONBIO, (u_long *) &dontblock)<0)
	     goto error;

	FD_ZERO(&dxfds);
	i = connection->fd;
	FD_SET(i, &dxfds);
	i = select(i, &dxfds, NULL, NULL, &tv);
	if(i < 0) {
	    int fstest = WSAGetLastError();
	    printf("socket error %d connecting to server\n", fstest);
	    goto error;
	}
#endif
    }
#endif


    return 1;

error:

    return 0;
 }

DXLConnection *
DXLConnectToRunningServer(int port, const char *host)
{
    DXLEvent event;
    DXLConnection *connection = DXLNewConnection(); 
    if (! connection)
	goto error;
    

    if (getenv("DXLTRACE")) {
        connection->debugMessaging = 1;
	fprintf(stderr,"DXLink library is version %d.%d.%d\n",
		IBM_MAJOR_VERSION,IBM_MINOR_VERSION,IBM_MICRO_VERSION);
    }


    if (!_dxl_MakeConnection(connection, port, host))
	goto error;

    /* Ask the server for its version */
    DXLSendImmediate(connection, "version"); 
    /* Wait until we get a response */
    if (DXLWaitPacketString(connection,PACK_INFO,"version:",&event)) {
	int major, minor, micro, items;

	if (strstr(event.contents,"Executive"))
	{
	    connection->dxuiConnected = 0;
	    items = sscanf(event.contents,"Executive version: %d %d %d",
			    &major, &minor, &micro);
	    if (items == 3)
	    {
		    connection->majorVersion = major;
		    connection->minorVersion = minor;
		    connection->microVersion = micro;
	    }
	    DXLClearEvent(&event);
	}
	else if (strstr(event.contents,"UI"))
	{
	    connection->dxuiConnected = 1;
	    items = sscanf(event.contents,"UI version: %d %d %d",
			    &major, &minor, &micro);
	    if (items == 3)
	    {
		    connection->majorVersion = major;
		    connection->minorVersion = minor;
		    connection->microVersion = micro;
	    }
	    DXLClearEvent(&event);
	}
	DXLClearEvent(&event);
    }

    if (connection->majorVersion == 0) {
	fprintf(stderr,"Can not determine server version number!\n");
	goto error;
	
    }

    if (connection->debugMessaging) 
	fprintf(stderr,"DXLink connected to server at version %d.%d.%d\n",
			connection->majorVersion,
			connection->minorVersion,
			connection->microVersion);
  
    /*
     * Make sure the remote connection is at the same or later release
     * than this library.
     */
    if ((connection->majorVersion < IBM_MAJOR_VERSION) ||
	(connection->minorVersion < IBM_MINOR_VERSION)) {
	fprintf(stderr,"Warning: DXLink library (V %d.%d) is at a later "
			"level than the\n\t remote connection (V %d.%d)\n",
			IBM_MAJOR_VERSION,IBM_MINOR_VERSION,
			connection->majorVersion,
			connection->minorVersion);
    }


#if defined(DXLINK_LICENSES_EXEC) && !defined(OS2)   && !defined(DXD_WIN)
    /*
     * Tell the executive that DXLink has a concurrent license
     * so that the executive does not need one.
     * FIXME: Pass cmdline argument that tells exec to get its own license.
     */
    if (!connection->dxuiConnected) {
	char *lic_token = "LICENSE:";
	char lic_code[64];
	char *outkey, *p= NULL, *dup;
	int unlicensed = 1;
	DXLSendImmediate(connection,"getkey");

	if (!DXLGetPacketString(connection,PACK_INFO,lic_token,&event)) 
	    goto error;
	p = strstr(event.contents,lic_token);
	p = p + strlen(lic_token);
	while (*p == ' ') p++;
	strcpy(lic_code,p);	
	DXLClearEvent(&event);

	if (p) {	
	    outkey = GenerateExecKey(lic_code,0xafe3);
	    if (outkey) {
		char buf[1024];
		sprintf(buf,"license %s",outkey);
		DXLSendImmediate(connection, buf);
		FREE(outkey);
		while (1) {
		    if (!DXLGetPacketString(connection,PACK_INFO,
							lic_token,&event)) {
			break;
		    } else if (strstr(event.contents,"AUTHORIZED")) {
			if (strstr(event.contents,"UNAUTHORIZED")) 
			    unlicensed = 1;
			else if (strstr(event.contents,"AUTHORIZED")) 
			    unlicensed = 0;
			break;
		    }
		    DXLClearEvent(&event);
		}
		DXLClearEvent(&event);
	    }
	}
	if (unlicensed) {
	   fprintf(stderr,"Executive could not get a license\n");
	   goto error;
  	}
    }
#endif /* defined(DXLINK_LICENSES_EXEC) && !defined(OS2)    && !defined(DXD_WIN)*/

    return connection;

error:
    if (connection)
	DXLCloseConnection(connection);

    return NULL;
}


void
DXLSetSynchronization(DXLConnection *conn, const int onoff)
{
    conn->synchronous = onoff;
}

int
DXLIsHostLocal(const char *host)
{
    char localHostname[BUFSIZ];
    char localhostHostname[BUFSIZ];
    char remoteHostname[BUFSIZ];
    struct hostent *he;
    int  hostnameFound;
#ifndef DXD_LACKS_UTS
    struct utsname Uts_Name;

    if (strcmp ("unix", host) == 0)
	return TRUE;

    he = gethostbyname ((char*)host);
    if (he == NULL) {
	fprintf(stderr, "%s: Invalid host", host);
	return(0);
    }
    strcpy(remoteHostname, he->h_name);

    if (uname(&Uts_Name) >= 0 && (he=gethostbyname(Uts_Name.nodename)) != NULL)
    {
	strcpy(localHostname, he->h_name);
	hostnameFound = 1;
    }
    else
    {
	hostnameFound = 0;
    }

    he = gethostbyname ("localhost");
    if (he == NULL) {
	fprintf(stderr, "%s: Invalid host", "localhost");
	return (0);
    }
    strcpy(localhostHostname, he->h_name);

    return ((hostnameFound && strcmp (localHostname, remoteHostname) == 0) ||
	    strcmp (localhostHostname, remoteHostname) == 0);
#else
    return TRUE;
#endif  
}

#if defined(DXLINK_LICENSES_EXEC) && !defined(OS2)    && !defined(DXD_WIN)
/* This function creates the message which will tell the exec if it
 * is OK to run without a license. inkey must be at least char[14]
 * and should contain the key returned from the $getkey.  type
 * should be either ConcurrentLicense or NodeLockedLicense. On return
 * inkey holds the string to send to the exec with $license.
 * The returned string must be freed by the caller.
 * FIXME: code is that same is in dxui.
 */

static char *GenerateExecKey(const char *inkey, int licenseType)
{

#ifndef OS2
#define NEEDS_LICENSE_ROUTINES 1
#endif
#if NEEDS_LICENSE_ROUTINES

    int i;
    char keybuf[64];
    char cryptbuf[64];
    char *outkey, salt[8];

    for(i=0;i<4;i++)
      keybuf[i*2]=inkey[i];

    keybuf[1] = 'g';
    keybuf[3] = '3';
    keybuf[5] = '$';
    keybuf[7] = 'Q';
    keybuf[8] = '\0';

    salt[0] = '4';
    salt[1] = '.';
    salt[2] = '\0';

    strcpy(cryptbuf,crypt(keybuf,salt));

    outkey = (char*)MALLOC(64 * sizeof(char));
    sprintf(outkey,"%s%hx",cryptbuf,
                        (unsigned short)licenseType ^
                        (*((unsigned char *)&cryptbuf[4])<<8)+(*((unsigned char
*)&cryptbuf[5])));

    return outkey;
#else
    return NULL;
#endif 

}

#endif /* defined(DXLINK_LICENSES_EXEC) && !defined(OS2)    && !defined(DXD_WIN)  */
