//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/CfgValues.java,v 1.2 1999/05/25 22:12:14 gda Exp $
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


