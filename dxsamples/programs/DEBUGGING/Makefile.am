## Process this file with automake to produce Makefile.in

LINKLIST = \
         Verify.cfg\
         Verify.net\
         VisualObject.cfg\
         VisualObject.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/DEBUGGING
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/DEBUGGING ; \
	done
