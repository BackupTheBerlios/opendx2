//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/doneMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.io.*;

//
// JavaDir,path
//
public class doneMsg extends threadMsg {

    public static String GetCommand() throws ClassNotFoundException
	   { return Class.forName("dx.protocol.doneMsg").getName(); }
    public doneMsg() { super(); }
    public doneMsg(String inputLine) { super(inputLine); }
}
