## Process this file with automake to produce Makefile.in

htmldir = $(prefix)/dx/html

html_DATA = README.htm README_SMP.htm README_alphax.htm \
	README_hp700.htm README_ibm6000.htm README_intelnt.htm \
	README_sgi.htm README_solaris.htm allguide.htm \
	insguide.htm proguide.htm qikguide.htm refguide.htm usrguide.htm 

EXTRA_DIST = pages.tar images.tar $(html_DATA)

if WITH_INSTALLHTML

install-data-local:
	sh -c 'f=`pwd` ; 					\
	       if test ! -d $(htmldir) ; then 			\
		   mkdir $(htmldir) ; 				\
	       fi ; 						\
	       chmod 755 $(htmldir) ;				\
	       cd $(htmldir) ; 					\
	       tar xpof $$f/pages.tar ;				\
	       tar xpof $$f/images.tar ;			\
	       ln -s $(htmldir)/allguide.htm $(htmldir)/index.htm ; \
	       ln -s $(htmldir)/allguide.htm $(htmldir)/index.html ; \
	       cd $$f ; 						\
	      '
endif # WITH_INSTALLHTML
