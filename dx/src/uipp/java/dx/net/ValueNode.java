//

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/ValueNode.java,v 1.3 1999/07/09 19:30:00 daniel Exp $
 */

package dx.net;
import java.util.*;
import dx.runtime.*;

public class ValueNode extends dx.net.InteractorNode {

    private String value ;

    public ValueNode(Network net, String name, int instance, String notation) {
	super(net, name, instance, notation);
	this.value = null;
    }

    public synchronized void setValue (String value) {
	this.value = value;
    }

    public void installValues (Interactor i) {
	super.installValues(i);
	if (this.value == null) return ;
	i.setValue(this.value);
    }

}; // end ValueNode
