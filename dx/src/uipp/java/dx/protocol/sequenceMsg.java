//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/sequenceMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.io.*;
import java.util.*;

//
// JavaDir,path
//
public class sequenceMsg extends threadMsg {
    int action;
    public int getAction() { return this.action; }
    public void setAction(int action) { this.action = action; }
    public sequenceMsg() { super(); this.action = 0; }
    public sequenceMsg(int action) { super(); this.action = action; }
    public sequenceMsg(String inputLine) { 
	super(inputLine); 
	try {
	    String hdr = this.getHeader();
	    String data_str = inputLine.substring(hdr.length()+1);
	    StringTokenizer stok = new StringTokenizer(data_str, ",");
	    String actionid = stok.nextToken();
	    this.action = new Integer(actionid).intValue();
	} catch (Exception e) {
	    this.action = 0;
	}
    }
    public String toString() { return getHeader() + "," + action; }
    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.sequenceMsg").getName(); }
}
