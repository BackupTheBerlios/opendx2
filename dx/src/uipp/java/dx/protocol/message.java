//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/protocol/message.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */

package dx.protocol;
import java.net.*;
import java.util.*;

public abstract class message {
    private static int next_id = 1;
    protected synchronized static int NextPacketId() { return next_id++; }

    protected int packet_id;

    public int getPacketId() { return this.packet_id; }
    protected String getHeader() { return this.getCommand() + ":" + this.packet_id; }

    public abstract String toString();
    public abstract String getCommand();

    protected message() {  
	packet_id = NextPacketId();
    }
    protected message(String inputLine){ 
	StringTokenizer stok = new StringTokenizer (inputLine, ",:");
	stok.nextToken();
	String pno = stok.nextToken();
	Integer pnoi = new Integer(pno);
	packet_id = pnoi.intValue();
    }

    protected final static int MajorVersion = 2;
    protected final static int MinorVersion = 0;
    protected final static int MicroVersion = 0;
    protected final static String version_string =
	MajorVersion + "." + MinorVersion + "." + MicroVersion;
}
