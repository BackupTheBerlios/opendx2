## Process this file with automake to produce Makefile.in

helpdir = $(prefix)/dx/help

EXTRA_DIST = help.tar

install-data-local:
	@sh -c 'if test ! -f $(helpdir)/hlpalhtl ; then \
		   f=`pwd` ; \
		   if test ! -d $(helpdir) ; then \
		   	mkdir $(helpdir) ; \
		   fi ; \
	       	   cd $(helpdir) ; \
		   echo "Extracting Help Files." ; \
	       	   tar xf $$f/help.tar ; \
		   echo "Linking Help Files." ; \
	       	   ln -s hlpalhtl  mbidx ; 	\
	       	   ln -s hlpalhtl  quikidx ; 	\
	       	   ln -s hlpalhtl  svsmstrh ; 	\
	       	   ln -s hlpalhtl  ugidx ; 	\
	       	   ln -s hlpalhtl  usrefidx ; 	\
	       	   ln -s HelpDir   GarHelpDir ; \
	       	   ln -s HelpDir   MBHelpDir ; 	\
	       fi \
	      '
