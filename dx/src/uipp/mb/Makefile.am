## Process this file with automake to produce Makefile.in

INCLUDES = -I$(DXROOT)/include
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxbindir = $(prefix)/dx/bin_@ARCH@

dxbin_PROGRAMS = builder

builder_SOURCES =			
	MBApplication.C			\
	MBMainWindow.C			\
	MBCommand.C			\
	MBNewCommand.C			\
	OpenFileDialog.C		\
	SADialog.C			\
	QuitCommand.C			\
	ConfirmedQCommand.C		\
	CommentDialog.C			\
	OptionsDialog.C			\
	MBParameter.C			\
	MBGenerate.C			\
	\
	Main.C

noinst_HEADERS = \
	CommentDialog.h \
	ConfirmedQCommand.h \
	MBApplication.h \
	MBCommand.h \
	MBGenerate.h \
	MBMainWindow.h \
	MBNewCommand.h \
	MBParameter.h \
	OpenFileDialog.h \
	OptionsDialog.h \
	QuitCommand.h \
	SADialog.h

builder_LDADD = 			\
	../base/libBASE.a  		\
	../widgets/libWIDGETS.a  	\
	../dxl/libDXL.a		  	\
	-L/usr/X11R6/lib 		\
	-L/usr/local/lib 		\
	-L$(DXROOT)/lib_@ARCH@	\
	-lcrypt -lg++ -lXm -lXmu -lXt -lX11 -lXext
