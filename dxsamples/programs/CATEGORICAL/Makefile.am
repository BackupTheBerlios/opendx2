## Process this file with automake to produce Makefile.in

LINKLIST = \
         Categorical.cfg\
         Categorical.net\
         Duplicates.cfg\
         Duplicates.net\
         ExamplePieChart.cfg\
         ExamplePieChart.net\
         GroceryList.cfg\
         GroceryList.net\
         Legend.cfg\
         Legend.net\
         SalesOnStates.cfg\
         SalesOnStates.net\
         ZipCodes.cfg\
         ZipCodes.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/CATEGORICAL
	@for s in $(LINKLIST) ; do \
		ln -sf $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/CATEGORICAL ; \
	done
