## Process this file with automake to produce Makefile.in

INCLUDES = -I../dpexec -D@ARCH@

dxbindir = $(prefix)/dx/bin_@ARCH@
dxbin_PROGRAMS = dxexec

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
	-lm -lGL -lX11 -lXext
