//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE					    //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/client/DXClientThread.java,v 1.1 1999/03/24 15:17:30 gda Exp $
 */


package dx.client;
import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;
import java.applet.*;
import dx.protocol.*;

public abstract class DXClientThread extends Thread {
    private boolean failed;

    protected DataInputStream inputStream;
    protected DXClient parent;
    protected Vector actions;

    public final static int SHOWDOC = 1;
    public final static int MESSAGE = 2;
    protected final static int LASTMSG = 50;


public DXClientThread(DXClient apple, DataInputStream is)
{
    inputStream = is;
    parent = apple;
    actions = new Vector(10);

    try {
	actions.addElement((Object)new 
	    DXClientThreadCommand(this, messageMsg.GetCommand(), DXClientThread.MESSAGE));
    } catch (ClassNotFoundException cnfe ) {
	cnfe.printStackTrace();
    }
}

//
// Read from the server until receiving a message that says a file has
// been updated.  Then show the document;
//
public void run()
{
    failed = false;
    try {
	String inputLine;
	while ((failed == false) && ((inputLine = inputStream.readLine()) != null)) {
	    Enumeration enum = actions.elements();
	    boolean executed = false;
	    while (enum.hasMoreElements()) {
		DXClientThreadCommand etc = (DXClientThreadCommand)enum.nextElement();
		if (inputLine.startsWith(etc.getCommandString())) {
		   executed = etc.execute(inputLine);
		   if (executed) break;
		}
	    }
	    if (!executed) {
		System.out.println ("DXClientThread: Unrecognized - " + inputLine);
	    }
	}
    } catch (IOException e) {
	failed = true;
    } catch (Exception e) {
	e.printStackTrace();
	failed = true;
    }

    //
    // Do not add any code after the call to disconnect because
    // the applet will stop this thread
    //
    if (failed)
	parent.disconnect(this);
}

//
// If the error message looks fatal then terminate.
// The server side won't terminate before we do.
//
public boolean message (threadMsg msg)
{
    messageMsg mm = (messageMsg)msg;
    System.out.println (mm.getMessage());
    if (mm.getMessage().startsWith("Error"))
	failed = true;
    return true;
}

}; // end DXClientThread


