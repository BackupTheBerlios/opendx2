## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxbindir = $(DXROOT)/bin
dxincludedir = $(DXROOT)/include/dx
noinst_LIBRARIES = libDPEXEC.a

SUFFIXES = .m .y .c .s .h .o .a 

BUILT_SOURCES =  yuiif.c

libDPEXEC_a_SOURCES =  \
	attribute.c background.c cache.c cachegraph.c ccm.c \
	command.c context.c crc.c d.c distconnect.c distpacket.c \
	distqueue.c dxmain.c dxpfsmgr.c evalgraph.c exobject.c function.c \
	graph.c graph2.c graphqueue.c help.c instrument.c lex.c \
	license.c loader.c log.c macro.c nodereadb.c \
	nodewriteb.c packet.c parse.c parsemdf.c path.c pendingcmds.c \
	queue.c remote.c rih.c rq.c socket.c status.c \
	swap.c task.c userinter.c utils.c variable.c vcr.c \
	yuiif.c

.y.h:
	yacc $(YFLAGS) $*.y
	mv y.tab.h $*.h
	mv y.tab.c $*.c

.y.c:
	yacc $(YFLAGS) $*.y
	mv y.tab.h $*.h
	mv y.tab.c $*.c

compile.h: 
	echo '#define' EX_COM_DATE '"'`date`'"' >> compile.h
	echo '#define' EX_COM_HOST '"'`uname -a`'"' >> compile.h
	
