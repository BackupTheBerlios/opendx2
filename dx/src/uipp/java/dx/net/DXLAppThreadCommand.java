//////////////////////////////////////////////////////////////////////////////
//                         DX SOURCEFILE				    //
//////////////////////////////////////////////////////////////////////////////


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/net/DXLAppThreadCommand.java,v 1.1 1999/03/24 15:17:30 gda Exp $
 */

package dx.net;
import dx.client.*;
import dx.protocol.*;

public class DXLAppThreadCommand extends DXClientThreadCommand 
{


public DXLAppThreadCommand
    (DXLAppThread dxst, String str, int code)
{
    super (dxst, str, code);
}


public boolean execute(String inputLine)
{
    boolean retval = true;
    DXLAppThread dlt = (DXLAppThread)obj;
    threadMsg msg;
    switch (opcode) {
	case DXLAppThread.FINISHED:
	    msg = new doneMsg(inputLine);
	    retval = dlt.doneExecuting(msg);
	    break;
	case DXLAppThread.SETID:
	    msg = new setidMsg(inputLine);
	    retval = dlt.setId(msg);
	    break;
	case DXLAppThread.SETMACRO:
	    msg = new setmacroMsg(inputLine);
	    retval = dlt.setMacro(msg);
	    break;
	default:
	    retval = super.execute(inputLine);
	    break;
    }
    return retval;
}

} // end DXLAppThreadCommand
