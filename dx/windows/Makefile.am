## Process this file with automake to produce Makefile.in

EXTRA_DIST = ar cc cpp cxx mkdep msenv ranlib

install-exec-local:
	if test "@ARCH@" = "intelnt" ; then 	        \
	    $(mkinstalldirs) $(prefix)/dx/bin_intelnt ; \
	    cd $(srcdir) ; 				\
	    cp $(EXTRA_DIST) $(prefix)/dx/bin_intelnt ; \
	fi
	
all: 
	echo no targets here
