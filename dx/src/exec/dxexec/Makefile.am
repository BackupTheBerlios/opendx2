## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include ../dpexec
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

bin_PROGRAMS = dxexec

SUFFIXES = .m .y .c .s .h .o .a 

dxexec_SOURCES = main.c

dxexec_LDADD = \
        ../dpexec/libDPEXEC.a \
	../dxmods/libDXMODS.a \
	../libdx/libLIBDX.a \
	../hwrender/libHW.a \
	../hwrender/opengl/libOPENGL.a \
	-L/usr/X11R6/lib \
	-L/usr/local/lib \
	-ldl -lm -lMesaGL -lX11 -lXext
