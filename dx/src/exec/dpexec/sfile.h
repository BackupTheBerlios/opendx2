/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _SFILE_H
#define _SFILE_H

typedef void SFILE;

#if !defined(HAVE_CYGWIN_SOCKET_H) &&  !defined(HAVE_SYS_SOCKET_H) && !defined(HAVE_SOCKET_H) && defined(HAVE_WINSOCK_H)
#define HANDLE_SOCKET
SFILE *socketToSFILE(SOCKET sock);
#endif

#if !defined(SOCKET)
#define SOCKET int
#endif

SFILE *socketToSFILE(SOCKET);

SFILE *fdToSFILE(int fd);
SFILE *FILEToSFILE(FILE *fptr);
int    readFromSFILE(SFILE *sf, char *buf, int n);
int    writeToSFILE(SFILE *sf, char *buf, int n);
int    closeSFILE(SFILE *sf);
int    SFILECharReady(SFILE *sf);
int    SFILEGetChar(SFILE *sf);
int    SFILEIoctl(SFILE *sf, int cmd, void *argp);
int    SFILEfileno(SFILE *sf);

#endif /* _SFILE_H */
