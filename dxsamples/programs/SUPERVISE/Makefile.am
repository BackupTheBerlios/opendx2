## Process this file with automake to produce Makefile.in

LINKLIST = \
         Image_wo_UI.cfg\
         Image_wo_UI.net\
         IndependentlyArrange.cfg\
         IndependentlyArrange.net\
         InsetImage.cfg\
         InsetImage.net\
         InsetImageSimple.cfg\
         InsetImageSimple.net\
         Supervise.cfg\
         Supervise.net\
         SupervisePicking.cfg\
         SupervisePicking.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/SUPERVISE
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/SUPERVISE ; \
	done
