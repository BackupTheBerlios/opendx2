//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE					    //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/runtime/LabelGroup.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */
package dx.runtime;
import java.awt.*;

//
// Provide behavior similar to a Motif Label widget: support multi
// line labels which java labels don't seem to be able to do.
//

public class LabelGroup extends Panel {
    //
    // private
    //
    private int label_count;
    private int next;
    private Object[] label_array;
    private String[] string_array;
    private Font local_font;
    private Color local_fg;
    private Color local_bg;
    private int local_alignment;
    private boolean initialized;

public LabelGroup(int count)
{
    label_count = count;
    label_array = new Object[label_count];
    string_array = new String[label_count];
    next = 0;
    local_font = null;
    local_fg = null;
    local_bg = null;
    local_alignment = Label.CENTER;
    initialized = false;
}

public void setFont(Font newf)
{
    if (initialized == true) {
	int i;
	for (i=0; i<next; i++) {
	    Label lab = (Label)label_array[i];
	    lab.setFont(newf);
	}
    }
    local_font = newf;
}

public void setAlignment(int align)
{
    if (initialized == true) {
	int i;
	for (i=0; i<next; i++) {
	    Label lab = (Label)label_array[i];
	    lab.setAlignment(align);
	}
    }
    local_alignment = align;
}

public void setBackground (Color newc)
{
    if (initialized == true) {
	int i;
	for (i=0; i<next; i++) {
	    Label lab = (Label)label_array[i];
	    lab.setBackground(newc);
	}
    }
    local_bg = newc;
    super.setBackground(newc);
}

public void setForeground (Color newc)
{
    if (initialized == true) {
	int i;
	for (i=0; i<next; i++) {
	    Label lab = (Label)label_array[i];
	    lab.setBackground(newc);
	}
    }
    local_fg = newc;
    super.setForeground(newc);
}

public void setText (String txt)
{
    if (next == label_count) return ;

    if (initialized == false) {
	string_array[next] = txt;
    } else {
	Label lab = (Label)label_array[next];
	lab.setText(txt);
    }
    next++;
}

//
//
//
public void init() 
{
    GridLayout gbl = new GridLayout(label_count, 1, 0, -6);
    setLayout(gbl);

    try {
	int i;
	for (i=0; i<label_count; i++) {
	    Label lab = new Label();
	    lab.setAlignment (local_alignment);
	    if (i < next) {
		lab.setText(string_array[i]);
	    } else {
		lab.setText("stringy");
	    }
	    if (local_fg != null) lab.setForeground(local_fg);
	    if (local_bg != null) lab.setBackground(local_bg);
	    if (local_font != null) lab.setFont (local_font);

	    add(lab);
	    label_array[i] = (Object)lab;
	}
    } catch (Exception e) {
	e.printStackTrace();
    }
    //validate();
}


} // end class Interactor

