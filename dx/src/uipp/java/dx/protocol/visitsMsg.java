//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/visitsMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.util.*;

//
// JavaDir,path
//
public class visitsMsg extends threadMsg {
    private int visitCnt;

    public visitsMsg() { 
	super();
	visitCnt = 0; 
    }

    public int getVisitCount() { return visitCnt; }
    public void setVisitCount(int c) { visitCnt = c; }

    public visitsMsg(String inputLine) { 
	super(inputLine);
	visitCnt = 0;
	try {
	    StringTokenizer stok = new StringTokenizer(inputLine, ",");
	    String tok = stok.nextToken();
	    tok = stok.nextToken();
	    Integer uc = new Integer(tok);
	    visitCnt = uc.intValue();
	} catch (Exception e) {
	}
    }

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.visitsMsg").getName(); }
    public String toString() { 
	return getHeader() + "," + visitCnt;
    }
}
