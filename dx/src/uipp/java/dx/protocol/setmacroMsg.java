//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/setmacroMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.util.*;

//
// JavaDir,path
//
public class setmacroMsg extends threadMsg {
    private String macro;


    public String getMacroName() { return macro; }
    public void setMacroName(String c) { macro = c; }

    public setmacroMsg() { super(); macro = null; }
    public setmacroMsg(String inputLine) { 
	super(inputLine);
	macro = null;
	try {
	    int comma = inputLine.indexOf((int)',');
	    macro = inputLine.substring(comma+1);
	} catch (Exception e) {
	}
    }

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.setmacroMsg").getName(); }
    public String toString() { 
	return getHeader() + "," + macro;
    }
}
