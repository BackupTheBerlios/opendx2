//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/CfgValues.java,v 1.1 1999/03/24 15:17:30 gda Exp $
 */

package dx.net;

public class CfgValues extends Object {
    Object interactor;
    int x,y,width,height;

    public CfgValues (Object ntr, int x, int y, int width, int height) {
	super();
	this.interactor = ntr;
	this.x = x;
	this.y = y;
	this.width = width;
	this.height = height;
    }
}; // end CfgValues


