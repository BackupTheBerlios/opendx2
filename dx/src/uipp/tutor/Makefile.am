## Process this file with automake to produce Makefile.in

INCLUDES = -I../../../include -I../base
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxbindir = $(prefix)/dx/bin_@ARCH@

dxbin_PROGRAMS = tutor

tutor_SOURCES =				\
	Main.C                          \
	NoUndoTutorAppCommand.C         \
	TutorApplication.C              \
	TutorWindow.C			

noinst_HEADERS = \
	NoUndoTutorAppCommand.h \
	TutorApplication.h \
	TutorWindow.h

tutor_LDADD = 				\
	../base/libBASE.a  		\
	../widgets/libWIDGETS.a  	\
	../dxl/libDXL.a		  	\
	-L/usr/X11R6/lib 		\
	-L/usr/local/lib 		\
	-L$(DXROOT)/lib_@ARCH@	\
	-lg++ -lXm -lXmu -lXt -lX11 -lXext
