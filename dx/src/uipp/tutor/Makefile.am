## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxbindir = $(DXROOT)/bin
dxdatadir = $(DXROOT)/data
dxincludedir = $(DXROOT)/include/dx
# dxbin_PROGRAMS = tutor
# tutor_SOURCES =				

EXTRA_DIST = \
	Main.C                          \
	NoUndoTutorAppCommand.C         \
	TutorApplication.C              \
	TutorWindow.C			\
	\
	Main.C

tutor_LDADD = 				\
	../base/libBASE.a  		\
	../widgets/libWIDGETS.a  	\
	../dxl/libDXL.a		  	\
	-L/usr/X11R6/lib 		\
	-L/usr/local/lib 		\
	-L$(DXROOT)/lib_$(ARCH) 	\
	-lcrypt -lg++ -lXm -lXmu -lXt -lX11 -lXext
