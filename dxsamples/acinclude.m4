AC_DEFUN(DX_FIND_DX,
[
AC_MSG_CHECKING([for dx installation via dx -whereami, ignore if next response is not found])
DXINST=
DX_DEFAULT_INST=${prefix}/dx
DXINST= `dx -whereami | grep "installed in" | sed -e "s/installed in //" `
if test -z "$DXINST" ; then
	AC_MSG_RESULT([dx not in path or old version of dx script])
	AC_MSG_CHECKING([for dx executable in default /usr/local/bin])
	DXINST=`/usr/local/bin/dx -whereami | grep "installed in" | sed -e "s/installed in //" | sed -e "s/ //"`
	if test -z "$DXINST" ; then
		AC_MSG_RESULT([dx not in /usr/local/bin or old version of dx script, defaulting to $DX_DEFAULT_INST])
		DXINST=$DX_DEFAULT_INST
	     else
		AC_MSG_RESULT([dx reported in $DXINST])	
	fi
     else
	AC_MSG_RESULT(dx is installed in $DXINST)
fi
JBASE=`cat $DXINST/java/javainfo | grep JBASE | sed -e "s/JBASE //"`
JDKBIN=$JBASE/bin
WRL_CLASSPATH=`cat $DXINST/java/javainfo | grep WRL_CLASSPATH | sed -e "s/WRL_CLASSPATH //"`
echo WRL_CLASSPATH $WRL_CLASSPATH
MAKE_WRL="OMIT_WRL"
if ! test -z "$WRL_CLASSPATH" ; then
	MAKE_WRL="WRL_USERS"
	fi
echo MAKE_WRL $MAKE_WRL
])
