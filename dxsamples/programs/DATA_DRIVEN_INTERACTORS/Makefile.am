## Process this file with automake to produce Makefile.in

LINKLIST = \
         DataDrivenInteractors.cfg\
         DataDrivenInteractors.net\
         DataDrivenSelector.cfg\
         DataDrivenSelector.net\
         Imide_potential.cfg\
         Imide_potential.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/DATA_DRIVEN_INTERACTORS
	@for s in $(LINKLIST) ; do \
		ln -sf $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/DATA_DRIVEN_INTERACTORS ; \
	done
