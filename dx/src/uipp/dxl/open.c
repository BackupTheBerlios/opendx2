/*  Open Visualization Data Explorer Source File */

DXLError
uiDXLResetServer(DXLConnection *conn)
{
    int sts;
    if (conn->dxuiConnected) {
	DXLEndExecution(conn);
        sts = DXLSend(conn, "reset");
    } else  {
        /*
         *  Be sure we have the executives attention.
         */
	sts = DXLSendImmediate(conn, "sync");
        if (sts) {
	    char buffer[256];

	    /*
	     * Stop an execution, in case one is in progress. 
	     */
	    DXLEndExecution(conn);

	    /*
	     * Clear the executives cache (this is what we are really
 	     * after).
	     */
            sprintf(buffer, "Executive(\"flush cache\");\n");
	    DXLSend(conn,buffer);
	    sts = DXLSendImmediate(conn, "sync");
        } 
    }

    return sts;

}
DXLError
DXLLoadVisualProgram(DXLConnection *conn, const char *file)
{
    int l = strlen(file);
    int sts;
    char *buffer = MALLOC(l + 32);
    if (conn->dxuiConnected) {
        sprintf(buffer, "open network %s", file);
        sts = DXLSend(conn, buffer);
    } else  {
        /*
         * We must sync, before we do the include to be sure that we
         * get a non-zero packet id on subsequent DXLSync() calls.
         * FIXME: Is it sufficient to do a sync only when conn->id == 0 or
         *      to initialize conn->id = 1.
         */
        if (DXLSync(conn)) {
            sprintf(buffer, "include \"%s\"", file);
            sts = DXLSendUnpacketized(conn, buffer);
            /*
             * FIXME: stop the program from executing.
             */
            if (sts)
                DXLSync(conn); /* wait for the program to finish executing */
        } else
            sts = ERROR;

    }

    FREE(buffer);
    return sts;

}

DXLError
exDXLLoadScript(DXLConnection *conn, const char *file)
{
    int l = strlen(file);
    int sts;
    char *buffer = MALLOC(l + 32);
    if (conn->dxuiConnected) {
        sts = ERROR;
    } else  {
#if 11
	DXLLoadVisualProgram(conn,file); 
#else
        /*
         * We must sync, before we do the include to be sure that we
         * get a non-zero packet id on subsequent DXLSync() calls.
         * FIXME: Is it sufficient to do a sync only when conn->id == 0 or
         *      to initialize conn->id = 1.
         */
        if (DXLSync(conn)) {
            sprintf(buffer, "include \"%s\"", file);
            sts = DXLSendUnpacketized(conn, buffer);
            /*
             * FIXME: stop the program from executing.
             */
            if (sts)
                DXLSync(conn); /* wait for the program to finish executing */
        } else
            sts = ERROR;
#endif
    }

    FREE(buffer);
    return sts;

}

/*
 * Load a configuration file.
 * Currently only meaningful when connected to dxui.
 */
DXLError
uiDXLLoadConfig(DXLConnection *conn, const char *file)
{
    int l = strlen(file);
    int sts;

    if (conn->dxuiConnected) {
        char *buffer = MALLOC(l + 50);
        sprintf(buffer, "open config %s", file);
        sts = DXLSend(conn, buffer);
        FREE(buffer);
    } else {
        sts = 0;
    }
    return sts;
}
