## Process this file with automake to produce Makefile.in

htmldir = $(prefix)/dx/html

SUBDIRS = pages images

html_files = README.htm README_SMP.htm README_alphax.htm \
	README_hp700.htm README_ibm6000.htm README_intelnt.htm \
	README_sgi.htm README_solaris.htm allguide.htm \
	insguide.htm proguide.htm qikguide.htm refguide.htm usrguide.htm \
	search.js srchhelp.htm srchidx.js srchindx.htm srchnav.htm


EXTRA_DIST = $(html_files)

if WITH_INSTALLHTML

html_DATA = $(EXTRA_DIST)

install-data-local:
	sh -c 'f=`pwd` ; 					\
	       if test ! -d $(htmldir) ; then 			\
		   mkdir $(htmldir) ; 				\
	       fi ; 						\
	       chmod 755 $(htmldir) ;				\
	       cd $(htmldir) ; 					\
	       ln -s $(htmldir)/allguide.htm $(htmldir)/index.htm ; \
	       ln -s $(htmldir)/allguide.htm $(htmldir)/index.html ; \
	       cd $$f ; 						\
	      '
endif # WITH_INSTALLHTML
