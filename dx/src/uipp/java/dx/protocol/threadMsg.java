//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/threadMsg.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.io.*;

public abstract class threadMsg extends message {
    public String getCommand() { return getClass().getName(); }
    protected threadMsg() { super(); }
    public String toString() { return getHeader(); }
    protected threadMsg(String inputLine) { super(inputLine); }
}
