## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
java = $(dxdir)/java
server = $(java)/server
bindir = $(server)/bin
libdir = $(server)/lib
macrodir = $(server)/dxmacros
classdir = $(server)/class

bin_SCRIPTS = 				\
	startserver 			\
	startserver.bat			\
	stopserver

class_JAVA = 				\
	CleanUpDaemon.java		\
	ConnectThread.java		\
	ConnectionEntry.java		\
	DXServer.java			\
	DXServerThread.java		\
	DXThread.java			\
	DXThreadCommand.java		\
	FileStyle.java			\
	FileStyleANY.java		\
	FileStyleHTM.java		\
	FileStyleHTML.java		\
	FileStyleWRAP.java		\
	ServerCommand.java		\
	ServerThreadCommand.java	\
	StatusThread.java		\
	StatusThreadCommand.java

macro_DATA = 				\
    	dxmac.net			\
    	gifmac.net			\
	vrmlmac.net			\
	weboptionsmac.net

