## Process this file with automake to produce Makefile.in

INCLUDES = -I../../../include -I../base -D@ARCH@

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
	-L$(DXROOT)/lib_@ARCH@
