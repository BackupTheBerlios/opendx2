/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef	__REMOTE_H
#define	__REMOTE_H

#include <dxconfig.h>


#include "utils.h"

#define OBPORT		1910

#define	REMOTE_NAME	"[Remote]"
#define	REMOTE_SPECIAL	4
#define	REMOTE_NIN	20
#define	REMOTE_NOUT	10

Error _dxfExRemote (Object *in, Object *out);

/* one struct per outboard socket */
typedef struct obinfo {
    int fd;                /* socket file descriptor */
    char *modid;           /* cpath to module */
    int async_handler;     /* set if an RIH is already installed */
    int deleted;           /* set if we notice the socket has closed */
} ObInfo;

#endif
