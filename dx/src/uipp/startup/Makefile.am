## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxbindir = $(DXROOT)/bin
dxdatadir = $(DXROOT)/data
dxincludedir = $(DXROOT)/include/dx

# dxbin_PROGRAMS = startupui
# startupui_SOURCES =			

EXTRA_DATA = \
	NetFileDialog.C			\
	StartupApplication.C		\
	StartupCommand.C		\
	StartupWindow.C			\
	TimedInfoDialog.C
	\
	Main.C

startupui_LDADD = 			\
	../base/libBASE.a  		\
	../widgets/libWIDGETS.a  	\
	../dxl/libDXL.a		  	\
	-L/usr/X11R6/lib 		\
	-L/usr/local/lib 		\
	-L$(DXROOT)/lib_$(ARCH) 	\
	-lcrypt -lg++ -lXm -lXmu -lXt -lX11 -lXext
