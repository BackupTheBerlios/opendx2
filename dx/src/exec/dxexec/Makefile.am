## Process this file with automake to produce Makefile.in

INCLUDES = -I../dpexec -D@ARCH@

EXPARG=@EXPARG@
EXP=$BUILDBASE/lib/dxexec.exp

dxbindir = $(prefix)/dx/bin_@ARCH@
dxbin_PROGRAMS = dxexec
noinst_LIBRARIES = libDXEXEC.a

SUFFIXES = .m .y .c .s .h .o .a 

dxexec_SOURCES = main.c
libDXEXEC_a_SOURCES = main.c

EXP = @BUILDBASE@/lib/dxexec.exp

dxexec_LDFLAGS = @DXEXEC_EXP@

dxexec_LDADD = \
        ../dpexec/libDPEXEC.a \
	../dxmods/libDXMODS.a \
	../libdx/libLIBDX.a \
	../hwrender/libHW.a \
	../hwrender/opengl/libOPENGL.a \
	-L/usr/X11R6/lib \
	-L/usr/local/lib \
	-lm -lGL -lX11 -lXext
