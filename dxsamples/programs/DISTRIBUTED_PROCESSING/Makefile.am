## Process this file with automake to produce Makefile.in

LINKLIST = \
         Distributed.cfg\
         Distributed.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/DISTRIBUTED_PROCESSING
	@for s in $(LINKLIST) ; do \
		ln -sf $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/DISTRIBUTED_PROCESSING ; \
	done
