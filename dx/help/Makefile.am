## Process this file with automake to produce Makefile.in

helpdir = $(prefix)/dx/help

EXTRA_DIST = help.tar

install-data-local:
	@sh -c 'if test ! -f $(helpdir)/hlpalhtl ; then \
		   f=`pwd` ; \
		   fs=`cd $(srcdir); pwd`; \
		   if test ! -d $(helpdir) ; then \
		   	mkdir $(helpdir) ; \
		   fi ; \
	       	   cd $(helpdir) ; \
		   echo "Extracting Help Files." ; \
	       	   tar xf $$fs/help.tar ; \
		   echo "Linking Help Files." ; \
	       	   ln -sf hlpalhtl  $(helpdir)/mbidx ; 		\
	       	   ln -sf hlpalhtl  $(helpdir)/quikidx ; 	\
	       	   ln -sf hlpalhtl  $(helpdir)/svsmstrh ; 	\
	       	   ln -sf hlpalhtl  $(helpdir)/ugidx ; 		\
	       	   ln -sf hlpalhtl  $(helpdir)/usrefidx ; 	\
	       	   ln -sf HelpDir   $(helpdir)/GarHelpDir ; 	\
	       	   ln -sf HelpDir   $(helpdir)/MBHelpDir ; 	\
	       fi \
	      '
