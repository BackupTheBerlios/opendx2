## Process this file with automake to produce Makefile.in

INCLUDES = -I${srcdir}/../dpexec -D@ARCH@

EXPARG=@EXPARG@
EXP=${top_srcdir}/lib/dxexec.exp
WEXP=${top_srcdir}/lib/dxexec.def

dxbindir = $(prefix)/dx/bin_@ARCH@
dxbin_PROGRAMS = dxexec
noinst_LIBRARIES = libDXEXEC.a

SUFFIXES = .m .y .c .s .h .o .a 

dxexec_SOURCES = main.c
libDXEXEC_a_SOURCES = main.c

dxexec_LDFLAGS = @DXEXEC_EXP@

dxexec_LDADD = \
        ../dpexec/libDPEXEC.a \
	../dxmods/libDXMODS.a \
	../libdx/libLIBDX.a \
	../hwrender/libHW.a \
	../hwrender/opengl/libOPENGL.a 
