/*  Open Visualization Data Explorer Source File */

    DXLConnection* conn = this->gcw->getConnection();

    char net_file[512];
    const char *net_dir = theGARApplication->getResourcesNetDir();
    sprintf (net_file, "%s/ui/ReadImage.net", net_dir);

    Widget wid;
    XtVaGetValues (this->format_om, XmNmenuHistory, &wid, NULL);
    if (!wid) return FALSE;

    char *args[4];
    args[0] = "_filename_";
    args[1] = DuplicateString (this->gcw->getDataFilename());
    args[2] = "_image_format_";
    args[3] = XtName(wid);
    this->gcw->loadAndSet (conn, net_file, args, 4);
    delete args[1];

    this->hideList();
    DXLExecuteOnce (conn);

    return TRUE;
}


//
// file_checked means that the caller has looked for the file and found
// that is exists.
//
void ImageChoice::setCommandActivation(boolean file_checked)
{
    this->NonimportableChoice::setCommandActivation(file_checked);


    boolean file_ready = FALSE;

    //
    // Does the text widget at the top contain a valid data file name?
    //
    const char *cp = this->gcw->getDataFilename();
    const char *file_name = NUL(char*);
    if ((cp) && (cp[0]))
	file_name = theGARApplication->resolvePathName(cp, this->getFileExtension());

    int name_len = 0;
    if (file_name)
	name_len = strlen(file_name);

    if (name_len) {
	char* fname = DuplicateString(file_name);

	int i = name_len - 1;
	while ((i>=0) && (fname[i] != '.')) i--;
	const char* ext = &fname[i];

	i++;
	while (i<name_len) {
	    fname[i] = toupper(fname[i]);
	    i++;
	}

	i = 0;
	while (ImageChoice::FormatNames[i]) {
	    XtPointer ud;
	    XtVaGetValues (this->format_widget[i], XmNuserData, &ud, NULL);
	    char* cp = (char*)ud;
	    if (EqualString(ext, cp)) {
		XtVaSetValues (this->format_om, 
		    XmNmenuHistory, this->format_widget[i],
		NULL);
		break;
	    }
	    i++;
	}
	delete fname;
    }
}


boolean ImageChoice::canHandle(const char* ext)
{
    int i = 0;
    while (ImageChoice::FormatNames[i]) {
	XtPointer ud;
	XtVaGetValues (this->format_widget[i], XmNuserData, &ud, NULL);
	char* cp = (char*)ud;
	if (EqualString(ext, cp)) return TRUE;
	i++;
    }
    return FALSE;
}
