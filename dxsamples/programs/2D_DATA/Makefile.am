## Process this file with automake to produce Makefile.in

LINKLIST = \
         AlternateVisualizations.cfg\
         AlternateVisualizations.net\
         BandedColors.cfg\
         BandedColors.net\
         ConnectingScatteredPoints.cfg\
         ConnectingScatteredPoints.net\
         FFT.cfg\
         FFT.net\
         GeneralImport1.cfg\
         GeneralImport1.net\
         GeneralImport2.cfg\
         GeneralImport2.net\
         InvalidData.cfg\
         InvalidData.net\
         Sealevel.cfg\
         Sealevel.net\
         Sort.cfg\
         Sort.net\
         Topo.cfg\
         Topo.net\
         UsingDrape.cfg\
         UsingDrape.net\
         UsingFilter.cfg\
         UsingFilter.net\
         UsingIsosurface.cfg\
         UsingIsosurface.net\
         UsingMorph.cfg\
         UsingMorph.net\
         UsingOverlay.cfg\
         UsingOverlay.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/2D_DATA
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/2D_DATA ; \
	done
