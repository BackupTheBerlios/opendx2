//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/BinaryNode.java,v 1.2 1999/05/25 22:12:14 gda Exp $
 */

package dx.net;
import java.util.*;
import dx.runtime.*;

public class BinaryNode extends dx.net.InteractorNode {

    private int second_param_number;

    public BinaryNode(Network net, String name, int instance, String notation) {
	super(net, name, instance, notation);
	this.second_param_number = 2;
    }

    public void setParameterNumber(int p, int q) {
	super.setParameterNumber(p);
	this.second_param_number = q;
    }

    public int getExtraParameterNumber() { return this.second_param_number; }
    public void setOutputValues (String name, String value) {
	Network net = this.getNetwork();
	DXLinkApplication dxa = (DXLinkApplication)net.getApplet();
	boolean resume = dxa.getEocMode();
	if (resume) dxa.setEocMode(false);
	this.setOutputValue (name);
	this.setOutputValue (this.getExtraParameterNumber(), value);
	if (resume)
	    dxa.setEocMode(true);
    }

}; // end BinaryNode
