javaclassdir = $(DXINST)/java/htmlpages
javaclass_DATA = samples.jar
EXTRA_DIST = $(JAVA_FILES) $(WRL_USERS)
samples.jar:
	javac -classpath $(WRL_CLASSPATH):$(javaclassdir)/dx.jar $(JAVA_FILES)
	if test -z "$(WRL_CLASSPATH)" ; then \
	javac -classpath $(WRL_CLASSPATH):$(javaclassdir)/dx.jar $(WRL_USERS); \
	fi ;
	$(JDKBIN)/jar cf samples.jar *.class


WRL_USERS = ThunderGlyphSheet.java Navigation.java
OMIT_WRL =

JAVA_FILES = AutoInsurance.java CCNet2.java GroceryList.java HomeOwn.java MRI_2.java MutualFund.java  ScatterData.java Streamline.java Topo.java ddi.java gordon.java hedge.java ibmqw.java npvcall.java optval.java wacc.java

