## Process this file with automake to produce Makefile.in

dxbindir = $(prefix)/dx/bin
dxbin_SCRIPTS = mdf2c

EXTRA_DIST = dxworker dx mdf2c

uninstall-local: 
	if test -f $(prefix)/bin/dx  ; then \
		/bin/rm  $(prefix)/bin/dx ; \
	fi ; \
	if test -f $(prefix)/bin/dx.workerscript  ; then \
		/bin/rm $(prefix)/dx/bin/dxworker ; \
	fi

install-exec-local: 
	if test "@INSTALL_DX_CSH@" != "" ; then \
	    if test ! -d $(prefix)/bin ; then \
	    	mkdir $(prefix)/bin ; \
	    fi ; \
	    $(INSTALL) dx $(prefix)/bin ; \
	    if test ! -d $(prefix)/dx/bin ; then \
	    	mkdir $(prefix)/dx/bin ; \
	    fi ; \
	    $(INSTALL) dxworker $(prefix)/dx/bin  ;\
	fi
