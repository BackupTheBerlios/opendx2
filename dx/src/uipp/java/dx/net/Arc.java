//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/Arc.java,v 1.1 1999/03/24 15:17:30 gda Exp $
 */

package dx.net;
import java.util.*;

public class Arc extends Object {

    //
    // represent a connection from src_node.output_param_no 
    // to dest_node.input_param_no;
    //
    private int output_param_no;
    private int input_param_no;
    private dx.net.Node src_node;
    private dx.net.Node dest_node;

    public Arc() { 
	super(); 
	this.output_param_no = 0;
	this.input_param_no = 0;
	this.src_node = null;
	this.dest_node = null;
    }

    public Arc(dx.net.Node src, int ono, dx.net.Node dest, int ino) {
	super(); 
	this.output_param_no = ono;
	this.input_param_no = ino;
	this.src_node = src;
	this.dest_node = dest;
    }

    public dx.net.Node getDestinationNode() { return this.dest_node; }
    public dx.net.Node getSourceNode() { return this.src_node; }
    public int getInputParamNumber() { return this.input_param_no; }
    public int getOutputParamNumber() { return this.output_param_no; }

}; // end Arc
