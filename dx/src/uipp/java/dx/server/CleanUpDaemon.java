//
// (C) COPYRIGHT International Business Machines Corp. 1997
// All Rights Reserved
// Licensed Materials - Property of IBM
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/CleanUpDaemon.java,v 1.1 1999/03/24 15:17:33 gda Exp $
 */
import java.net.*;
import java.io.*;


public class CleanUpDaemon extends Thread
{
    //
    // Number of milliseconds betwen clean up operations.
    //
    long millis = 30000; 

    public void run() 
    {
	boolean run = true;
	while (run) {
	    DXServer.CleanUp();
	    try {
		sleep(millis);
	    } catch (InterruptedException ie) {
		System.out.println ("CleanUpDaemon exiting due to InterruptedException");
		run = false;
	    }
	}
    }

}; // end CleanUpDaemon
