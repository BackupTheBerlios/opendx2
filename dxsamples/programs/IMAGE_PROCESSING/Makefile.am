## Process this file with automake to produce Makefile.in

LINKLIST = \
         FFT.cfg\
         FFT.net\
         MRI_1.cfg\
         MRI_1.net\
         QuantizeImage.cfg\
         QuantizeImage.net\
         UsingEqualize.cfg\
         UsingEqualize.net\
         UsingFilter.cfg\
         UsingFilter.net\
         UsingMorph.cfg\
         UsingMorph.net\
         UsingOverlay.cfg\
         UsingOverlay.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/IMAGE_PROCESSING
	@for s in $(LINKLIST) ; do \
		ln  $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/IMAGE_PROCESSING ; \
	done
