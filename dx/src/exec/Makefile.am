SUBDIRS = libdx dxmods hwrender dpexec dxexec

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
	echo export prefix=\"$(prefix)\"         > env
	echo export ARCH=\"$(ARCH)\"             >> env
	echo export RANLIB=\"$(RANLIB)\"         >> env
	echo export FMTLIBS=\"$(FMTLIBS)\"       >> env
	echo export INSTALL=\"$(INSTALL)\"       >> env
	echo export DELFILES=\"$(DELFILES)\"     >> env
	sh  mklib
	-rm env

endif # WITH_BUILDLIBDX

clean-local:
	rm -rf tmp
