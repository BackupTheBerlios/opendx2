## Process this file with automake to produce Makefile.in

LINKLIST = \
         DialogStyle.cfg\
         DialogStyle.net\
         InterfaceControl1.cfg\
         InterfaceControl1.net\
         InterfaceControl2.cfg\
         InterfaceControl2.net\
         InterfaceControl3.cfg\
         InterfaceControl3.net

myinstall: 
	$(mkinstalldirs) $(prefix)/dx/samples/programs/INTERFACE_CONTROL
	@for s in $(LINKLIST) ; do \
		ln -sf $(prefix)/dx/samples/programs/$$s  $(prefix)/dx/samples/programs/INTERFACE_CONTROL ; \
	done
