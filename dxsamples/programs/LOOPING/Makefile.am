## Process this file with automake to produce Makefile.in

LINKLIST = \
         Accumulate.cfg\
         Accumulate.net\
         Bounce.cfg\
         Bounce.net\
         SimpleGetSetLoop.cfg\
         SimpleGetSetLoop.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/LOOPING
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/LOOPING ; \
	done
