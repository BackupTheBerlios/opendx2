javaclassdir = $(DXINST)/java/htmlpages
javaclass_DATA = samples.jar
EXTRA_DIST = $(JAVA_FILES) $(WRL_USERS)

CLEANFILES = samples.jar

CLASSPATH := $(CLASSPATH):@WRL_CLASSPATH@:@JDK_CLASSPATH@:@DX_JAR@:.
export CLASSPATH

samples.jar:
	@for i in $(JAVA_FILES) ; do		\
	  echo " $(JAVAC) $$i" ;		\
	  $(JAVAC) $$i ;			\
	done ;
	@if test -n "$(WRL_CLASSPATH)" ; then 	\
	  for i in $(WRL_USERS) ; do		\
	    echo " $(JAVAC) $$i" ;		\
	    $(JAVAC) $$i; 			\
	  done ;				\
	fi ;
	$(JAR) cf samples.jar *.class


WRL_USERS = ThunderGlyphSheet.java Navigation.java

JAVA_FILES = AutoInsurance.java CCNet2.java GroceryList.java \
	HomeOwn.java MRI_2.java MutualFund.java  ScatterData.java \
	Streamline.java Topo.java ddi.java gordon.java hedge.java \
	ibmqw.java npvcall.java optval.java wacc.java

clean-local:
	rm -f *.class
