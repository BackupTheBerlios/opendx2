## Process this file with automake to produce Makefile.in

INCLUDES = -I${top_srcdir}/include -I${srcdir}/../libdx -D@ARCH@

noinst_LIBRARIES = libDPEXEC.a

SUFFIXES = .m .y .c .s .h .o .a 

BUILT_SOURCES =  

noinst_HEADERS = \
	_eval.h _macro.h _variable.h attribute.h background.h cache.h \
	compile.h config.h context.h crc.h d.h distp.h exobject.h graph.h \
	graphIntr.h graphqueue.h instrument.h license.h log.h obmodule.h \
	packet.h parse.h path.h pmodflags.h queue.h rq.h status.h swap.h \
	sysvars.h utils.h vcr.h version.h sfile.h

libDPEXEC_a_SOURCES =  \
	attribute.c background.c cache.c cachegraph.c ccm.c \
	command.c context.c crc.c d.c distconnect.c distpacket.c \
	distqueue.c dxmain.c dxpfsmgr.c evalgraph.c exobject.c function.c \
	graph.c graph2.c graphqueue.c help.c instrument.c lex.c \
	license.c loader.c log.c macro.c nodereadb.c \
	nodewriteb.c packet.c parse.c parsemdf.c path.c pendingcmds.c \
	queue.c remote.c rih.c rq.c socket.c status.c \
	swap.c task.c userinter.c utils.c variable.c vcr.c \
	optarg.c yuiif.y sfile.c usercleanup.c

EXTRA_DIST = local.mk

$(libDPEXEC_a_SOURCES): yuiif.c yuiif.h

DISTCLEANFILES = yuiif.c yuiif.h

@LOCALMAKE@
