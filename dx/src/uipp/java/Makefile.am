## Process this file with automake to produce Makefile.in
##
## There are 2 build happening here: client side javadx
## and server side javadx.  These 2 builds live together
## because their sources overlap - the dx.protocol
## package is used by each.  The build strategy
## is to call javac on some source which will force
## all the dependencies to be built.  (Java just
## does that for us.)  This way we don't need
## makefiles in subdirs.  This works fine a nightly
## type of build but doesn't work so well as 
## a developer's build.  The -d arg to javac
## causes all resulting .class file to be output
## to the directory arg following the -d.  The
## result is a place which is easy to jar up.
##
javadxdir = $(prefix)/dx/java/htmlpages
javadx_DATA = dx.jar 
javasrvdir = $(prefix)/dx/java/server/class
javasrv_DATA = server.jar 
EXTRA_DIST = $(DX_SRCS) DXServer.java makeall.java makewrl.java exports.awk
javalibdir = $(prefix)/dx/java/server/lib_@ARCH@

javalib_PROGRAMS = @ANYDX@
EXTRA_PROGRAMS = libAnyDX.so AnyDX.dll
libAnyDX_so_SOURCES =
AnyDX_dll_SOURCES =
SUBDIRS = server dx

##
## Using -d simplifies things because all .class files
## are automatically copied into a directory structure
## which allows for quick jarring
##

CLASSPATH = @DX_JAVA_CLASSPATH@

export CLASSPATH

dx.jar: makeall.java $(DX_SRCS)
	mkdir -p classes
	if test "$(ARCH)" = "cygwin" -o "$(ARCH)" = "intelnt" ; then \
		tmp=`pwd`/classes ; \
		classdir=`cygpath --windows $$tmp` ; \
	else \
		classdir=`pwd`/classes ; \
	fi ; \
	cd $(srcdir) ; \
	$(JAVAC) -d $$classdir makewrl.java ; \
	$(JAVAC) -d $$classdir makeall.java $(DX_SRCS) ; \
	cd $$classdir ; \
	$(JAR) cf ../dx.jar $(DX_OBJS) dx

server.jar: dx.jar DXServer.java
	mkdir -p dxsc
	if test "$(ARCH)" = "cygwin" -o "$(ARCH)" = "intelnt" ; then \
	        tmp=`pwd`/dxsc ; \
	        dxscdir=`cygpath --windows $$tmp` ; \
	else \
		dxscdir=`pwd`/dxsc ; \
	fi ; \
	cd $(srcdir) ; \
	$(JAVAC) -d $$dxscdir DXServer.java ; \
	cd $$dxscdir ; \
	$(JAR) cf ../server.jar DXServer.class server dx

SHRD_FLAGS = -shared -o libAnyDX.so

libAnyDX.so: DXLink.o
	if test ! "$(ARCH)" = "intelnt" -a ! "$(ARCH)" = "macos" ; then \
		( $(MAKE) usual_shared_object || $(MAKE) aix_shared_object ) \
	elif test "$(ARCH)" = "macos" ; then \
		( $(MAKE) macos_shared_object ) \
	elif test "$(ARCH)" = "intelnt" ; then \
		( $(MAKE) AnyDX.dll ) \
	fi

usual_shared_object:
	$(SHARED_LINK) $(DXABI) $(DX_RTL_LDFLAGS) $(SO_FLAGS) $(SHRD_FLAGS) `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&" -e "s&../dxl/x11.o&&"`  DXLink.o

aix_shared_object:
	ar -ruv tmpAnyDX.a `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&"` DXLink.o
	nm -epC tmpAnyDX.a | awk -f $(srcdir)/exports.awk > tmpAnyDX.exp
	ld -bnoentry -bM:SRE -o libAnyDX.so -bE:tmpAnyDX.exp tmpAnyDX.a -L /usr/lpp/X11/lib -lXt -lX11 -lc
	rm -f tmpAnyDX.*

macos_shared_object:
	ar -ruv tmpAnyDX.a `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&"` DXLink.o
	ld -dylib -o libAnyDX.dylib tmpAnyDX.a -L/usr/X11R6/lib -lXt -lX11 -lc
	rm -f tmpAnyDX.*

#AnyDX.dll: DXLink.o
#	ar -ruv tmpAnyDX.a `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&"` DXLink.o
#	echo EXPORTS > tmpAnyDX.exp
#	nm --demangle --defined-only tmpAnyDX.a | sed -n 's/^.* T //p' >> tmpAnyDX.exp
#	dllwrap -s --export-all-symbols --image-base 0x6620000 --def tmpAnyDX.exp --driver-name gcc -o libAnyDX.dll DXLink.o -L../dxl -lDXL -L/usr/X11R6/lib -lXt -lSM -lICE -lX11
#	rm -f tmpAnyDX.*

AnyDX.dll: DXLink.o
	ar -ruv tmpAnyDX.a `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&"` DXLink.o
	cc /LD -o AnyDX.dll DXLink.o -L../dxl libDXL.a $(LIBS)
	rm -f tmpAnyDX.*



## JINC set by configure via acinclude.m4

DXLink.o:  server.jar
	javaobj=`pwd` ; \
	cd $(top_srcdir) ; \
	srcincs=`pwd`/include ; \
	cd $$javaobj ; \
	cd $(srcdir) ; \
	javasrc=`pwd` ; \
	cd $$javaobj ; \
	if test "$(ARCH)" = "cygwin" -o "$(ARCH)" = "intelnt" ; then \
	        tmp=`pwd`/server ; \
	        srvrdir=`cygpath --windows $$tmp` ; \
	        tmp=`pwd`/dxsc ; \
	        dxscdir=`cygpath --windows $$tmp` ; \
	else \
	        dxscdir=`pwd`/dxsc ; \
	        srvrdir=`pwd`/server ; \
	fi ; \
	cd $$dxscdir ; \
	CLASSPATH="." $(JAVAH) -d \
	        $$srvrdir server.DXServer server.DXServerThread ; \
	cd $$javaobj ; \
	if test "$(ARCH)" = "cygwin" -o "$(ARCH)" = "intelnet" ; then \
		$(CC) $(DXABI) -o $$javaobj/DXLink.o -I$$srcincs -Iserver \
	        -I$(BUILDBASE)/include -I$$javaobj/server \
	        -c -Dintelnt $(JNI_CFLAGS) -I/cygdrive/c/jdk1.1.8/include -I/cygdrive/c/jdk1.1.8/include/win32 $(srcdir)/server/DXLink.c ; \
	else \
		$(CC) $(DXABI) -o $$javaobj/DXLink.o -I$$srcincs -Iserver \
		-I$(BUILDBASE)/include -c -D@ARCH@ $(JNI_CFLAGS) @JINC@ $(srcdir)/server/DXLink.c ; \
	fi ;

##SAMPLE_OBJS = AS400VSMonth.class AutoInsurance.class CCNet2.class \
##	GroceryList.class HomeOwn.class MRI_2.class MappedIso.class \
##	MutualFund.class ScatterData.class SimplifySurface.class \
##	Streamline.class Topo.class TwoWells.class ddi.class \
##	gordon.class hedge.class ibmqw.class mutFun.class npvcall.class \
##	optval.class tgsheet.class wacc.class

##SAMPLE_SRCS = AS400VSMonth.java AutoInsurance.java CCNet2.java \
##	GroceryList.java HomeOwn.java MRI_2.java MappedIso.java \
##	MutualFund.java ScatterData.java SimplifySurface.java Streamline.java \
##	Topo.java TwoWells.java ddi.java gordon.java hedge.java ibmqw.java \
##	mutFun.java npvcall.java optval.java tgsheet.java wacc.java

DX_OBJS = imageWindow.class CaptionLabels.class Status.class
DX_SRCS = imageWindow.java CaptionLabels.java Status.java

CLEANFILES = dx.jar server.jar javainfo

distclean-local:
	rm -rf classes dxsc
