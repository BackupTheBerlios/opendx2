## Process this file with automake to produce Makefile.in

INCLUDES = -I../../../include  -D@ARCH@

dxlibdir = $(prefix)/dx/lib_@ARCH@

dxlib_LIBRARIES = libDXL.a

noinst_HEADERS = \
	dxlP.h \
	dict.h

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

