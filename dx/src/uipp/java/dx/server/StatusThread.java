//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/StatusThread.java,v 1.1 1999/03/24 15:17:33 gda Exp $
 */
import java.net.*;
import java.io.*;
import java.util.*;
import dx.protocol.*;

public class StatusThread extends DXThread
{
    public final static int STATUS = 1;
    public final static int USERS = 2;
    public final static int VISITS = 3;
    public final static int HOSTS = 4;
    public final static int UPTIME = 5;
    public final static int DISCONNECT = 6;


public StatusThread (Socket client)
{
    super(client);

    try {
	actions.addElement ((Object)new
	   StatusThreadCommand(this, stopMsg.GetCommand(), StatusThread.DISCONNECT));
	actions.addElement ((Object)new
	    StatusThreadCommand(this, usersMsg.GetCommand(), StatusThread.USERS));
	actions.addElement ((Object)new
	    StatusThreadCommand(this, visitsMsg.GetCommand(), StatusThread.VISITS));
	actions.addElement ((Object)new
	    StatusThreadCommand(this, uptimeMsg.GetCommand(), StatusThread.UPTIME));
    } catch (ClassNotFoundException cnfe) {
	cnfe.printStackTrace();
    }
}

public boolean uptime (threadMsg msg)
{
    uptimeMsg utm = new uptimeMsg();
    utm.setUpTime(DXServer.getStartDate());
    transmit(utm);
    return true;
}

public boolean users (threadMsg msg)
{
    usersMsg um = new usersMsg();
    um.setUserCount(DXServer.getUserCount());
    transmit(um);
    return true;
}

public boolean visits (threadMsg  msg)
{
    visitsMsg vm = new visitsMsg();
    vm.setVisitCount(DXServer.getServedCount());
    transmit(vm);
    return true;
}

}; // end StatusThread
