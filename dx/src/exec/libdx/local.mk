.X.h: class.awk $*.X
	rm -f $*.h
	sh ./class -h $*.X >$*.h

.X.c: class.awk  $*.X
	rm -f $*.c
	sh ./class -c $*.X > $*.c

buffer.c: buffer.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' buffer.Z > __buffer.c
	xlc -E __buffer.c \
	| tr -s "\044" "\012" \
	| sed   -e '/^#/d' \
		-e 's/INCLUDE2/#include/' \
		-e 's/^pragma/#pragma/'  > buffer.c
	rm -f __buffer.c

shade.c: shade.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' shade.Z > __shade_.c
	xlc -E __shade_.c  \
	| tr -s "\044" "\012" \
	| sed -e '/^#/d' \
		-e 's/DEFINE2/#define/'   \
		-e 's/INCLUDE2/#include/' \
		-e 's/[^#]pragma/#pragma/' > shade.c
	rm -f __shade_.c

triangle.c: triangle.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' triangle.Z > __triangle.c
	xlc -E -DPASS1 __triangle.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE1/#include/' \
		| tr -s "\044" "\012" > triangle1.c
	xlc -E -DPASS2 triangle1.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE2/#include/' \
		| tr -s "\044" "\012" > triangle2.c
	xlc -E -DPASS3 triangle2.c \
		| tr -s "\044" "\012" \
		| sed -e '/^#/d' \
		      -e 's/DEFINE3/#define/' \
		      -e 's/INCLUDE3/#include/' \
		      -e 's/[^#]pragma/#pragma/' > triangle.c
	rm triangle1.c triangle2.c __triangle.c

quad.c: quad.Z
	sed -e 's/[ 	][ 	]*\$$/ $$/' quad.Z > __quad.c
	xlc -E -DPASS1 __quad.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE1/#include/' \
		| tr -s "\044" "\012" > quad1.c
	xlc -E -DPASS2 quad1.c \
		| sed -e '/^#/d' \
		      -e 's/INCLUDE2/#include/' \
		| tr -s "\044" "\012" > quad2.c
	xlc -E -DPASS3 quad2.c \
		| tr -s "\044" "\012" \
		| sed -e '/^#/d' \
		      -e 's/DEFINE3/#define/' \
		      -e 's/INCLUDE3/#include/' \
		      -e 's/[^#]pragma/#pragma/' > quad.c
	rm -f quad1.c quad2.c __quad.c

plane.c: plane.Z
	cp plane.Z _plane.c
	xlc -E _plane.c \
	        | tr -s "\044" "\012" \
	        | sed -e '/^#/d' \
		      -e 's/INCLUDE2/#include/' \
	              -e 's/[^#]pragma/#pragma/' > plane.c
	rm -f _plane.c

