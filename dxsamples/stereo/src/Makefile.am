## Process this file with automake to produce Makefile.in

datadir = $(prefix)/dx/samples/stereo/src

data_DATA =  mymodes.c mycams.c

EXTRA_DIST = $(data_DATA) 

install-data-local:
	cp localmk $(datadir)/makefile

uninstall-local:
	rm $(datadir)/makefile
