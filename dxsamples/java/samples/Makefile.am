javaclassdir = $(DXINST)/java/htmlpages
javaclass_DATA = samples.jar
EXTRA_DIST = $(JAVA_FILES) $(WRL_USERS)

CLEANFILES = samples.jar

CLASSPATH := .:$(CLASSPATH):@WRL_CLASSPATH@:@DX_JAR@
export CLASSPATH

samples.jar:
	$(JAVAC) $(JAVA_FILES)
	if test -z "$(WRL_CLASSPATH)" ; then \
	   $(JAVAC) $(WRL_USERS); \
	fi ;
	$(JAR) cf samples.jar *.class


WRL_USERS = ThunderGlyphSheet.java Navigation.java

JAVA_FILES = AutoInsurance.java CCNet2.java GroceryList.java \
	HomeOwn.java MRI_2.java MutualFund.java  ScatterData.java \
	Streamline.java Topo.java ddi.java gordon.java hedge.java \
	ibmqw.java npvcall.java optval.java wacc.java

clean-local:
	rm -f *.class
