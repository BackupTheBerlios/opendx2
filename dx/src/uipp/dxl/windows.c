/*  Open Visualization Data Explorer Source File */


    sprintf(buf, "render-mode %s title=%s",mode,title);
    printf("%s\n",buf);
    return DXLSend(conn, buf);
}
