## Process this file with automake to produce Makefile.in

helpdir = $(prefix)/dx/help

EXTRA_DIST = help.tar

install-data-local:
	sh -c 'f=`pwd` ; \
	       $(INSTALL) -d $(helpdir) ; \
	       cd $(helpdir) ; \
	       tar xf $$f/help.tar ; \
	       ln -s $(helpdir)/hlpalhtl   $(helpdir)/mbidx ; \
	       ln -s $(helpdir)/hlpalhtl   $(helpdir)/quikidx ; \
	       ln -s $(helpdir)/hlpalhtl   $(helpdir)/svsmstrh ; \
	       ln -s $(helpdir)/hlpalhtl   $(helpdir)/ugidx ; \
	       ln -s $(helpdir)/hlpalhtl   $(helpdir)/usrefidx ; \
	       ln -s $(helpdir)/GarHelpDir $(helpdir)/GarHelpDir ; \
	       ln -s $(helpdir)/MBHelpDir  $(helpdir)/BMHelpDir ; \
	      '
