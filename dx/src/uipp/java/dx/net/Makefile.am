## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
java = $(dxdir)/java
installdir = $(java)/htmlpages/dx/net

SUFFIXES = .java .class

install_JAVA =	 			\
	Arc.java			\
	BinaryNode.java			\
	CfgValues.java			\
	ControlPanel.java		\
	DXApplication.java		\
	DXLAppThread.java		\
	DXLAppThreadCommand.java	\
	DXLOutputNode.java		\
	DXLinkApplication.java		\
	DXLinkHandler.java		\
	DXViewIF.java			\
	DrivenNode.java			\
	Gnomon.java			\
	ImageNode.java			\
	ImageWindow.java		\
	InteractorNode.java		\
	Network.java			\
	Node.java			\
	NumericValues.java		\
	PacketIF.java			\
	PickNode.java			\
	ResetNode.java			\
	ScalarNode.java			\
	SelectionNode.java		\
	SequencerNode.java		\
	ToggleNode.java			\
	ValueNode.java			\
	WRLApplication.java		\
	WebOptionsNode.java
