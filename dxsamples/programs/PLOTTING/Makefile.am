## Process this file with automake to produce Makefile.in

LINKLIST = \
         Categorical.cfg\
         Categorical.net\
         GroceryList.cfg\
         GroceryList.net\
         Histogram.cfg\
         Histogram.net\
         InterfaceControl2.cfg\
         InterfaceControl2.net\
         PickPlot.cfg\
         PickPlot.net\
         PlotGroupOfLines.cfg\
         PlotGroupOfLines.net\
         PlotLine.cfg\
         PlotLine.net\
         PlotLine2.cfg\
         PlotLine2.net\
         PlotSpecifyTicks.cfg\
         PlotSpecifyTicks.net\
         PlotTwoLines.cfg\
         PlotTwoLines.net\
         Sort.cfg\
         Sort.net\
         UsingBarChart.cfg\
         UsingBarChart.net\
         UsingEqualize.cfg\
         UsingEqualize.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/PLOTTING
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/PLOTTING ; \
	done
