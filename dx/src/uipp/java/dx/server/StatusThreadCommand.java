//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/StatusThreadCommand.java,v 1.1 1999/03/24 15:17:33 gda Exp $
 */
import dx.protocol.*;

public final class StatusThreadCommand extends DXThreadCommand
{

    public StatusThreadCommand (StatusThread dxst, String str, int code)
    {
	super(dxst, str, code);
    }


    public boolean execute(String inputLine)
    {
	boolean retval = true;
	threadMsg msg;
	StatusThread st = (StatusThread)obj;
	switch (opcode) {
	    case StatusThread.USERS:
		msg = new usersMsg(inputLine);
		retval = st.users(msg);
		break;
	    case StatusThread.VISITS:
		msg = new visitsMsg(inputLine);
		retval = st.visits(msg);
		break;
	    case StatusThread.UPTIME:
		msg = new uptimeMsg(inputLine);
		retval = st.uptime(msg);
		break;
	    case StatusThread.DISCONNECT:
		msg = new stopMsg(inputLine);
		retval = st.disconnect(msg);
		break;
	}
	return retval;
    }

} // end StatusThreadCommand
