//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE					    //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/runtime/Separator.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */
package dx.runtime;
import java.awt.*;

public class Separator extends Canvas {

    //
    // private member data
    //


    //
    // protected member data
    //
    protected int horizontal = 1;
    protected Color local_color = null;

public void setForeground(Color c)
{
    super.setForeground(c);
    local_color = c;
}

//
//
//
public void setVertical () 
{
    horizontal = 0;
}

//
//
//
public void setHorizontal () 
{
    horizontal = 1;
}

//
// Add shadowThickness
//
public void paint(Graphics g)
{
    Dimension d = size();
    Color bg;
    if (local_color == null)
	bg = getBackground();
    else
	bg = local_color;
    g.setColor(bg);
    int w = d.width-1;
    int h = d.height-1;
    if (horizontal == 1)
	h=3;
    else
	w=3;
    g.draw3DRect (0,0,w,h,false);

}


} // end class Separator

