AC_DEFUN(DX_ARCHITECTURE,
[
    AC_MSG_CHECKING(architecture type)
    unameS=`uname -s`
    unameM=`uname -m`
    ARCH=unknown
    if test $unameS = "CYGWIN_95-4.0" ; then
    	ARCH=intelnt
    fi
    if test $unameS = "Linux" ; then
        if test $unameM = "i686" ; then
	    ARCH=linux86 
	else
	    ARCH=unknown 
	fi
    fi
    if test $unameS = "IRIX" || test $unameS = "IRIX64" ; then
    	ARCH=sgi
    fi
    if test $unameS = "AIX" ; then
    	ARCH=ibm6000
    fi
    if test $unameM = "alpha" ; then
        ARCH=alphax
    fi
    if test $unameS = "HP_UX" ; then
        ARCH=hp700
    fi
    AC_MSG_RESULT($ARCH)
    AC_SUBST(ARCH)
    AC_DEFINE_UNQUOTED($ARCH)
])

AC_DEFUN(DX_STREAM_O2,
[
    AC_MSG_CHECKING(whether -O2 interferes with fstream in C++)
    ac_ext=C
    AC_TRY_LINK(
 [
 #include <stdio.h>
 #include <stdarg.h>
 #include <fstream.h>
 ],
 [
 ifstream *i = new ifstream("foo");
 ],
 AC_MSG_RESULT(no)
 ,
 CXXFLAGS=`echo $CXXFLAGS | sed "s/-O2//"`
 AC_MSG_RESULT(yes)
    )
])

AC_DEFUN(DX_HEADER_HAS_SYMBOL,
[
    AC_MSG_CHECKING(whether header file $1 contains symbol $2)
    ac_ext=C
    AC_EGREP_CPP(yes, 
	[#include <$1>
	#ifdef $2
	yes
	#endif
	], found="yes", found="no")
    if test $found = "no" ; then
	AC_EGREP_HEADER($2, $1, found="yes", found="no")
    fi
    if test $found = "yes" ; then 
	AC_DEFINE_UNQUOTED(HAS_$2)
	AC_MSG_RESULT("yes")
    else
	AC_MSG_RESULT("no")
    fi
])
