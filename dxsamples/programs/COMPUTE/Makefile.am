## Process this file with automake to produce Makefile.in

LINKLIST = \
         Bounce.cfg\
         Bounce.net\
         Compute2.cfg\
         Compute2.net\
         ComputeMultiLine.cfg\
         ComputeMultiLine.net\
         ComputeOnData.cfg\
         ComputeOnData.net\
         WarpingPositions.cfg\
         WarpingPositions.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/COMPUTE
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/COMPUTE ; \
	done
