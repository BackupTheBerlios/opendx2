## Process this file with automake to produce Makefile.in

helpdir = $(prefix)/dx/help

EXTRA_DIST = help.tar

install-data-local:
	mkdir $(helpdir)
	tar -C $(helpdir) -xf pages.tar
	ln -s $(helpdir)/mbidx      $(helpdir)/hlpalhtl
	ln -s $(helpdir)/quikidx    $(helpdir)/hlpalhtl
	ln -s $(helpdir)/svsmstrh   $(helpdir)/hlpalhtl
	ln -s $(helpdir)/ugidx      $(helpdir)/hlpalhtl
	ln -s $(helpdir)/usrefidx   $(helpdir)/hlpalhtl
	ln -s $(helpdir)/GarHelpDir $(helpdir)/HelpDir
	ln -s $(helpdir)/MBHelpDir  $(helpdir)/HelpDir
