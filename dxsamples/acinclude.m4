dnl
dnl  Locate the dx installation. If not found then can default to where it would
dnl  go with a default install of OpenDX.
dnl
AC_DEFUN(DX_INSTALL_PATH,
[
DX_DEFAULT_INST=/usr/local/dx

if test "x${prefix}" = "xNONE" ; then
  AC_CHECK_PROGS( DX, dx )
  if test -n "$DX" ; then
    AC_MSG_CHECKING([for path via "dx -whereami"])
    DXINST=""
    DXINST=`$DX -whereami | grep "installed in" | sed -e "s/installed in //"`
    if test -z "$DXINST" ; then
	AC_MSG_RESULT([old version of dx script])
	AC_MSG_CHECKING([for /usr/local/bin/dx])
	if test -r "/usr/local/bin/dx" ; then
	  DXINST=`/usr/local/bin/dx -whereami | grep "installed in" | sed -e "s/installed in //"`
	  if test -z "$DXINST" ; then
	   	DXINST=$DX_DEFAULT_INST
	   	AC_MSG_RESULT([old version of dx script, defaulting to $DXINST])
	  else
	   	AC_MSG_RESULT([installed in $DXINST])	
	  fi
	else
	  DXINST=$DX_DEFAULT_INST
	  AC_MSG_RESULT([no /usr/local/bin/dx, setting to $DXINST])
	fi
    else
	AC_MSG_RESULT($DXINST)
    fi
  else
    AC_MSG_CHECKING([for /usr/local/bin/dx])
    if test -r "/usr/local/bin/dx" ; then
	DXINST=`/usr/local/bin/dx -whereami | grep "installed in" | sed -e "s/installed in //"`
	if test -z "$DXINST" ; then
   	 	DXINST=$DX_DEFAULT_INST
   		AC_MSG_RESULT([old version of dx script, setting to $DXINST])
	else
   		AC_MSG_RESULT([installed in $DXINST])	
	fi
     else
   	DXINST=$DX_DEFAULT_INST
	AC_MSG_RESULT([no dx, setting to $DXINST])
     fi
  fi
else
  AC_MSG_CHECKING(for dx path)
  DXINST=$prefix
  AC_MSG_RESULT(using --prefix value $DXINST)
fi

dnl Don't forget to set it once found!
prefix=$DXINST
])

dnl
dnl  DX_PROG_JAVAC([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_PROG_JAVAC,[
AC_CHECKING([for java compiler])
if test -n "$JAVAC"; then
  AC_MSG_WARN(JAVAC was preset)
  AC_CHECK_PROG(JAVAC, $JAVAC)
else
  AC_CHECK_PROGS(JAVAC, javac "gcj -C" guavac jikes)
fi
if test -z "$JAVAC"; then
  AC_MSG_WARN(No java compiler found)
  ifelse([$2], , , [$2])
else
  DX_PROG_JAVAC_WORKS($JAVAC, $1, $2)
fi
])


dnl
dnl  DX_PROG_JAVAC_WORKS(JAVA-COMPILER, [ACTION-IF-TRUE [, ACTION-IF-FALSE]])
dnl  This will fail if the CLASSPATH is bad--that is what we want.
dnl  -------------------------------------------------------------
AC_DEFUN(DX_PROG_JAVAC_WORKS,[
AC_MSG_CHECKING([if $1 works...])
dx_test_java_classname="dx_conf"
dx_test_java_prog=$dx_test_java_classname".java"
dx_test_java_class=$dx_test_java_classname".class"
cat << EOF_JAVA > $dx_test_java_prog

public class $dx_test_java_classname extends Object {
  public static void main() {
    }
}
EOF_JAVA

if AC_TRY_COMMAND($1 $dx_test_java_prog) >/dev/null 2>&1; then
  AC_MSG_RESULT(yes)
  ifelse([$2], , , [$2])
else
 AC_MSG_RESULT(no)
 ifelse([$3], , , [$3])
 AC_MSG_WARN([$1 failed to compile (see config.log, check your CLASSPATH?)])
fi
rm -f $dx_test_java_prog $dx_test_java_class
])


dnl
dnl  DX_PROG_JAR([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_PROG_JAR,[
AC_CHECKING(for jar)
if test -n "$JAR"; then
  AC_MSG_WARN(JAR was preset)
  AC_CHECK_PROG(JAR, $JAR)
else
  AC_CHECK_PROGS(JAR, jar)
fi
if test -z "$JAR"; then
  AC_MSG_WARN([jar class packager not found in \$PATH])
  ifelse([$2], , , [$2])
else
  ifelse([$1], , , [$1])
fi
])


dnl
dnl  Set up the JavaDX related samples stuff.
dnl  DX_JAVADX_SETUP([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
AC_DEFUN(DX_JAVADX_SETUP,
[
AC_MSG_CHECKING(for JavaDX files)
DX_JAR=""
WRL_CLASSPATH=""
if test -r $DXINST/java/javainfo ; then
  WRL_CLASSPATH=`cat $DXINST/java/javainfo | grep WRL_CLASSPATH | sed -e "s/WRL_CLASSPATH //"`
fi
if test -r $DXINST/java/htmlpages/dx.jar ; then
  DX_JAR=$DXINST/java/htmlpages/dx.jar
  AC_MSG_RESULT([$DX_JAR])
  ifelse([$1], , , [$1])
else
  AC_MSG_RESULT([dx.jar not found or not readable])
  ifelse([$2], , , [$2])
fi
])

