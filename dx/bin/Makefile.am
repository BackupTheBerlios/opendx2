## Process this file with automake to produce Makefile.in

EXTRA_DIST = dx.workerscript

install-exec-local:
	$(INSTALL) dx $(prefix)/bin
	install -d $(prefix)/dx/bin
	$(INSTALL) dx.workerscript $(prefix)/dx/bin
