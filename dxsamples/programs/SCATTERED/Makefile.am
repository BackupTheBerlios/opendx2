## Process this file with automake to produce Makefile.in

LINKLIST = \
         AnnotationGlyphs.cfg\
         AnnotationGlyphs.net\
         ConnectingScatteredPoints.cfg\
         ConnectingScatteredPoints.net\
         ScatterData.cfg\
         ScatterData.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/SCATTERED
	@for s in $(LINKLIST) ; do \
		ln -sf $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/SCATTERED ; \
	done
