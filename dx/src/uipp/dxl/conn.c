/*  Open Visualization Data Explorer Source File */

    argv[i++] = "self";		/* of negotiated with the remote connection */ 
    argv[i++] = NULL;		

    child = ConnectTo(host, NULL, NULL, i, argv, environ,
			    &in, &out, &err, errorstr);
    if (inp) *inp = in;
    if (outp) *outp = out;
    if (errp) *errp = err;

    free(s);

#ifndef DXD_WIN
    if (child <= 0)
#else
    if (child == 0)
#endif
    {
	fprintf(stderr, "DXLStartChild: %s\n", errorstr);
	return -1;
    }

    port = _dxl_ReadPortNumber(out);
    if (port <= 0)
    {
	if (err >= 0) {
	    char buf[2048];
	    int n = read(err,buf,2048);
	    buf[n] = '\0';
	    fprintf(stderr,buf);
	}
#ifdef DXD_WIN
    TerminateProcess(child,-1);
#else
	kill(child, SIGKILL);
#endif
	return -1;
    }

    return port;
}

DXLError
DXLDeleteConnection(DXLConnection *conn)
{
    DXLEvent *e;
    _dxl_FreeMessageHandlers(conn);

    for (e=conn->events ; e ; ) {
	DXLEvent *tmp = e->next;
	DXLFreeEvent(e);	
	e = tmp;
    }
    conn->events = NULL;

    if (conn->leftOver)
	free(conn->leftOver);

    /*
     * These two are allocated in InitliazeObject/ValueHandler, but
     * deleted here so that the user does not have to link with libDXlite 
     * if not using the Object handling code.
     */
    if (conn->objectHandlerDict)
	DeleteDictionary(conn->objectHandlerDict);
    if (conn->valueHandlerDict)
	DeleteDictionary(conn->valueHandlerDict);

    free(conn);

    return OK;
}

DXLConnection*
DXLNewConnection()
{
    DXLConnection *conn = malloc(sizeof(DXLConnection));
    if (!conn)
	goto error;
   
    memset((char *)conn, 0, sizeof(DXLConnection));

    conn->synchronous    = getenv("DXLSYNCHRONOUS") != NULL;
    /*
     * This is a bit of a hack, but we do this to avoid a problem with 
     * 'include ...' in which a subcontext is create in the exec 
     * and new packets ids are used beginning at zero.  If we also begin
     * at zero, and send an 'include' early, then there can duplicate
     * Complete packets that come back with the same id.  Initializing
     * our first packet id to be a large number should avoid this conflict.
     *  			2/24/96  - dawood
     */
    conn->id = 1000000;

    if (! _dxl_InitMessageHandlers(conn))
        goto error;

    if (! DXLSetErrorHandler(conn, _DXLDefaultHandler, (void *)NULL))
        goto error;

    return conn;

error:
   if (conn->objectHandlerDict)
	DeleteDictionary(conn->objectHandlerDict);
   if (conn->valueHandlerDict)
	DeleteDictionary(conn->valueHandlerDict);
   if (conn)
	free(conn);
   return NULL;

}

DXLConnection *
DXLStartDX(const char *string, const char *host)
{
    int port;
    int fd;
    int in, out,err;
    DXLConnection *connection;


#if  defined(DEBUG)  && defined(DXD_WIN)
    /* This is to spawn DX seperately for debugging */

    if (!host && !getenv("DX_TEST_HOST") ) {
	host = "localhost";

	port = DXLStartChild(string,host);
	if (port == -1)
	    return NULL;
	connection = DXLConnectToRunningServer(port, host);
    }
    else {

	char achStr[32];

	host = getenv("DX_TEST_HOST");

	printf("Enter Port No... "); gets(achStr);
	port = atoi(achStr);
	printf("Getting port %d \n", port);
	connection = DXLConnectToRunningServer(port, host);
    }
#else
    if (!host) 
	host = "localhost";

	port = DXLStartChild(string,host, &in, &out, &err);
	if (port == -1)
	    return NULL;

    connection = DXLConnectToRunningServer(port, host);
    if (connection) {
	connection->in = in;
	connection->out = out;
	connection->err = err;
    }
#endif
    return connection;
}

void
DXLSetBrokenConnectionCallback(DXLConnection *connection,
				void (*proc)(), void *data)
{
    connection->brokenConnectionCallback = proc;
    connection->brokenConnectionCallbackData = data;

}

void _dxl_InvalidateSocket(DXLConnection *connection)
{
    _DXLError(connection, "Connection to DX broken");

     if (connection->brokenConnectionCallback)
        (*connection->brokenConnectionCallback)
                (connection, connection->brokenConnectionCallbackData);

    if (connection->fd >= 0)
    {
	close(connection->fd);

	/*
	 * If there was a system-dependent event handler installed,
	 * then clean it up.
	 */
	_dxf_RemoveEventHandler(connection);

	connection->fd = -1;
    }
}

void
DXLCloseConnection(DXLConnection *connection)
{
    int i;
    DXLEvent *e;

    if (connection->fd >= 0) {
	close(connection->fd);
	connection->fd = 0;
    }

    if (connection->in >= 0) {
	close (connection->in);
	connection->in = 0;
    }
    if (connection->out >= 0) {
	close (connection->out);
	connection->out = 0;
    }
    if (connection->err >= 0) {
	close (connection->err);
	connection->err = 0;
    }

    /*
     * If there was a system-dependent event handler installed,
     * then clean it up.
     */
    _dxf_RemoveEventHandler(connection);

    DXLDeleteConnection(connection);

}

int DXLGetSocket(DXLConnection *connection)
{
    return connection->fd;
}

static int
ConnectTo(const char *host,
		   const char *user,
		   const char *cwd,
		   int ac,
		   char *av[],
		   char *ep[],
		   int *remin,
		   int *remout,
		   int *remerr,
		   char *errstr)
{
    char s[BUFSIZ];
    char wd[BUFSIZ],script_name[500],cmd[1000];
    FILE *fp;
    int i;
#if defined(DXD_WIN) || defined(OS2)
    int *in[2], *out[2], *err[2];
#else
    int in[2], out[2], err[2];
#endif
    char **rep;
    char **fargv = NULL;
    int child;
    struct hostent *he;
    char *home;
    int findx;
    char *pathEnv;
    char *is;
    char *os;
    int  j;
#ifdef hp700
    int  width = MAXFUPLIM;
#else
#ifdef aviion
    int  width = NOFILE;
#else
#ifdef solaris
    int  width = FD_SETSIZE;
#else
#ifdef DXD_HAS_WINSOCKETS
    int  width = FD_SETSIZE;
#else
#ifndef OS2
    int  width = getdtablesize();
#endif
#endif
#endif
#endif
#endif
    char *dnum;
#ifndef DXD_LACKS_UTS
    struct utsname Uts_Name;

    /*
     * Initialize return values (to default negative results).
     */
    *remin  = -1;
    *remout = -1;
    *remerr = -1;
    *errstr = '\0';

    /*
     * Check to see if "host" is a valid hostname.
     */
    if (strcmp("unix", host) != 0)
    {
	he = gethostbyname ((char*)host);
	if (he == NULL)
	{
	    fprintf(stderr, "%s: Invalid host", host);
	    return (-1);
	}
    }

    for (pathEnv = NULL, i = 0; ep[i] && pathEnv == NULL; ++i)
	if (    strncmp (ep[i], "PATH=", strlen("PATH=")) == 0 ||
		strncmp (ep[i], "PATH =", strlen("PATH =")) == 0) 
	    pathEnv = ep[i];

    if (DXLIsHostLocal(host)) {
	char *path;
	char *opath;
	struct stat sbuffer;

	if (verbose) printf ("local\n");

	if (user != NULL)
	    fprintf (stdout, "Different user on local machine ignored\n");

	fargv = (char**)CALLOC((ac + 1), sizeof (char*));
	if (fargv == NULL) {
	    fprintf(stderr, "calloc() error: %s", strerror(errno));
	    goto error_return;
	}
	for (i = 0; i < ac; ++i) {
	    fargv[i] = av[i];
	}
	fargv[i] = 0;
	rep = ep;
	/* Scan through ep looking for "PATH".  If "PATH" is found, then
	 * look through path for the specified command, and if it's
	 * found and executable, replace it in fargv with the expanded 
	 * path name.
	 */
	if (*fargv[0] != '.' && *fargv[0] != '/') {
	    path = strchr (pathEnv, '=') + 1;
	    opath = path = strdup(path);
	    if (path == NULL) {
		fprintf(stderr, "strdup() error: %s", strerror(errno));
		goto error_return;
	    }
	    while (*path) {
		for (i = 0; 
		     *path != '\0' && *path != ':'; 
		     ++i, ++path) {
		    s[i] = *path;
		}
		if (*path == ':') {
		    ++path;
		}
		s[i] = '\0';
		strcat (s, "/");
		strcat (s, av[0]);
		if (stat (s, &sbuffer) < 0) {
		    /* if the file doesn't exist, go on */
		    if (errno == ENOENT) {
			/* We have no more paths to search */
			if (*path == '\0') {
			    goto error_return;
			}
		    }
		    /* Ignore bad stats, we just can't find it */
		    continue;
		}
		/* If it's executable, and a regular file, we're done. */
		if ((sbuffer.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0 &&
		    (sbuffer.st_mode & S_IFREG) != 0) {
		    break;	/* out of while(*path) */
		}
	    }
	    fargv[0] = s;
	    free (opath);
	}
    }
    else {		/* Host is NOT local */
	/* The general thread here is to first create a script on the
	 * remote host using popen().  The script contains shell code to
	 *   1) set up a similar environment to the current one (PATH,...)
	 *   2) exec 'dx -...' 
	 *   3) remove the script from the remote file system.
	 * Then we set up fargv to contain the following: 
	 *    rsh host [ -l user ] /bin/sh /tmp/dx-$host:$pid 
	 */ 

	if (verbose) printf ("remote\n");

	fargv = (char**)CALLOC(12, sizeof(char*));

	if (fargv == NULL) {
	    fprintf(stderr, "calloc() error: %s", strerror(errno));
	    goto error_return;
	}

	
	if (uname(&Uts_Name) < 0) {
	    fprintf(stderr, "uname() error: %s", strerror(errno));
	    goto error_return;
	}
	sprintf(script_name,"/tmp/dx-%s:%d",Uts_Name.nodename,getpid());
	findx=0;
	fargv[findx++] = RSH;
	fargv[findx++] = (char *)host;

	if (user != NULL) {
	    fargv[findx++] = "-l";
	    fargv[findx++] = (char *)user;
	    sprintf(cmd, "%s -c \"%s %s -l %s 'cat > %s' > /dev/null 2>&1\"",
		BSH, RSH, host, user, script_name);
	} else
	    sprintf(cmd, "%s -c \"%s %s 'cat > %s' > /dev/null 2>&1\"",
		BSH, RSH, host, script_name);

	fargv[findx++] = "/bin/sh";
	fargv[findx++] = script_name; 
	fargv[findx++] = NULL ;
		
	fp = popen(cmd,"w");
	if (!fp) {
		fprintf(stderr, "popen() error: %s", strerror(errno));
		goto error_return;
	}
	setbuf(fp,NULL); /* Unbuffered so file is 'immediately' updated */
	
	for (i = 0; ep[i]; ++i) {
	    /* Environment variables which are NOT passed to remote process */
	    static char *eignore[] = {"HOST=","HOSTNAME=","TZ=","SHELL=", 0}; 
	    int ignore;
	    
	    /* Look for and skip certain environment variables */
	    /* We could do this more quickly elsewhere, but ... */ 
	    for (ignore=j=0 ; !ignore && eignore[j] ; j++)
		if (!strncmp(ep[i], eignore[j], strlen(eignore[j])))
		   ignore = 1;
	    if (ignore)
		continue;

	    /* 
	     * Write the environment variable to the remote script file 
	     */
	    if ((strncmp(ep[i],"DISPLAY=unix:",strlen("DISPLAY=unix:"))==0 ||
		 strncmp(ep[i],"DISPLAY=:",    strlen("DISPLAY=:")) == 0) &&
		(dnum = strchr(ep[i], ':')) != NULL)
	    {
		fprintf(fp,"DISPLAY='%s%s';export DISPLAY\n",
							Uts_Name.nodename,dnum);
	    } else {
		int k;
		char evar[256], c;
		char eval[1024];
	
		for (j=0 ; ep[i][j] && (ep[i][j] != '=') ; j++)
			evar[j] = ep[i][j];
		evar[j] = '\0';
		k = j + 1;	/* Skip the '=' sign */
		for (j=0 ; c = ep[i][k] ; k++, j++) {
			if (c == '\'') {		/* ' -> '\'' */
				/* Value contains a double quote */
				eval[j++] = '\'';
				eval[j++] = '\\';
				eval[j++] = '\'';
			} 
			eval[j] = c; 
		}
		eval[j] = '\0';
	        fprintf(fp,"%s='%s'; export %s\n", evar, eval, evar);
	    }
	}

	if (cwd != NULL) 
	    fprintf(fp,"cd %s\n",cwd);

	fprintf(fp,"\n(sleep %d; rm -f %s) &\nexec ",TIMEOUT,script_name);
	for (i = 0; i < ac; ++i) {
	    /* near line 346 the code puts NULL into the last slot */
	    if (av[i] == 0) break;
	    fprintf(fp, "%s ",av[i]);
	}
	fprintf(fp,"\n");
	pclose(fp);
		
	rep = ep;
    }

    /* Set up three pipes */
    if (pipe(in) < 0) {
	fprintf(stderr, "pipe(in) error: %s", strerror(errno));
	goto error_return;
    }
    if (pipe(out) < 0) {
	fprintf(stderr, "pipe(out) error: %s", strerror(errno));
	goto error_return;
    }
    if (pipe(err) < 0) {
	fprintf(stderr, "pipe(err) error: %s", strerror(errno));
	goto error_return;
    }

    child = fork();
    if (child == 0) {
	if (verbose && cwd != NULL) printf ("cd %s\n", cwd); fflush (stdout);
	if (verbose) printf ("exec %s\n", fargv[0]); fflush (stdout);
	if (verbose) for (i = 0; rep[i]; ++i)
	    printf ("envp[%d] = `%s'\n", i, rep[i]);
	if (verbose) for (i = 0; fargv[i]; ++i)
	    printf ("argv[%d] = `%s'\n", i, fargv[i]);
	close (in[1]);
	close (out[0]);
	close (err[0]);
	if (dup2(in[0], 0) < 0) {
	    fprintf(stderr, "dup2() error: %s", strerror(errno));
	    exit(1);
	}
	if (dup2(out[1], 1) < 0) {
	    fprintf(stderr, "dup2() error: %s", strerror(errno));
	    exit(1);
	}
	if (dup2(err[1], 2) < 0) {
	    fprintf(stderr, "dup2() error: %s", strerror(errno));
	    exit(1);
	}
	/* Close all other file descriptors */
	for (i = 3; i < width; ++i)
	    close(i);

	if (cwd != NULL && chdir (cwd) < 0) {
	    fprintf(stderr, "chdir() error: %s", strerror(errno));
	    exit(1);
	}
	if (execve(fargv[0], (EXECVE_2ND_TYPE)fargv, (EXECVE_3RD_TYPE)rep) < 0)
	{
	    fprintf(stderr, "execve() error: %s", strerror(errno));
	    exit(1);
	}
    }
    else if (child > 0) {
	close (in[0]);
	close (out[1]);
	close (err[1]);
	*remin = in[1];
	*remout = out[0];
	*remerr = err[0];
    }
    else {
	goto error_return;
    }


    if (fargv != NULL)
	free ((char*)fargv);
    return (child);

#endif	/*   DXD_LACKS_UTS     */
#ifdef OS2
    if (DXLIsHostLocal(host)) {

#define BuffSize     1000
#define HF_STDIN     0
#define HF_STDOUT    1
#define HF_STDERR    2
        CHAR         LoadError[100];
        CHAR         args[1000];
        PSZ          Envs;
        RESULTCODES  ReturnCodes;
        APIRET       rc;
        PSZ          ptr;
        HFILE        hpR0, hpW0;
        HFILE        hpR1, hpW1;
        HFILE        hpR2, hpW2;
        int          PipeSize=4096;
        int          NRead, TotRead;
        char         Buff[BuffSize];
        HFILE        hfSave0 = -1;
        HFILE        hin = HF_STDIN;
        HFILE        hfSave1 = -1;
        HFILE        hout = HF_STDOUT;
        HFILE        hfSave2 = -1;
        HFILE        herr = HF_STDERR;
        char         exename[255];

        rc=DosDupHandle(hout, &hfSave1);
        rc=DosCreatePipe(&hpR1, &hpW1, PipeSize);
        rc=DosClose(hout);
        rc=DosDupHandle(hpW1, &hout);

        *remout = hpR1;

        if (verbose) printf ("local\n");

        if (user != NULL)
            fprintf (stdout, "Different user on local machine ignored\n");

        strcpy(exename,av[0]);
        for (i=0;i<strlen(exename);i++)
           if (exename[i]=='/')
              exename[i]='\\';
        if (strstr(exename,".cmd") || strstr(exename,".CMD") || !strstr(exename,"."))
          {
            strcpy(cmd,"CMD.EXE");
            strcpy(args,"CMD.EXE");
            ptr = &args[strlen(args)+1];
            strcpy(ptr,"/C ");
            strcat(ptr,exename);
          }
         else
          {
            strcpy(cmd,exename);
            strcpy(args,exename);
            ptr = &args[strlen(args)+1];
            *ptr = '\0';
          }

        for (i=1;i<ac;i++)
          {
            if (av[i] && *av[i])
              {
                strcat(ptr, " ");
                strcat(ptr, av[i]);
              }
          }
        ptr[strlen(ptr)+1]='\0';
        cmd[strlen(cmd)+1]='\0';
        Envs = 0;

        rc = DosSetFHState(hin,  OPEN_FLAGS_NOINHERIT);

        rc = DosExecPgm(LoadError, sizeof(LoadError), EXEC_ASYNC, args, Envs,
                        (PRESULTCODES)&ReturnCodes, cmd);

        rc = DosClose(hout);
        rc = DosDupHandle(hfSave1, &hout);

        child = -1;
        if (rc==0)
          child = ReturnCodes.codeTerminate;
         else
          fprintf(stderr,"Failure to spawn child process");
        return child;
    }
    else
    {
        return (-1);
    }

#endif    /*    OS2    */

#ifdef	DXD_WIN

    char         args[1000];
    char         exename[255];

    char         *Envs;
    int          ReturnCodes, rc, iHostIsLocal, pid;

    HFILE        hpR0, hpW0;
    HFILE        hpR1, hpW1;
    HFILE        hpR2, hpW2;

    int          NRead, TotRead, bTest;
    HFILE        hfSave0 = -1;
    HFILE        hfSave1 = -1;
    HFILE        hfSave2 = -1;

    HFILE        hin  = _fileno(stdin);
    HFILE        hout = _fileno(stdout);
    HFILE        herr = _fileno(stderr);
    DWORD        dwordTmp;

    unsigned long       ThrdTID;
    STARTUPINFO         sInfo;
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pInfo;

    iHostIsLocal = DXLIsHostLocal(host);
    if (verbose)
	printf ("local\n");

    if (user != NULL)
	fprintf (stdout, "Different user on local machine ignored\n");

    strcpy(exename,av[0]);
    for (i=0;i<strlen(exename);i++)
	if (exename[i]=='/')
	    exename[i]='\\';

    if ((strstr(exename,".bat") || strstr(exename,".BAT"))  && iHostIsLocal)
    {
	strcpy(cmd,"command.com /C "); 

	strcat(cmd,exename);
    }
    else
    {
	strcpy(cmd, "");

	if(! iHostIsLocal) {
	    strcat(cmd, "rsh ");
	    strcat(cmd, host);
	    strcat(cmd, " ");
	}

	strcat(cmd,exename);
    }

    for (i=1;i<ac;i++)
    {
	if (av[i] && *av[i])
	{
	    strcat(cmd, " ");
	    strcat(cmd, av[i]);
	}
    }

    Envs = NULL;

    memset(&pInfo, 0, sizeof(pInfo));
    memset(&sInfo, 0, sizeof(sInfo));
    memset(&sa,    0, sizeof(sa));

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);	
    sa.lpSecurityDescriptor = NULL;		
    sa.bInheritHandle = TRUE;			

    bTest = CreatePipe( &hpipeRead,	
			&hpipeWrite,	
			&sa,			
			0 );			

    bTest = DuplicateHandle( GetCurrentProcess( ),
			    hpipeRead,		
			    GetCurrentProcess( ),
			    NULL,			
			    0,
			    FALSE,			
			    DUPLICATE_SAME_ACCESS );

    sInfo.cb = sizeof(sInfo);
    sInfo.dwFlags = STARTF_USESTDHANDLES;
    sInfo.hStdInput = GetStdHandle( STD_INPUT_HANDLE );
    sInfo.hStdOutput = hpipeWrite;
    sInfo.hStdError  = GetStdHandle( STD_ERROR_HANDLE );

    pid = rc = CreateProcess(NULL,
                        cmd,
                        NULL,
                        NULL,
                        TRUE,
                        0,
                        Envs,
                        NULL,	
                        &sInfo,	
                        &pInfo	
		    );
    if(rc == TRUE)  {
	CloseHandle(pInfo.hThread);	
	pid = pInfo.dwProcessId;
	rc = 0;
/*
	bTest = (int) CreateThread(NULL, 0, 
	(LPTHREAD_START_ROUTINE) ClearExecMessages, 
	(LPVOID) hpipeRead, 0, &ThrdTID);
	SetThreadPriority((LPVOID) &ThrdTID, THREAD_PRIORITY_BELOW_NORMAL);
*/
    }
    else
    {
	rc = 1;
	pid = -1;
    }

    *remout = -1;
    child = 0;
    if (rc == 0) 
      child = pid;
    else
      goto error_return;

    return child;

#endif		



error_return:
    sprintf(errstr,"Could not connect using '%s'\n",fargv[0]);
    if (fargv != NULL)
	free ((char*)fargv);
#ifndef DXD_WIN
    return (-1);
#else
    return (0);
#endif
}

