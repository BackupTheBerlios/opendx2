## Process this file with automake to produce Makefile.in

INCLUDES = -I../../include

dxbindir = $(prefix)/bin
noinst_PROGRAMS = dxlocal
archmakdir = $(prefix)/dx/lib_$(ARCH)
archmak_DATA = arch.mak

dxlocal_SOURCES = dx.c 

install-exec-local: 
	if test ! -z "@INSTALL_DX_EXE@" ; then 				     \
	    cp $(noinst_PROGRAMS) @INSTALL_DX_EXE@@EXEEXT@ ;  	     	     \
	    $(INSTALL) @INSTALL_DX_EXE@@EXEEXT@  $(prefix)/bin ;	     \
	fi
