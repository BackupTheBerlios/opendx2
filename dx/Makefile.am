## Process this file with automake to produce Makefile.in

SUBDIRS = src samples include lib bin

install-data-local:
	if [ "$(prefix)" != "/usr/lpp" ] ; then \
	    ln -s $(prefix)/dx /usr/lpp/dx ; \
	fi

