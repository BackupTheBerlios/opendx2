#include <dxconfig.h>
#include <dx/dx.h>
#include "sfile.h"

#if !defined(HAVE_CYGWIN_SOCKET_H) &&  !defined(HAVE_SYS_SOCKET_H) && !defined(HAVE_SOCKET_H) && defined(HAVE_WINSOCK_H)
#define HANDLE_SOCKET
#endif

#if !defined(SOCKET)
#define SOCKET int
#endif

struct sfile
{
    enum 
    {
#if defined(HANDLE_SOCKET)
    	SFILE_SOCKET,
#endif
	SFILE_FDESC,
	SFILE_FPTR
    }			type;
#if defined(HANDLE_SOCKET)
    SOCKET 		socket;
#endif
    int			fd;
    char                buffer[BUFSIZ];
    char                *nextchar;
    FILE                *file;
    int			count;
	int			isAtty;
};

int
SFILEfileno(SFILE *SF)
{
    struct sfile *sf = (struct sfile *)SF;

    if (sf->type == SFILE_FDESC)
	return sf->fd;
    else if (sf->type == SFILE_FPTR)
	return fileno(sf->file);
#if defined(HANDLE_SOCKET)
    else if (sf->type == SFILE_SOCKET)
	return sf->socket;
#endif
    else
    {
	fprintf(stderr, "unknown SFILE type\n");
	abort();
    }
}

SFILE *
socketToSFILE(SOCKET sock)
{
#if !defined(HANDLE_SOCKET)
	return fdToSFILE((int)sock);
#else
   struct sfile *sf = DXAllocate(sizeof(struct sfile));
    if (! sf)
    	return NULL;

    sf->socket 	 = sock;
    sf->type     = SFILE_SOCKET;
    sf->nextchar = NULL;
    sf->count    = 0;
	sf->isAtty	 = 0;

    return (SFILE *)sf;
#endif
}

SFILE *
FILEToSFILE(FILE *fptr)
{
    struct sfile *sf = DXAllocate(sizeof(struct sfile));
    if (! sf)
    	return NULL;

    sf->type     = SFILE_FPTR;
    sf->file	 = fptr;
    sf->fd	 = fileno(fptr);
    sf->nextchar = NULL;
    sf->count    = 0;
	sf->isAtty	 = isatty(fileno(fptr));

    return (SFILE *)sf;
}

SFILE *
fdToSFILE(int fd)
{
    struct sfile *sf = DXAllocate(sizeof(struct sfile));
    if (! sf)
    	return NULL;

    sf->type 	 = SFILE_FDESC;
    sf->fd	 = fd;
    sf->nextchar = NULL;
    sf->count    = 0;
	sf->isAtty	 = isatty(fd);

    return (SFILE *)sf;
}

int
closeSFILE(SFILE *sf)
{
    struct sfile *ssf = (struct sfile *)sf;

#if defined(HANDLE_SOCKET)
    if (ssf->type == SFILE_SOCKET)
    	closesocket(ssf->socket);
    else if (ssf->type == SFILE_FDESC)
        close(ssf->fd);
    else
        fclose(ssf->file);
#else
    if (ssf->type == SFILE_FDESC)
        close(ssf->fd);
    else
        fclose(ssf->file);
#endif

    DXFree((Pointer)ssf);
    return OK;
}

int
readFromSFILE(SFILE *sf, char *buf, int n)
{
    struct sfile *ssf = (struct sfile *)sf;
    int a = 0, b = 0;
    if (ssf->count > 0)
    {
        a = (ssf->count > n) ? n : ssf->count;
	memcpy(buf, ssf->nextchar, a);
	ssf->nextchar += a;
	ssf->count -= a;
	n -= a;
    }
    if (n)
    {
#if defined(HANDLE_SOCKET)
        if (ssf->type == SFILE_SOCKET)
	    b = recv(ssf->socket, buf+a, n, 0);
	else
#endif
		if (ssf->type == SFILE_FPTR)
	        b = fread(buf+a, 1, n, ssf->file);
		else
	        b = read(ssf->fd, buf+a, n);
    }
    return a+b;
}

int
writeToSFILE(SFILE *sf, char *buf, int n)
{
    struct sfile *ssf = (struct sfile *)sf;
#if defined(HANDLE_SOCKET)
    if (ssf->type == SFILE_SOCKET)
	return send(ssf->socket, buf, n, 0);
    else
    {
 	DXSetError(ERROR_INTERNAL, "writeToSFILE on non-socket SFILE?");
	return -1;
    }
#else
    DXSetError(ERROR_INTERNAL, "writeToSFILE on non-socket SFILE?");
    return -1;
#endif
}

extern SFILE *_dxd_exSockFD;

int 
SFILECharReady(SFILE *sf)
{
	int i = 1;
	SFILE *mystdin = stdin;
#if defined(HANDLE_SOCKET)
    struct sfile *ssf = (struct sfile *)sf;

	if (ssf->isAtty)
	{
		int semi, nl, j;
		
		//while(ssf->count > 0 && *ssf->nextchar == 10)
		//{
		//	ssf->count --;
		//	ssf->nextchar --;
		//}

		if (ssf->count == 0)
		{
			ssf->nextchar = ssf->buffer;
			ssf->buffer[0] = '\0';
		}

		for (semi = nl = j = 0; j < ssf->count; j++)
		{
			if (ssf->nextchar[j] == ';') 
				semi ++;
			else if (semi && ssf->nextchar[j] == (char)10)
				nl ++;
		}

		i = 0;
		if (semi && nl)
			i = 1;
		else
		{
			while (kbhit())
			{
				int c = getche();
				if (c == 8)
				{
					if (ssf->count > 0) 
					{
						ssf->count --;
						ssf->nextchar[ssf->count] = '\0';
						putch(' ');
						putch(8);
					}
				}
				else 
				{
					if (c == ';')
					{
						semi ++;
					}
					else if (c == '\r')
					{
						i = 1;
						c = 10;
						putch(10);
					}

					ssf->nextchar[ssf->count++] = c;
					ssf->nextchar[ssf->count] = '\0';
				}
			}
		}
	}
	else if (ssf == _dxd_exSockFD)
	{
		if (ssf->count == 0)
		{
			struct timeval tv = {0, 0};  
			fd_set fds;
			FD_ZERO(&fds);
			FD_SET(ssf->socket, &fds);
			select(1, &fds, NULL, NULL, &tv);
			i = FD_ISSET(ssf->socket, &fds);
		}
	}
#endif

	return i;
}

int
SFILEGetChar(SFILE *sf)
{
    int s;
    struct sfile *ssf = (struct sfile *)sf;
    if (ssf->count == 0)
    {
#if defined(HANDLE_SOCKET)
	if (ssf->type == SFILE_SOCKET)
	    ssf->count = recv(ssf->socket, ssf->buffer, BUFSIZ, 0);
	else 
#endif
	if (ssf->type == SFILE_FPTR)
	{
#if defined(intelnt)
		if (ssf->file == stdin)
			return ';';
		else
#endif
			ssf->count = fread(ssf->buffer, 1, BUFSIZ, ssf->file);
	}
	else if (ssf->type == SFILE_FPTR)
	{
#if defined(intelnt)
		if (ssf->fd == fileno(stdin))
			return _getche();
		else
#endif
	    ssf->count = read(ssf->fd, ssf->buffer, BUFSIZ);
	}

	ssf->nextchar = ssf->buffer;

	if (ssf->count <= 0)
	    return EOF;
    }

    ssf->count --;
    s = (int)(*ssf->nextchar ++);
    return s;
}

int
SFILEIoctl(SFILE *sf, int cmd, void *argp)
{
    struct sfile *ssf = (struct sfile *)sf;
#if defined(HANDLE_SOCKET)
    if (ssf->type == SFILE_SOCKET)
	return ioctlsocket(ssf->socket, cmd, argp);
    else
    {
	DXSetError(ERROR_INTERNAL, "IOCTL on non-socket SFILE?");
	return ERROR;
    }
#else
    DXSetError(ERROR_INTERNAL, "IOCTL on non-socket SFILE?");
    return ERROR;
#endif
}
