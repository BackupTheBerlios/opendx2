//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/uptimeMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.util.*;

//
// JavaDir,path
//
public class uptimeMsg extends threadMsg {
    private String uptime;


    public String getUpTime() { return uptime; }
    public void setUpTime(String c) { uptime = c; }

    public uptimeMsg() { super(); uptime = null; }
    public uptimeMsg(String inputLine) { 
	super(inputLine);
	uptime = null;
	try {
	    StringTokenizer stok = new StringTokenizer(inputLine, ",");
	    String tok = stok.nextToken();
	    uptime = stok.nextToken();
	} catch (Exception e) {
	}
    }

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.uptimeMsg").getName(); }
    public String toString() { 
	return getHeader() + "," + uptime;
    }
}
