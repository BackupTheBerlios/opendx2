## Process this file with automake to produce Makefile.in

INCLUDES = 
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxbindir = $(prefix)/dx/bin

# dxbin_PROGRAMS = tutor
# tutor_SOURCES =				

EXTRA_DIST = \
	Main.C                          \
	NoUndoTutorAppCommand.C         \
	TutorApplication.C              \
	TutorWindow.C			\
	\
	Main.C

noinst_HEADERS = \
	NoUndoTutorAppCommand.h \
	TutorApplication.h \
	TutorWindow.h

#tutor_LDADD = 				\
#	../base/libBASE.a  		\
#	../widgets/libWIDGETS.a  	\
#	../dxl/libDXL.a		  	\
#	-L/usr/X11R6/lib 		\
#	-L/usr/local/lib 		\
#	-L$(DXROOT)/lib_@ARCH@	\
#	-lcrypt -lg++ -lXm -lXmu -lXt -lX11 -lXext
