## Process this file with automake to produce Makefile.in

INCLUDES =  -I${top_srcdir}/include -I${srcdir}/.. -I${srcdir}/../../libdx -I/usr/include -I/usr/local/include -D@ARCH@

noinst_LIBRARIES = libOPENGL.a

SUFFIXES = .m .y .c .s .h .o .a 

noinst_HEADERS = \
	hwPortOGL.h hwPortUtilOGL.help


libOPENGL_a_SOURCES = \
	hwPortUtilOGL.c			\
	hwInteractorEchoOGL.c		\
	hwDisplayListsOGL.c		\
	hwPortOGL.c			\
	hwLoadOGL.c			
