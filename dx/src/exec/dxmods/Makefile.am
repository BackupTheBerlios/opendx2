## Process this file with automake to produce Makefile.in

INCLUDES = -D$(ARCH) -I$(DXROOT)/include -I../dpexec
MKDEP = gcc -M -MG $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

dxdir = $(DXROOT)
dxincludedir = $(DXROOT)/include/dx
dxmdfdir = $(DXROOT)/lib
noinst_LIBRARIES = libDXMODS.a
SUFFIXES = .c .y .c .s .h .o .a 

BUILT_SOURCES = user.c

dxmdf_DATA = dx.mdf

libDXMODS_a_SOURCES =  \
	ambientlight.c append.c arrange.c attribute.c \
	autocolor.c autoaxes.c autoglyph.c autogray.c \
	autoregrid.c band.c cachescene.c camera.c \
	caption.c categorize.c catstats.c changetype.c \
	changemember.c clipbox.c clipplane.c collect.c \
	collectmulti.c collectnamed.c collectser.c color.c \
	colorbar.c colormap.c compute.c compute2.c connect.c \
	construct.c convert.c copy.c describe.c direction.c \
	display.c divcurl.c dxlmessage.c dxlinnamed.c \
	dxloutvalue.c echo.c enumerate.c equalize.c executive.c \
	export.c extract.c facenormals.c filter.c format.c \
	fourier.c getscene.c getset.c glyph.c gradient.c \
	grid.c histogram.c imagemessage.c import.c import_ss.c \
	include.c inquire.c isolate.c isosurface.c integer.c \
	integerlist.c keyin.c light.c list.c lookup.c \
	loop.c macroutil.c map.c maptoplane.c mark.c \
	measure.c message.c normals.c options.c overlay.c \
	parse.c partition.c pick.c pickinv.c pie.c plot.c \
	post.c print.c programctl.c quantize.c rdimagewin.c \
	readimage.c reduce.c refine.c regrid.c remove.c \
	rename.c render.c reorient.c replace.c ribbon.c \
	rotate.c route.c rubbersheet.c sample.c scalar.c \
	scalarlist.c scale.c scalescreen.c screen.c select.c \
	selector.c sequencer.c shade.c showboundary.c showbox.c \
	showconnect.c showposition.c slab.c slice.c \
	sort.c stack.c statistics.c streakline.c streamline.c \
	stringlegend.c superstate.c superwin.c switch.c system.c \
	text.c toggle.c trace.c transform.c translate.c \
	transpose.c tube.c unmark.c usage.c vector.c \
	vectorlist.c verify.c visualobject.c writeimage.c \
	simplesurf.c dxmdf.src \
	\
	user.c \
	\
	_autocolor.c _autogray.c \
	_cat_util.c _color.c _colormap.c _complex.c \
	_compoper.c _compoper1.c _compoper2.c _compcmplx.c \
	_compinput.c _compexec.c _compparse.y _compputils.c \
	_connectgrids.c _connectvor.c _construct.c _divcurl.c \
	_getfield.c _gif.c _glyph.c _gradient.c \
	_grid.c _helper_jea.c _irregstream.c _isosurface.c \
	_maptoplane.c _newtri.c _normals.c _partnbrs.c \
	_plot.c _post.c _postscript.c _refine.c \
	_refineirr.c _refinereg.c _refinetopo.c _regstream.c \
	_rgb_image.c _rubbersheet.c _rw_image.c _sample.c \
	_simplesurf.c _tiff.c _tube.c _unpart.c \
	bounds.c definter.c exp_gai.c genimp.c \
	genimp_io.c genimp_parse.c importtable.c import_cdf.c \
	import_cm.c import_hdf.c import_ncdf.c private.c \
	separate.c superwinX.c tracevisual.c vectors.c \
	vrml.c eigen.c vsincos.c


.l.c:
	lex $(LFLAGS) $*.l

user.c:  dx.mdf
	@echo user.c rule
	awk -f $(DXROOT)/lib/mdf2c.awk < dx.mdf > user.c

dx.mdf:  dxmdf.src
	-rm -f dx.mdf
	sed '4q' dxmdf.src > dx.mdf
	sed '1,4d' dxmdf.src > userTmp.c
	$(CPP) $(MDF) -DCPLUSPLUS_UI -DEXECUTIVE_MODS userTmp.c >>dx.mdf

.c.c:
	echo "#line 1 \"$*.c\"" | cat - $*.c > $*.c

.y.c:
	yacc -vd $*.y
	sed -e "s/yy/_dxfcc/g" -e "s/YY/_CC/g" y.tab.h > $*.h
	rm y.tab.h
	sed -e "s/yy/_dxfcc/g" -e "s/YY/_CC/g" y.tab.c > $*.c
	rm y.tab.c

.y.h:
	yacc -vd $*.y
	sed -e "s/yy/_dxfcc/g" -e "s/YY/_CC/g" y.tab.h > $*.h
	rm y.tab.h
	sed -e "s/yy/_dxfcc/g" -e "s/YY/_CC/g" y.tab.c > $*.c
	rm y.tab.c

.y.o:
	yacc -vd $*.y
	sed -e "s/yy/_dxfcc/g" -e "s/YY/_CC/g" y.tab.h > $*.h
	rm y.tab.h
	sed -e "s/yy/_dxfcc/g" -e "s/YY/_CC/g" y.tab.c > $*.c
	rm y.tab.c
	$(CC) $(CFLAGS) -c $*.c

