## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
java = $(dxdir)/java
installdir = $(java)/htmlpages/dx/client

SUFFIXES = .java .class

install_JAVA =	 			\
	AppletClient.java		\
	AppletLoadThread.java		\
	DXClient.java			\
	DXClientThread.java		\
	DXClientThreadCommand.java	\
	StopThread.java
