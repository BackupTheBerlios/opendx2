## Process this file with automake to produce Makefile.in

SUBDIRS = src samples include lib bin

uninstall-local:
	if [ "$(prefix)" != "/usr/lpp" ] ; then \
	    rm -f /usr/lpp/dx ; \
	fi
	rm -rf $(prefix)/dx

install-data-local:
	if [ "$(prefix)" != "/usr/lpp" ] ; then \
	    ln -s $(prefix)/dx /usr/lpp/dx ; \
	fi

