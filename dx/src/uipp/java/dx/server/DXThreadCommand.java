//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/DXThreadCommand.java,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

import dx.protocol.*;

public abstract class DXThreadCommand
{
    protected DXThread obj;
    protected String cmdstr;
    protected int opcode;

    public DXThreadCommand (DXThread tc, String str, int code)
    {
	opcode = code;
	cmdstr = str;
	obj = tc;
    }

    public final String getCommandString() { return cmdstr; }
    public abstract boolean execute(String inputLine);

} // end DXThreadCommand
