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
	tetrasClass.X quadsII2DClass.X

BUILT_SOURCES = \
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

SUFFIXES = .X .h .c .o .s .i


.X.h:
	rm -f $*.h
	./class -h $*.X >$*.h

.X.c:
	rm -f $*.c
	./class -c $*.X > $*.c

.X.o:
	rm -f $*.c
	./class -c $*.X >$*.c
	$(COMPILE) -c $*.c

.c.i:
	$(CC) $(CFLAGS) -P $*.c

buffer.o: buffer.c
	rm -f buffer_.c
	sed -e 's/[ 	][ 	]*\$$/ $$/' buffer.c > __buffer.c
	$(CPP) $(DEFS) $(INCLUDES) $(CFLAGS) -E __buffer.c \
	| tr -s '$$\012' '\012\012' \
	| sed -e '/^#/d'  \
	| sed -e 's/[^#]pragma/#pragma/'  > buffer_.c
	rm -f __buffer.c
	$(COMPILE) $(CFLAGS) -c buffer_.c
	mv buffer_.o buffer.o
	rm buffer_.c 

zclipQ.o: zclipQ.c
	$(CC) $(DEFS) $(INCLUDES) $(DEFS) $(CPPFLAGS) -c -g zclipQ.c

shade.o: shade.c
	rm -f shade_.c
	sed -e 's/[ 	][ 	]*\$$/ $$/' shade.c > __shade_.c
	$(CPP) $(DEFS) $(INCLUDES) $(CFLAGS) -E __shade_.c \
	| tr -s '$$\012' '\012\012' \
	| sed -e '/^#/d'  \
	| sed -e 's/DEFINE2/#define/'  \
	| sed -e 's/[^#]pragma/#pragma/'  > shade_.c
	$(COMPILE) $(CFLAGS) -c shade_.c
	mv shade_.o shade.o
	rm shade_.c

triangle.o: triangle.c
	rm -f triangle_.c
	sed -e 's/[ 	][ 	]*\$$/ $$/' triangle.c > __triangle.c
	$(CPP) -E -DPASS1 __triangle.c \
		| sed -e '/^#/d' \
		| sed -e 's/INCLUDE1/#include/' \
		| tr -s '$$\012' '\012\012' > triangle1.c
	$(CPP) -E -DPASS2 -I. triangle1.c \
		| sed -e '/^#/d' \
		| sed -e 's/INCLUDE2/#include/' \
		| tr -s '$$\012' '\012\012' > triangle2.c
	$(CPP) $(DEFS) $(INCLUDES) $(CFLAGS) -E -DPASS3 triangle2.c \
		| tr -s '$$\012' '\012\012' \
		| sed -e '/^#/d' \
		| sed -e 's/DEFINE3/#define/' \
		| sed -e 's/[^#]pragma/#pragma/' >triangle_.c
	/bin/rm triangle1.c triangle2.c __triangle.c
	$(COMPILE) $(DEFS) $(INCLUDES) $(CFLAGS) -c triangle_.c
	mv triangle_.o triangle.o
	/bin/rm -f triangle_.c 

quad.o: quad.c
	rm -f quad_.c
	sed -e 's/[ 	][ 	]*\$$/ $$/' quad.c > __quad.c
	$(CPP) -E -DPASS1 __quad.c \
		| sed -e '/^#/d' \
		| sed -e 's/INCLUDE1/#include/' \
		| tr -s '$$\012' '\012\012' > quad1.c
	$(CPP) -E -DPASS2 -I. quad1.c \
		| sed -e '/^#/d' \
		| sed -e 's/INCLUDE2/#include/' \
		| tr -s '$$\012' '\012\012' > quad2.c
	$(CPP) $(DEFS) $(INCLUDES) $(CFLAGS) -E -DPASS3 quad2.c \
		| tr -s '$$\012' '\012\012' \
		| sed -e '/^#/d' \
		| sed -e 's/DEFINE3/#define/' \
		| sed -e 's/[^#]pragma/#pragma/' >quad_.c
	/bin/rm quad1.c quad2.c __quad.c
	$(COMPILE) $(DEFS) $(INCLUDES) $(CFLAGS) -c quad_.c
	mv quad_.o quad.o
	rm -f quad_.c

plane.o: plane.c
	rm -f plane_.c
	$(CPP) $(DEFS) $(INCLUDES) $(CFLAGS) -E plane.c \
	        | tr -s '$$\012' '\012\012' \
	        | sed -e '/^#/d' \
	        | sed -e 's/[^#]pragma/#pragma/' >plane_.c
	$(COMPILE) $(DEFS) $(INCLUDES) $(CFLAGS) -c plane_.c
	mv plane_.o plane.o
	rm -f plane_.c
