//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/server/serverMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol.server;
import dx.protocol.*;
import java.net.*;
import java.io.*;

public abstract class serverMsg extends message {
   public String getCommand() { return this.getClass().getName(); }
   public String toString() { return getHeader(); }
   public serverMsg() { super(); }
   public serverMsg(String inputLine) { super(inputLine); }
}
