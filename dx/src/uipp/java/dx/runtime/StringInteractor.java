//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE					    //
//////////////////////////////////////////////////////////////////////////////
package dx.runtime;
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/runtime/StringInteractor.java,v 1.1 1999/03/24 15:17:32 gda Exp $
 */
import java.awt.*;

public class StringInteractor extends Interactor {

    //
    // private member data
    //

    //
    // protected member data
    //

protected String getTypeName() 
{
    return "String";
}

public int getWeightX()
{
    return 1;
}

public void reshape (int x, int y, int w, int h)
{
    if (vertical == 1)
	super.reshape (x,y,w,65);
    else
	super.reshape (x,y,w,h);
}

public int getVerticalFill() { return GridBagConstraints.BOTH; }

public Insets getComponentInsets()
{
    if (vertical == 1)
	return new Insets (0,10,0,10);
    else
	return new Insets (0,0,0,10);
}


} // end class Interactor

