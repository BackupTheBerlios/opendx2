## Process this file with automake to produce Makefile.in

INCLUDES =  -I../../../../include -I.. -I../../libdx
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

noinst_LIBRARIES = libOPENGL.a

SUFFIXES = .m .y .c .s .h .o .a 

noinst_HEADERS = \
	hwPortOGL.h hwPortUtilOGL.help


libOPENGL_a_SOURCES = \
	hwPortUtilOGL.c			\
	hwInteractorEchoOGL.c		\
	hwDisplayListsOGL.c		\
	hwPortOGL.c			\
	hwLoadOGL.c			\
