## Process this file with automake to produce Makefile.in

htmldir = $(prefix)/dx/html

html_DATA = README.htm README_SMP.htm README_alphax.htm \
	README_hp700.htm README_ibm6000.htm README_intelnt.htm \
	README_sgi.htm README_solaris.htm allguide.htm \
	insguide.htm proguide.htm qikguide.htm refguide.htm usrguide.htm 

EXTRA_DIST = pages.tar images.tar $(html_DATA)

install-data-local:
	tar -C $(prefix)/html -xf pages.tar
	tar -C $(prefix)/html -xf images.tar
	ln -s $(prefix)/html/allguide.htm $(prefix)/html/index.htm
	ln -s $(prefix)/html/allguide.htm $(prefix)/html/index.html

