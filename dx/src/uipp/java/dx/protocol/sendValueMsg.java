//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/sendValueMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.io.*;

//
// JavaDir,path
//
public class sendValueMsg extends threadMsg {
    private String value;

    public sendValueMsg() { 
	super();
	value = null;
    }

    //
    // Don't use StringTokenizer because the value may contain a comma
    //
    public sendValueMsg(String inputLine) { 
	super(inputLine);
	int icomma = inputLine.indexOf(',');
	value = inputLine.substring(icomma+1);
    }

    public void setValue(String value) { this.value = value; }
    public String getValue() { return this.value ; }

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.sendValueMsg").getName(); }
    public String toString() {
	return getHeader() + "," + value;
    }
}
