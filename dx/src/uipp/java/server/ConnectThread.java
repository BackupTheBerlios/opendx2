//
package server;
import java.net.*;
import java.io.*;
import java.util.*;
import dx.protocol.server.*;

public class ConnectThread extends Thread
{
    Socket clientSocket;
    public ConnectThread(Socket clientSocket) {
	this.clientSocket = clientSocket;
    }

    public void run() 
    {
	try {
	    InputStream bis = new DataInputStream(clientSocket.getInputStream());
	    DataInputStream dis = new DataInputStream(bis);
	    String inputLine = dis.readLine();
	    if (inputLine == null)
		return;

	    if (DXServer.versionMatch(inputLine) == true) {
		PrintStream os = new PrintStream(clientSocket.getOutputStream());
		serverVersionMsg svm = new serverVersionMsg();
		svm.setVersion(DXServer.MajorVersion, DXServer.MinorVersion,
		    DXServer.MicroVersion);
		os.println (svm.toString());
		os.flush();
		os = null;
	    } else {
		dis.close(); dis = null;
		clientSocket.close(); clientSocket = null;
		return ;
	    }

	    Enumeration enum = DXServer.actions.elements();
	    while (enum.hasMoreElements()) {
		ServerCommand sc = (ServerCommand)enum.nextElement();
		if (inputLine.startsWith(sc.getCommandString())) {
		    sc.execute(inputLine, clientSocket);
		    break;
		}
	    }
	} catch (Exception e) {
	}
    }
}; // end ConnectThread
