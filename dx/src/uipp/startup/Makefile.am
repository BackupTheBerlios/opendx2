## Process this file with automake to produce Makefile.in

INCLUDES =  -I../../../include -I../base -D@ARCH@

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
	-lm -lXm -lXmu -lXt -lX11 -lXext
