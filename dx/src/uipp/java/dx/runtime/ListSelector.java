//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE					    //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/runtime/ListSelector.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */
package dx.runtime;
import java.awt.*;
import dx.net.PacketIF;

public class ListSelector extends Selector {

    //
    // private member data
    //
    private boolean mode = false;

    //
    // protected member data
    //
    protected Color local_bg = null;

public int getVerticalFill() { return GridBagConstraints.BOTH; }

public boolean handleEvent (Event e)
{
    if ((e.target == ipart) && 
	((e.id == Event.LIST_SELECT) || (e.id == Event.LIST_DESELECT))) {
	PacketIF pif = this.getNode();
	pif.setOutputValues (this.getOutputValue(), this.getOutput2Value());
        return true;
    } else
	return super.handleEvent(e);
}


//
// Defaults to single selection list
//
protected void createPart() {
    List ch = new List();
    if (this.local_bg != null)
	ch.setBackground(this.local_bg);
    ipart = ch;
    if (mode) ch.setMultipleSelections(true);
}

public void newItem(int i, String name)
{
    List ch = (List)ipart;
    ch.addItem(name);
}

public void clearOptions()
{
    List ch = (List)ipart;
    ch.clear();
}

public void setMode(boolean multi)
{
    List ch = (List)ipart;
    if (ch != null)
	ch.setMultipleSelections(multi);
    mode = multi;
    if (multi == true) {
	int t = getOutputType();
	t|= BinaryInstance.LIST;
	setOutputType(t);
    }
}

public void selectOption(int i)
{
    List ch = (List)ipart;
    ch.select(i-1);
}

public int getWeightY()
{
    return 1;
}

public int getWeightX()
{
    return 1;
}

public boolean isOptionSelected(int i)
{
    int ndx = i-1;
    List ch = (List)ipart;
    return ch.isSelected(ndx);
}

public void setBackground(Color newc) {
    super.setBackground(newc);
    local_bg = newc;
    List ch = (List)ipart;
    if (ch != null) ch.setBackground(newc);
}

public Insets getComponentInsets()
{
    if (vertical == 1)
	return new Insets (10,10,16,10);
    else
	return new Insets (10,10,10,10);
}


} // end class Interactor

