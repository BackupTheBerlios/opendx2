//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/NumericValues.java,v 1.1 1999/03/24 15:17:31 gda Exp $
 */

package dx.net;

public class NumericValues extends Object {
    int which;
    int places;
    double min, max, step, current;

    public NumericValues (int which, double min, double max, 
	double step, int places, double current) {
	super();
	this.which = which;
	this.min = min;
	this.max = max;
	this.step = step;
	this.current = current;
	this.places = places;
    }

    public NumericValues (int which, int min, int max, int step, int current) {
	super();
	this.which = which;
	this.min = min;
	this.max = max;
	this.step = step;
	this.current = current;
	this.places = 0;
    }
}; // end NumericValues


