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
javainfodir = $(prefix)/dx/java
javainfo_DATA = javainfo
javadxdir = $(prefix)/dx/java/htmlpages
javadx_DATA = dx.jar 
javasrvdir = $(prefix)/dx/java/server/class
javasrv_DATA = server.jar 
EXTRA_DIST = $(DX_SRCS) DXServer.java makeall.java makewrl.java exports.awk
javalibdir = $(prefix)/dx/java/server/lib_@ARCH@
javalib_DATA = libAnyDX.so

SUBDIRS = server dx

##
## Using -d simplifies things because all .class files
## are automatically copied into a directory structure
## which allows for quick jarring
##
javainfo:
	echo JBASE $(JBASE) >javainfo
	
dx.jar: javainfo
	mkdir -p classes
	(CLASSPATH=aaaaa ; unset CLASSPATH ; javac -d classes makeall.java $(DX_SRCS) )
	-(CLASSPATH=@WRL_CLASSPATH@ ; javac -d classes makewrl.java )
	grep -v WRL_CLASSPATH javainfo > javainfo.tmp
	echo WRL_CLASSPATH @WRL_CLASSPATH@ >>javainfo ; \
	rm -f javainfo.tmp
	(CLASSPATH=aaaaa ; unset CLASSPATH ; cd classes; @JDKBIN@jar cf ../dx.jar $(DX_OBJS) dx)

server.jar:
	mkdir -p dxsc
	(CLASSPATH=aaaaa ; unset CLASSPATH ; javac -d dxsc DXServer.java)
	(CLASSPATH=aaaaa ; unset CLASSPATH ; cd dxsc; @JDKBIN@jar cf ../server.jar DXServer.class server dx )

SHRD_FLAGS = -shared -L../dxl -lDXL -o libAnyDX.so

libAnyDX.so: DXLink.o
	( $(MAKE) usual_shared_object || $(MAKE) aix_shared_object )

usual_shared_object:
	$(CC) $(SHRD_FLAGS) `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&"`  DXLink.o

aix_shared_object:
	ar -ruv tmpAnyDX.a `ls ../dxl/*.o | sed -e "s&../dxl/object.o&&"` DXLink.o
	nm -epC tmpAnyDX.a | awk -f exports.awk > tmpAnyDX.exp
	ld -bnoentry -bM:SRE -o libAnyDX.so -bE:tmpAnyDX.exp tmpAnyDX.a -L /usr/lpp/X11/lib -lXt -lX11 -lc
	rm -f tmpAnyDX.*



## JBASE and JINC set by configure via acinclude.m4
JBASE = @JBASE@
JINC = -I$(JBASE)/include -I$(JBASE)/include/@JAVA_ARCH@ -I$(JBASE)/include/java -I$(JBASE)/include/java/@JAVA_ARCH@

DXLink.o:  server.jar
	(CLASSPATH=aaaaa ; unset CLASSPATH ; cd dxsc; @JDKBIN@javah -jni -d ../server server.DXServer server.DXServerThread)
	(cd server; $(CC) -o ../DXLink.o -I../../../../include -c -D@ARCH@ $(CFLAGS) $(JINC) DXLink.c)


##SAMPLE_OBJS = AS400VSMonth.class AutoInsurance.class CCNet2.class GroceryList.class HomeOwn.class MRI_2.class MappedIso.class MutualFund.class ScatterData.class SimplifySurface.class Streamline.class Topo.class TwoWells.class ddi.class gordon.class hedge.class ibmqw.class mutFun.class npvcall.class optval.class tgsheet.class wacc.class

##SAMPLE_SRCS = AS400VSMonth.java AutoInsurance.java CCNet2.java GroceryList.java HomeOwn.java MRI_2.java MappedIso.java MutualFund.java ScatterData.java SimplifySurface.java Streamline.java Topo.java TwoWells.java ddi.java gordon.java hedge.java ibmqw.java mutFun.java npvcall.java optval.java tgsheet.java wacc.java

DX_OBJS = imageWindow.class CaptionLabels.class Status.class
DX_SRCS = imageWindow.java CaptionLabels.java Status.java

clean:
	rm -rf classes dxsc
	rm -f *.class
	rm -f dx.jar
	rm -f server.jar
	rm -f libAnyDX.so
	rm -f DXLink.o
	rm -f javainfo


