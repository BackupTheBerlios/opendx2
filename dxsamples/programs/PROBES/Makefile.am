## Process this file with automake to produce Makefile.in

LINKLIST = \
         PlotLine2.cfg\
         PlotLine2.net\
         ProbeText.cfg\
         ProbeText.net\
         UsingProbes.cfg\
         UsingProbes.net\
         UsingStreakline.cfg\
         UsingStreakline.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/PROBES
	@for s in $(LINKLIST) ; do \
		ln -sf $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/PROBES ; \
	done
