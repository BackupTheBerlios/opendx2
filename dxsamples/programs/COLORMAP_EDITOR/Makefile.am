## Process this file with automake to produce Makefile.in

LINKLIST = \
         DataDrivenInteractors.cfg\
         DataDrivenInteractors.net\
         Imide_potential.cfg\
         Imide_potential.net\
         StandardColormaps.cfg\
         StandardColormaps.net\
         UsingColormaps.cfg\
         UsingColormaps.net\
         VolumeRendering.cfg\
         VolumeRendering.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/COLORMAP_EDITOR
	@for s in $(LINKLIST) ; do \
		ln  $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/COLORMAP_EDITOR ; \
	done
