//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/FileStyleWRAP.java,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

import java.net.*;
import java.io.*;
import java.util.*;


public class FileStyleWRAP extends FileStyle {
    protected Vector extensions;
    protected String base_name;
    protected FileStyleWRAP (String file_name) { 
	super(file_name); 
	int extid = file_name.lastIndexOf((int)'.');
	base_name = file_name.substring(0, extid);
    }
    public void delete() {
	super.delete();
	//
	// Delete the associated file(s)
	//
	Enumeration enum = extensions.elements();
	while (enum.hasMoreElements()) {
	    String ext = (String)enum.nextElement();
	    String path = base_name + "." + ext;
	    File df = new File(path);
	    if (df.exists()) df.delete();
	}
    }
} // end FileStyleWRAP
