//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/FileStyleHTM.java,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

import java.net.*;
import java.io.*;
import java.util.*;

public class FileStyleHTM extends FileStyleWRAP {
    public FileStyleHTM (String file_name) { 
	super(file_name); 
	extensions = new Vector(2);
	extensions.addElement((Object)"gif");
    }
} // end FileStyleHTML
