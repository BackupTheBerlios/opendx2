## Process this file with automake to produce Makefile.in

INCLUDES = -I${top_srcdir}/include -D@ARCH@

dxbindir = $(prefix)/bin
noinst_PROGRAMS = dxlocal
archmakdir = $(prefix)/dx/lib_$(ARCH)
archmak_DATA = arch.mak

dxlocal_SOURCES = dx.c utils.c

noinst_HEADERS = dx.h utils.h

install-exec-local: 
	if test ! -z "@INSTALL_DX_EXE@" ; then 				     \
	    $(mkinstalldirs) $(prefix)/bin ;                \
	    cp $(noinst_PROGRAMS) @INSTALL_DX_EXE@@EXEEXT@ ;  	     	     \
	    $(INSTALL) @INSTALL_DX_EXE@@EXEEXT@  $(prefix)/bin/@INSTALL_DX_EXE@@EXEEXT@ ;	     \
	fi
