## Process this file with automake to produce Makefile.in

EXTRA_DIST = dx.workerscript dx

uninstall-local: 
	if test -e $(prefix)/bin/dx  ; then
		/bin/rm  $(prefix)/bin/dx
	fi
	if test -e $(prefix)/bin/dx.workerscript  ; then
		/bin/rm $(prefix)/dx/bin/dx.workerscript
	fi

install-exec-local: 
	if test "@INSTALL_DX_CSH@" != "" ; then
	    $(INSTALL) dx $(prefix)/bin
	    $(INSTALL) -d $(prefix)/dx/bin
	    $(INSTALL) dx.workerscript $(prefix)/dx/bin
	fi
