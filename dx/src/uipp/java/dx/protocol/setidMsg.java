//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/setidMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.util.*;

//
// JavaDir,path
//
public class setidMsg extends threadMsg {
    private int javaid;
    private String output_dir;
    private String output_url;

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.setidMsg").getName(); }
    public void setJavaId(int j) { javaid = j; }
    public int getJavaId() { return javaid; }
    public String getOutputUrl() { return this.output_url; }
    public String getOutputDir() { return this.output_dir; }

    public setidMsg() { 
	super(); 
	javaid = 0; 
	output_dir = null;
	output_url = null;
    }

    public void setOutputDir(String dir) { this.output_dir = dir; }
    public void setOutputUrl(String url) { this.output_url = url; }

    public setidMsg(String inputLine) { 
	super(inputLine);
	try {
	    StringTokenizer stok = new StringTokenizer(inputLine, ":");
	    String tok = stok.nextToken();
	    tok = stok.nextToken();
	    StringTokenizer ctok = new StringTokenizer(tok, ",");
	    tok = ctok.nextToken();
	    tok = ctok.nextToken();
	    Integer jidi = new Integer(tok);
	    javaid = jidi.intValue();
	    output_dir = ctok.nextToken();
	    output_url = ctok.nextToken();
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }

    public String toString() {
	return getHeader() + "," + javaid + "," + output_dir + "," + output_url;
    }
}
