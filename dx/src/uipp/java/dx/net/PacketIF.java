//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/PacketIF.java,v 1.1 1999/03/24 15:17:31 gda Exp $
 */
package dx.net;

public interface PacketIF {
    public void setInputValue (int param, String value);
    public void setOutputValue (String value);
    public void setOutputValues (String name, String value);
    public void handleMessage (String msg);
};

