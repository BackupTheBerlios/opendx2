## Process this file with automake to produce Makefile.in

INCLUDES = -I../../../include 
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

noinst_LIBRARIES = libLIBDX.a

noinst_HEADERS = \
	binSort.h triangles.h internals.h diskio.h zclip.h edf.h render.h \
	qsort.c

EXTRA_DIST = \
	class class.awk \
	\
	arrayClass.X cameraClass.X clippedClass.X fieldClass.X groupClass.X \
	lightClass.X objectClass.X privateClass.X screenClass.X stringClass.X \
	xformClass.X interpClass.X fieldinterpClass.X groupinterpClass.X \
	fle2DClass.X linesII1DClass.X linesRR1DClass.X linesRI1DClass.X \
	trisRI2DClass.X quadsRR2DClass.X cubesIIClass.X cubesRRClass.X \
	tetrasClass.X quadsII2DClass.X \
	\
	buffer.Z shade.Z triangle.Z quad.Z plane.Z 

CLEANFILES = \
	buffer.c shade.c triangle.c quad.c plane.c 

BUILT_SOURCES = \
	buffer.c shade.c triangle.c quad.c plane.c \
	\
	arrayClass.c cameraClass.c clippedClass.c fieldClass.c groupClass.c \
	lightClass.c objectClass.c privateClass.c screenClass.c stringClass.c \
	xformClass.c interpClass.c fieldinterpClass.c groupinterpClass.c \
	fle2DClass.c linesII1DClass.c linesRR1DClass.c linesRI1DClass.c \
	trisRI2DClass.c quadsRR2DClass.c cubesIIClass.c cubesRRClass.c \
	tetrasClass.c quadsII2DClass.c  \
	\
	arrayClass.h cameraClass.h clippedClass.h fieldClass.h groupClass.h \
	lightClass.h objectClass.h privateClass.h screenClass.h stringClass.h \
	xformClass.h interpClass.h fieldinterpClass.h groupinterpClass.h \
	fle2DClass.h linesII1DClass.h linesRR1DClass.h linesRI1DClass.h \
	trisRI2DClass.h quadsRR2DClass.h cubesIIClass.h cubesRRClass.h \
	tetrasClass.h quadsII2DClass.h  

libLIBDX_a_LIBADD =  \
	arrayClass.o cameraClass.o clippedClass.o fieldClass.o groupClass.o \
	lightClass.o objectClass.o privateClass.o screenClass.o stringClass.o \
	xformClass.o interpClass.o fieldinterpClass.o groupinterpClass.o \
	fle2DClass.o linesII1DClass.o linesRR1DClass.o linesRI1DClass.o \
	trisRI2DClass.o quadsRR2DClass.o cubesIIClass.o cubesRRClass.o \
	tetrasClass.o quadsII2DClass.o 

libLIBDX_a_SOURCES =  \
	\
	array.c basic.c box.c cache.c camera.c clipped.c composite.c \
	cstarray.c field.c grid.c group.c helper.c init.c light.c lock.c \
	matrix.c mem.c memory.c mesharray.c message.c multigrid.c \
	neighbors.c object.c patharray.c private.c productarray.c \
	regulararray.c screen.c series.c string.c stringtable.c \
	task.c timing.c v3.c vector.c version.c xform.c \
	\
	axes.c buffer.c client.c color.c component.c displayfb.c displayx.c \
	edfdata.c edfdict.c edfio.c edflex.c edfobj.c edfparse.c edfprint.c \
	extract.c fileio.c grow.c hash.c image.c invalid.c irreggrow.c map.c \
	gather.c line.c partition.c partreg.c parts.c permute.c \
	paint.c print.c private.c reggrow.c rwobject.c seglist.c stats.c text.c \
	transform.c binSort.c interp.c fieldinterp.c groupinterp.c fle2D.c \
	linesII1D.c linesRR1D.c linesRI1D.c trisRI2D.c quadsRR2D.c \
	cubesII.c cubesRR.c tetras.c quadsII2D.c plane.c \
	point.c quad.c shade.c tile.c triangle.c volume.c xfield.c \
	xwindow.c zclipT.c zclipQ.c  notify.c pick.c

CLEANFILES = \
	buffer.c shade.c triangle.c quad.c plane.c \
	\
	arrayClass.c cameraClass.c clippedClass.c fieldClass.c groupClass.c \
	lightClass.c objectClass.c privateClass.c screenClass.c stringClass.c \
	xformClass.c interpClass.c fieldinterpClass.c groupinterpClass.c \
	fle2DClass.c linesII1DClass.c linesRR1DClass.c linesRI1DClass.c \
	trisRI2DClass.c quadsRR2DClass.c cubesIIClass.c cubesRRClass.c \
	tetrasClass.c quadsII2DClass.c \
	\
	arrayClass.h cameraClass.h clippedClass.h fieldClass.h groupClass.h \
	lightClass.h objectClass.h privateClass.h screenClass.h stringClass.h \
	xformClass.h interpClass.h fieldinterpClass.h groupinterpClass.h \
	fle2DClass.h linesII1DClass.h linesRR1DClass.h linesRI1DClass.h \
	trisRI2DClass.h quadsRR2DClass.h cubesIIClass.h cubesRRClass.h \
	tetrasClass.h quadsII2DClass.h 

SUFFIXES = .Z .X .h .c .o .s .i

include libdx.mf
