//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/DrivenNode.java,v 1.1 1999/03/24 15:17:31 gda Exp $
 */

package dx.net;
import java.util.*;

public class DrivenNode extends dx.net.Node {

    public DrivenNode(Network net, String name, int instance, String notation) {
	super(net, name, instance, notation);
    }

    public String getMatchString() { return getName() + "_" + this.getInstanceNumber(); }

    public void installHandlers() { 
	registerHandler(this.getMatchString()); 
	registerHandler("ECHO:  " + this.getMatchString()); 
	registerHandler(" 0:  " + this.getMatchString()); 
	registerHandler(" 0:  ECHO:  " + this.getMatchString()); 
    }


    protected String mungeString(String s) { return s.replace(' ', ';'); }
    protected boolean needsSpacesReplaced() { return false; }

    public void handleMessage (String msg) {
	String pkt = msg;
	if (this.needsSpacesReplaced()) {
	    try {
		//
		// pc modules don't prepend " 0: " before their messages.
		//
		StringTokenizer stok = new StringTokenizer(msg, ":");
		String tok = stok.nextToken();
		tok = stok.nextToken();
		if (stok.hasMoreTokens())
		    tok = stok.nextToken();
		pkt = this.mungeString(tok);
		stok = null;
		tok = null;
	    } catch (Exception e) {
		e.printStackTrace();
	    }
	}
	super.handleMessage(pkt);
    }


}; // end DrivenNode
