## Process this file with automake to produce Makefile.in

EXTRA_DIST = dx.workerscript

uninstall-local:
	/bin/rm  $(prefix)/bin/dx
	/bin/rm $(prefix)/dx/bin/dx.workerscript

install-exec-local:
	$(INSTALL) dx $(prefix)/bin
	$(INSTALL) -d $(prefix)/dx/bin
	$(INSTALL) dx.workerscript $(prefix)/dx/bin
