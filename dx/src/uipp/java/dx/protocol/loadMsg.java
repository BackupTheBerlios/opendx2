//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/loadMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.io.*;

//
// LOAD,foobar.net
//
public class loadMsg extends threadMsg {
    private String program;

    public loadMsg() { super(); program = null; }

    public loadMsg(String inputLine) {
	super(inputLine);
	int icomma = inputLine.indexOf(',');
	program = inputLine.substring(icomma+1);
    }

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.loadMsg").getName(); }
    public String toString() {
	return getHeader() + "," + program;
    }

    public void setProgram(String program) { this.program = program; }
    public String getProgram() { return program; }
}
