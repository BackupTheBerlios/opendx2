srvbindir = $(prefix)/dx/java/server/bin
# the server script (in srvbindir) will actually cd and run from the class subdir so that java will find the classes
# the server will expect to find a file dxserver.paths there to tell the exec where to find .net files
srvrundir = $(srvbindir)/../class
srvrundir_DATA=dxserver.paths
srvbin_DATA = $(SCRFILES)

SCRFILES = stopserver startserver startserver.bat

EXTRA_DIST = CleanUpDaemon.java ConnectThread.java ConnectionEntry.java DXLink.c DXServer.java DXServerThread.java DXThread.java DXThreadCommand.java FileStyle.java FileStyleANY.java FileStyleHTM.java FileStyleHTML.java FileStyleWRAP.java ServerCommand.java ServerThreadCommand.java StatusThread.java StatusThreadCommand.java $(SCRFILES) 


SUBDIRS = macros
