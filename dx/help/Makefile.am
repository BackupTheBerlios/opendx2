## Process this file with automake to produce Makefile.in

htmldir = $(prefix)/html

EXTRA_DIST = help.tar

install-data_local:
	mkdir $(prefix)/help
	tar -C $(prefix)/help -xf pages.tar
	ln -s $(prefix)/help/mbidx      $(prefix)/help/hlpalhtl
	ln -s $(prefix)/help/quikidx    $(prefix)/help/hlpalhtl
	ln -s $(prefix)/help/svsmstrh   $(prefix)/help/hlpalhtl
	ln -s $(prefix)/help/ugidx      $(prefix)/help/hlpalhtl
	ln -s $(prefix)/help/usrefidx   $(prefix)/help/hlpalhtl
	ln -s $(prefix)/help/GarHelpDir $(prefix)/help/HelpDir
	ln -s $(prefix)/help/MBHelpDir  $(prefix)/help/HelpDir
