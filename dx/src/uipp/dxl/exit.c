/*  Open Visualization Data Explorer Source File */

    DXLSetSynchronization(conn,0);

    sts = DXLSend(conn, cmd);

    FD_ZERO(&fds);
    FD_SET(conn->fd, &fds);
    to.tv_sec = 0;
    to.tv_usec = 0;
#ifdef DXD_HAS_WINSOCKETS
    select(width, &fds, NULL, NULL, NULL);
#else
#ifndef OS2
    /* this will set retval even though we don't need it here */
    SELECT_INTR(width, (SELECT_ARG_TYPE)&fds, NULL, NULL, NULL, retval);
#else
    select(&conn->fd, 1, 0, 0, -1);
#endif
#endif

    DXLCloseConnection(conn);

    return sts;
}

