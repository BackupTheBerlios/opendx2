## Process this file with automake to produce Makefile.in

LINKLIST = \
         Categorical.cfg\
         Categorical.net\
         Duplicates.cfg\
         Duplicates.net\
         GeneralImport1.cfg\
         GeneralImport1.net\
         GeneralImport2.cfg\
         GeneralImport2.net\
         ImportExternalFilter.cfg\
         ImportExternalFilter.net\
         ZipCodes.cfg\
         ZipCodes.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/IMPORTING
	@for s in $(LINKLIST) ; do \
		$(LN_S) $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/IMPORTING ; \
	done
