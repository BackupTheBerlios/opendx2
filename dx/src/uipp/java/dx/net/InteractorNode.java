//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/InteractorNode.java,v 1.1 1999/03/24 15:17:31 gda Exp $
 */

package dx.net;
import java.util.*;
import dx.runtime.*;

public abstract class InteractorNode extends dx.net.DrivenNode {

    private Vector cfgValues;
    protected Vector interactors;

    public InteractorNode(Network net, String name, int instance, String notation) {
	super(net, name, instance, notation);
	this.interactors = null;
    }

    public void addInteractor(Interactor i) {
	if (this.interactors == null) 
	    this.interactors = new Vector(2);
	this.interactors.addElement((Object)i);
	i.setNode(this);
    }

    public void reshape (Interactor i, int x, int y, int width, int height) {
	if (this.cfgValues == null)
	    this.cfgValues = new Vector(2);
	CfgValues cfg = new CfgValues (i, x,y,width,height);
	this.cfgValues.addElement((Object)cfg);
    }

    public void installValues (Interactor i) {
	if (this.cfgValues == null) return ;
	Enumeration enum = this.cfgValues.elements();
	while (enum.hasMoreElements()) {
	    CfgValues cfg = (CfgValues)enum.nextElement();
	    if (i != cfg.interactor) continue;

	    i.reshape(cfg.x, cfg.y, cfg.width, cfg.height);
	}
    }

    protected boolean needsSpacesReplaced() { return true; }
    public void handleMessage (String msg) {
	super.handleMessage(msg);
	this.cfgValues = null;
	if (this.interactors == null) 
	    return ;

	Enumeration enum = this.interactors.elements();
	while (enum.hasMoreElements()) {
	    Interactor i = (Interactor)enum.nextElement();
	    this.installValues(i);
	}
    }

}; // end InteractorNode
