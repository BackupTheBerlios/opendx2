SUFFIXES = .X .Z .h .m .c .o .s .i

.X.h: class.awk
	rm -f $*.h
	sh ./class -h $*.X >$*.h

.X.c: class.awk
	rm -f $*.c
	sh ./class -c $*.X > $*.c

buffer.c: buffer.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' buffer.Z > __buffer.c
	$(CPP) __buffer.c \
	| tr -s "\044" "\012" \
	| sed   -e '/^#/d' \
		-e 's/INCLUDE2/#include/' \
		-e 's/^pragma/#pragma/'  > buffer.c
	rm -f __buffer.c

shade.c: shade.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' shade.Z > __shade_.c
	$(CPP) __shade_.c  \
	| tr -s "\044" "\012" \
	| sed -e '/^#/d' \
		-e 's/DEFINE2/#define/'   \
		-e 's/INCLUDE2/#include/' \
		-e 's/[^#]pragma/#pragma/' > shade.c
	rm -f __shade_.c

triangle.c: triangle.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' triangle.Z > __triangle.c
	$(CPP) -DPASS1 __triangle.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE1/#include/' \
		| tr -s "\044" "\012" > triangle1.c
	$(CPP) -DPASS2 triangle1.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE2/#include/' \
		| tr -s "\044" "\012" > triangle2.c
	$(CPP) -DPASS3 triangle2.c \
		| tr -s "\044" "\012" \
		| sed -e '/^#/d' \
		      -e 's/DEFINE3/#define/' \
		      -e 's/INCLUDE3/#include/' \
		      -e 's/[^#]pragma/#pragma/' > triangle.c
	rm triangle1.c triangle2.c __triangle.c

quad.c: quad.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' quad.Z > __quad.c
	$(CPP) -DPASS1 __quad.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE1/#include/' \
		| tr -s "\044" "\012" > quad1.c
	$(CPP) -DPASS2 quad1.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE2/#include/' \
		| tr -s "\044" "\012" > quad2.c
	$(CPP) -DPASS3 quad2.c \
		| tr -s "\044" "\012" \
		| sed -e '/^#/d' \
		      -e 's/DEFINE3/#define/' \
		      -e 's/INCLUDE3/#include/' \
		      -e 's/[^#]pragma/#pragma/' > quad.c
	rm quad1.c quad2.c __quad.c

plane.c: plane.Z
	cp plane.Z _plane.c
	$(CPP) _plane.c \
	        | tr -s "\044" "\012" \
	        | sed -e '/^#/d' \
		      -e 's/INCLUDE2/#include/' \
	              -e 's/[^#]pragma/#pragma/' > plane.c
	rm _plane.c