## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I../base -I../dxuilib
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxbindir = $(prefix)/dx/bin
dxbin_PROGRAMS = dxui

dxui_SOURCES = 				\
	Main.C

dxui_LDADD = \
	../dxuilib/libDXUI.a  \
	../base/libBASE.a  \
	../widgets/libWIDGETS.a  \
	-L/usr/X11R6/lib \
	-L/usr/local/lib \
	-lg++ -lpthread -lm -lXm -lXmu -lXt -lX11 -lXext


