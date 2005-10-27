//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE         //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/runtime/Selector.java,v 1.2 2005/10/27 19:43:08 davidt Exp $
 */
package dx.runtime;
import java.awt.*;
import dx.net.PacketIF;
import java.lang.reflect.*;
//
//
//
//
//

public class Selector extends BinaryInstance
{

    //
    // private member data
    //

    //
    // protected member data
    //
    protected boolean selected[];
    protected boolean singleItemSelectable()
    {
        return false;
    }

    public boolean action ( Event e, Object o )
    {
        if ( ( e.target == ipart ) && ( e.target instanceof Choice ) ) {
            PacketIF pif = getNode();
            pif.setOutputValues( this.getOutputValue(), this.getOutput2Value() );
            return true;
        }

        return false;
    }

    protected void createPart()
    {
        ipart = new Choice();
    }

    protected void newItem ( int i, String name )
    {
        Choice ch = ( Choice ) ipart;
        ch.addItem( name );
    }

    public void clearOptions()
    {
        Choice ch = ( Choice ) ipart;

        //
        // Ouch. Don't try to provide data-drivenness in a OptionMenu-styl
        // selector interactor running inside netscape because the applet
        // will crash and there's no way to catch the error.
        // When I discovered this, I.E. claimed to be at java 1.1.  Netscape
        // claimed java 1.1.2.  This was I.E. 4.0 and Netscape 4.04
        //
        // ...update: Netscape 4.06 works it claims 45.3 and 1.1.5
        //
        String vendor = System.getProperty( "java.vendor" );
        String classver = System.getProperty( "java.class.version" );
        String javaver = System.getProperty( "java.version" );

        if ( ( vendor != null ) && ( classver != null ) && ( javaver != null ) ) {
            if ( vendor.startsWith( "Netscape" ) ) {
                if ( ( classver.startsWith( "45.3" ) ) && ( javaver.startsWith( "1.1.5" ) ) ) {
                    /* keep going because it's Netscape 4.06 */
                }

                else {
                    return ;
                }
            }
        }

        try {
            int length = ch.getItemCount();
            int i;

            for ( i = length - 1; i >= 0; i-- )
                ch.remove( i );
        }

        catch ( Exception nsme ) {
            nsme.printStackTrace();
            System.out.println
            ( "SelectorInteractor error: Your Java implementation is pre 1.1" );
            System.out.println
            ( "    Data-driven OptionMenu-style SelectorInteractors aren't available." );
            System.out.println
            ( "    Try using ScrolledList-style instead." );
        }
    }

    //
    //
    //
    protected String getTypeName()
    {
        return "Selector";
    }

    //
    // If the subclass supplies a createPart method then it must supply a getValue also
    //
    public String getValue()
    {
        return getOutputValue();
    }

    //
    // If the subclass supplies a createPart method then it must supply a setValue also
    //
    // There is no way to implement this without DXType and DXValue
    //
    public void setValue( String s )
    {}

    public void selectOption( int i )
    {
        Choice ch = ( Choice ) ipart;
        ch.select( i - 1 );
    }


    public boolean isOptionSelected( int i )
    {
        int ndx = i - 1;
        Choice ch = ( Choice ) ipart;

        if ( ndx == ch.getSelectedIndex() )
            return true;
        else
            return false;
    }

    public void setEnabled( boolean tf )
    {
        super.setEnabled( true );

        if ( this.isEnabled() == true ) {
            if ( ( this.getOptionCount() < 2 ) && ( this.singleItemSelectable() == false ) )
                setEnabled( false );
        }
    }

} // end class Selector

