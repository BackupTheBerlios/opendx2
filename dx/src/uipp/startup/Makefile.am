## Process this file with automake to produce Makefile.in

INCLUDES =  -I../../../include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxbindir = $(prefix)/dx/bin_@ARCH@

dxbin_PROGRAMS = startupui

startupui_SOURCES =			\
	NetFileDialog.C			\
	StartupApplication.C		\
	StartupCommand.C		\
	StartupWindow.C			\
	TimedInfoDialog.C 		\
	\
	Main.C

noinst_HEADERS = \
	NetFileDialog.h \
	StartupApplication.h \
	StartupCommand.h \
	StartupWindow.h \
	TimedInfoDialog.h

startupui_LDADD = 			\
	../base/libBASE.a  		\
	../widgets/libWIDGETS.a  	\
	../dxl/libDXL.a		  	\
	-L/usr/X11R6/lib 		\
	-L/usr/local/lib 		\
	-L$(DXROOT)/lib_@ARCH@	\
	-lcrypt  -lXm -lXmu -lXt -lX11 -lXext
