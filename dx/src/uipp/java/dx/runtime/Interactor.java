//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE					    //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/runtime/Interactor.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */
package dx.runtime;
import dx.net.PacketIF;
import dx.net.DXLinkApplication;
import java.awt.*;
import java.applet.*;

public class Interactor extends Panel {

    //
    // private member data
    //
    private LabelGroup label = null;
    private int developer = 1;
    private int label_lines = 1;
    private GridBagLayout gbl;
    private boolean requires_quotes = true;

    //
    // protected member data
    //
    protected int vertical = 1;
    protected Component ipart = null;
    protected int instance_number;
    protected dx.net.PacketIF node = null;

    public void setNode(PacketIF node) { this.node = node; }
    public PacketIF getNode() { return this.node; }

public void setInstanceNumber(int instnum) { this.instance_number = instnum; }
public int  getInstanceNumber() { return this.instance_number; }

public boolean action (Event e, Object o)
{
    if (e.target == ipart) {
	PacketIF pif = this.getNode();
	pif.setOutputValue(getValue());
	return true;
    }
    return false;
}

//
// By default we'll create a text widget for the interactor.  This should
// probably be a virtual method, but there will be so may interactors for
// which there is no java translation that we want to be able to use
// a plain text widget by default
//
protected void createPart() {
    ipart = new TextField("", 15);
    if (this.developer == 1) {
	ipart.setBackground(Color.white);
	ipart.setForeground(Color.black);
    }
}

public void setLabelLines(int lines)
{
    label_lines = lines;
}

public void setStyle (int dev)
{
    developer = dev;
}

public int getStyle()
{
    return developer;
}


//
//
//
public Component getComponent() {
    return ipart;
}

//
//
//
protected String getTypeName() {
    return "Value";
}

//
// If the subclass supplies a createPart method then it must supply a getValue also
//
public String getValue()
{
    TextField tf = (TextField)ipart;
    if (requires_quotes) return "\"" + tf.getText() + "\"";
    else return tf.getText();
}

public void setUseQuotes(boolean usem)
{
    requires_quotes = usem;
}

//
// If the subclass supplies a createPart method then it must supply a setValue also
//
public void setValue(String s)
{
    TextField tf = (TextField)ipart;
    tf.setText(s);
}

//
//
//
protected void addComponent (Component comp, int x, int y, int w, int h, 
    int fill, int anchor)
{
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.gridx = x;
    gbc.gridy = y;
    gbc.gridwidth = w;
    gbc.gridheight = h;
    gbc.fill = fill;
    gbc.anchor = anchor;
    gbc.ipadx = 0;
    gbc.ipady = 0;
    if (comp == (Component)label) {
	gbc.weightx = 0;
	gbc.weighty = 0;
	gbc.insets = getLabelInsets();
    } else {
	gbc.weightx = getWeightX();
	gbc.weighty = getWeightY();
	gbc.insets = getComponentInsets();
    }
    gbl.setConstraints(comp, gbc);
    add(comp);
}

public Insets getLabelInsets()
{
    if (vertical == 1)
	return new Insets (1,0,0,0);
    else
	return new Insets (1,1,1,0);
}

public Insets getComponentInsets()
{
    if (vertical == 1)
	return new Insets (0,0,3,0);
    else
	return new Insets (2,0,2,2);
}

public int getWeightY()
{
    return 0;
}

public int getWeightX()
{
    return 0;
}

//
//
//
public void init() 
{
    gbl = new GridBagLayout();
    setLayout(gbl);

    if (developer == 1) {
	setBackground(new Color(0x5f, 0x9e, 0xa0));
	setForeground(Color.white);
    }

    try {
	if (label_lines > 0) {
	    if (label == null)
		label = new LabelGroup(label_lines);
	    label.setFont(new Font("Helvetica", Font.BOLD, 12));
	    label.init();

	    if (developer == 1) {
		label.setBackground(new Color(0x5f, 0x9e, 0xa0));
		label.setForeground(Color.white);
	    }

	    if (vertical == 1) {
		label.setAlignment(Label.CENTER);
		addComponent(label, 0,0,1,1, 
		    GridBagConstraints.VERTICAL,
		    GridBagConstraints.CENTER); 
	    } else {
		label.setAlignment(Label.LEFT);
		addComponent(label, 0,1,1,1, 
		    GridBagConstraints.HORIZONTAL,
		    GridBagConstraints.WEST);
	    }
	}

	createPart();
	ipart.setFont(new Font("Helvetica", Font.BOLD, 12));
	if (developer == 1) {
	    ipart.setBackground(new Color(0x5f, 0x9e, 0xa0));
	    //ipart.setForeground(Color.white);
	}

	if (vertical == 1) {
	    int fill_rule = this.getVerticalFill();
	    addComponent (ipart, 0,1,1,1, fill_rule, GridBagConstraints.CENTER);
	} else {
	    addComponent (ipart, 1,1,1,1, 
		GridBagConstraints.HORIZONTAL,
		GridBagConstraints.EAST);
	}

    } catch (Exception e) {
	e.printStackTrace();
    }
}

public int getVerticalFill() { return GridBagConstraints.VERTICAL; }

//
//
//
public void setLabel (String s) 
{
    if (label == null)
	label = new LabelGroup(label_lines);
    label.setText(s);
}

//
//
//
public void setVertical () 
{
    vertical = 1;
}

//
//
//
public void setHorizontal () 
{
    vertical = 0;
}

//
// Add shadowThickness
//
public void paint(Graphics g)
{
    if (developer == 0)
	return ;

    Dimension d = size();
    int w = d.width-1;
    int h = d.height-1;
    Color bg = getBackground();
    g.setColor(bg);
    g.draw3DRect (0,0,w,h,true);
}


} // end class Interactor

