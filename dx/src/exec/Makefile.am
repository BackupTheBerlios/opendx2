SUBDIRS = libdx dxmods hwrender dpexec dxexec
EXTRA_DIST = mklib

DELFILES = \
        xxmain.o \
        mduser.o \
        lbmemory.o \
        lbmem.o    \
        exattribute.o \
        exbackground.o \
        excache.o \
        excachegraph.o \
        exccm.o \
        excommand.o \
        excontext.o \
        exdistconnect.o \
        exdistpacket.o \
        exdistqueue.o \
        exdxmain.o \
        exdxpfsmgr.o \
        exevalgraph.o \
        exgraph.o \
        exgraph2.o \
        exgraphqueue.o \
        exhelp.o \
        exinstrument.o \
        exlex.o \
        exlog.o \
        exnodereadb.o \
        exnodewriteb.o \
        expacket.o \
        exparsemdf.o \
        expath.o \
        expendingcmds.o \
        exqueue.o \
        exremote.o \
        exrih.o \
        exrq.o \
        exsocket.o \
        exstatus.o \
        exswap.o \
        extask.o \
        exvariable.o \
        exvcr.o \
        exyuiif.o

if WITH_BUILDLIBDX

install-exec-local:
	echo set prefix=\"$(prefix)\"         > env
	echo export prefix                    >> env
	echo set ARCH=\"$(ARCH)\"             >> env
	echo export ARCH                      >> env
	echo set RANLIB=\"$(RANLIB)\"         >> env
	echo export RANLIB                    >> env
	echo set FMTLIBS=\"$(FMTLIBS)\"       >> env
	echo export FMTLIBS                   >> env
	echo set INSTALL=\"$(INSTALL)\"       >> env
	echo export INSTALL                   >> env
	echo set DELFILES=\"$(DELFILES)\"     >> env
	echo export DELFILES                  >> env
	sh  ${srcdir}/mklib
	-rm env

endif # WITH_BUILDLIBDX

clean-local:
	rm -rf tmp
