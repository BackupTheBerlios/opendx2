## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include 
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
CXXMKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxbindir = $(DXROOT)/bin
dxlibdir = $(DXROOT)/lib
dxincludedir = $(DXROOT)/include/dx
dxlib_LIBRARIES = libDXL.a

libDXL_a_SOURCES =  \
	close.c				\
	conn.c				\
	connect.c			\
	dict.c				\
	execute.c			\
	exit.c				\
	handlers.c			\
	load.c				\
	object.c			\
	os2.c				\
	open.c				\
	query.c				\
	save.c				\
	send.c				\
	sequencer.c			\
	socket.c			\
	value.c				\
	windows.c			\
	x11.c

