AC_DEFUN(AC_CYGWIN,
[AC_CACHE_CHECK(for Cygwin environment, ac_cv_cygwin,
[AC_TRY_COMPILE(,[
#ifndef __CYGWIN__
#define __CYGWIN__ __CYGWIN32__
#endif
return __CYGWIN__;],
ac_cv_cygwin=yes, ac_cv_cygwin=no)
rm -f conftest*])
CYGWIN=
test "$ac_cv_cygwin" = yes && CYGWIN=yes])

AC_DEFUN(AC_EXEEXT,
[AC_REQUIRE([AC_CYGWIN])
AC_MSG_CHECKING([for executable suffix])
AC_CACHE_VAL(ac_cv_exeext,
[if test "$CYGWIN" = yes || test "$MINGW32" = yes; then
  ac_cv_exeext=.exe
else
  rm -f conftest*
  echo 'int main () { return 0; }' > conftest.$ac_ext
  ac_cv_exeext=
  if AC_TRY_EVAL(ac_link); then
    for file in conftest.*; do
      case $file in
      *.c | *.o | *.obj) ;;
      *) ac_cv_exeext=`echo $file | sed -e s/conftest//` ;;
      esac
    done
  else
    AC_MSG_ERROR([installation or configuration problem: compiler cannot create executables.])
  fi
  rm -f conftest*
  test x"${ac_cv_exeext}" = x && ac_cv_exeext=no
fi])
EXEEXT=""
test x"${ac_cv_exeext}" != xno && EXEEXT=${ac_cv_exeext}
AC_MSG_RESULT(${ac_cv_exeext})
dnl Setting ac_exeext will implicitly change the ac_link command.
ac_exeext=$EXEEXT
AC_SUBST(EXEEXT)])

AC_DEFUN(DX_CHECK_HEADER,
[dnl Do the transliteration at runtime so arg 1 can be a shell variable.
ac_safe=`echo "$1" | sed 'y%./+-%__p_%'`
AC_MSG_CHECKING([for $1])
AC_CACHE_VAL(ac_cv_header_$ac_safe,
[DX_TRY_CPP([#include <$1>], eval "ac_cv_header_$ac_safe=yes",
  eval "ac_cv_header_$ac_safe=no")])dnl
if eval "test \"`echo '$ac_cv_header_'$ac_safe`\" = yes"; then
  AC_MSG_RESULT(yes)
  ifelse([$2], , :, [$2])
else
  AC_MSG_RESULT(no)
ifelse([$3], , , [$3
])dnl
fi
])

AC_DEFUN(DX_CHECK_HEADERS,
[for ac_hdr in $1
do
DX_CHECK_HEADER($ac_hdr,
[changequote(, )dnl
  ac_tr_hdr=HAVE_`echo $ac_hdr | sed 'y%abcdefghijklmnopqrstuvwxyz./-%ABCDEFGHIJKLMNOPQRSTUVWXYZ___%'`
changequote([, ])dnl
  AC_DEFINE_UNQUOTED($ac_tr_hdr) $2], $3)dnl
done
])

dnl DX_TRY_CPP(INCLUDES, [ACTION-IF-TRUE [, ACTION-IF-FALSE]])
AC_DEFUN(DX_TRY_CPP,
[DX_REQUIRE_CPP()dnl
cat > conftest.$ac_ext <<EOF
[#]line __oline__ "configure"
#include "confdefs.h"
[$1]
EOF
dnl Capture the stderr of cpp.  eval is necessary to expand ac_cpp.
dnl We used to copy stderr to stdout and capture it in a variable, but
dnl that breaks under sh -x, which writes compile commands starting
dnl with ` +' to stderr in eval and subshells.
ac_try="$ac_cpp conftest.$ac_ext >conftest.out 2>conftest.err"
AC_TRY_EVAL(ac_try)
ac_err=`grep -v '^ *+' conftest.err | grep -v "^conftest.${ac_ext}\$"`
if test -z "$ac_err"; then
  ifelse([$2], , :, [rm -rf conftest*
  $2])
else
  echo "$ac_err" >&AC_FD_CC
  echo "configure: failed program was:" >&AC_FD_CC
  cat conftest.$ac_ext >&AC_FD_CC
ifelse([$3], , , [  rm -rf conftest*
  $3
])dnl
fi
rm -f conftest*])

dnl Require finding the C or C++ preprocessor, whichever is the
dnl current language.
AC_DEFUN(DX_REQUIRE_CPP,
[ifelse(AC_LANG, C, [AC_REQUIRE([DX_PROG_CPP])], [AC_REQUIRE([DX_PROG_CXXCPP])])])

AC_DEFUN(DX_PROG_CXXCPP,
[AC_MSG_CHECKING(how to run the C++ preprocessor)
if test -z "$CXXCPP"; then
AC_CACHE_VAL(ac_cv_prog_CXXCPP,
[AC_LANG_SAVE[]dnl
AC_LANG_CPLUSPLUS[]dnl
  CXXCPP="${CXX-g++} -E"
  DX_TRY_CPP([#include <stdlib.h>], , CXXCPP=/lib/cpp)
  ac_cv_prog_CXXCPP="$CXXCPP"
AC_LANG_RESTORE[]dnl
fi])dnl
CXXCPP="$ac_cv_prog_CXXCPP"
AC_MSG_RESULT($CXXCPP)
AC_SUBST(CXXCPP)dnl
])

AC_DEFUN(DX_PROG_CPP,
[AC_MSG_CHECKING(how to run the C preprocessor)
# On Suns, sometimes $CPP names a directory.
if test -n "$CPP" && test -d "$CPP"; then
  CPP=
fi
if test -z "$CPP"; then
AC_CACHE_VAL(ac_cv_prog_CPP,
[  # This must be in double quotes, not single quotes, because CPP may get
  # substituted into the Makefile and "${CC-cc}" will confuse make.
  CPP="${CC-cc} -E"
  # On the NeXT, cc -E runs the code through the compiler's parser,
  # not just through cpp.
dnl Use a header file that comes with gcc, so configuring glibc
dnl with a fresh cross-compiler works.
  DX_TRY_CPP([#include <assert.h>
Syntax Error], ,
  CPP="${CC-cc} -E -traditional-cpp"
  DX_TRY_CPP([#include <assert.h>
Syntax Error], ,
  CPP="${CC-cc} -nologo -E"
  DX_TRY_CPP([#include <assert.h>
Syntax Error], , CPP=/lib/cpp)))
  ac_cv_prog_CPP="$CPP"])dnl
  CPP="$ac_cv_prog_CPP"
else
  ac_cv_prog_CPP="$CPP"
fi
AC_MSG_RESULT($CPP)
AC_SUBST(CPP)dnl
])


AC_DEFUN(DX_PROG_CC_GNU,
[AC_CACHE_CHECK(whether we are using GNU C, ac_cv_prog_gcc,
[dnl The semicolon is to pacify NeXT's syntax-checking cpp.
cat > conftest.c <<EOF
#ifdef __GNUC__
  yes;
#endif
EOF
if AC_TRY_COMMAND(${CC-cc} -E conftest.c) | egrep yes > foo 2>&1; then
  ac_cv_prog_gcc=yes
else
  ac_cv_prog_gcc=no
fi
rm foo
])])

AC_DEFUN(DX_PROG_CXX_GNU,
[AC_CACHE_CHECK(whether we are using GNU C++, ac_cv_prog_gxx,
[dnl The semicolon is to pacify NeXT's syntax-checking cpp.
cat > conftest.C <<EOF
#ifdef __GNUC__
  yes;
#endif
EOF
if AC_TRY_COMMAND(${CXX-g++} -E conftest.C) | egrep yes > foo 2>&1; then
  ac_cv_prog_gxx=yes
else
  ac_cv_prog_gxx=no
fi
rm foo
])])
AC_DEFUN(DX_PROG_CC,
[AC_BEFORE([$0], [AC_PROG_CPP])dnl
AC_CHECK_PROG(CC, gcc, gcc)
if test -z "$CC"; then
  AC_CHECK_PROG(CC, cc, cc, , , /usr/ucb/cc)
  if test -z "$CC"; then
    case "`uname -s`" in
    *win32* | *WIN32*)
      AC_CHECK_PROG(CC, cl, cl) ;;
    esac
  fi
  test -z "$CC" && AC_MSG_ERROR([no acceptable cc found in \$PATH])
fi

AC_PROG_CC_WORKS
DX_PROG_CC_GNU

if test $ac_cv_prog_gcc = yes; then
  GCC=yes
else
  GCC=
fi

dnl Check whether -g works, even if CFLAGS is set, in case the package
dnl plays around with CFLAGS (such as to build both debugging and
dnl normal versions of a library), tasteless as that idea is.
ac_test_CFLAGS="${CFLAGS+set}"
ac_save_CFLAGS="$CFLAGS"
CFLAGS=
AC_PROG_CC_G
if test "$ac_test_CFLAGS" = set; then
  CFLAGS="$ac_save_CFLAGS"
elif test $ac_cv_prog_cc_g = yes; then
  if test "$GCC" = yes; then
    CFLAGS="-g -O2"
  else
    CFLAGS="-g"
  fi
else
  if test "$GCC" = yes; then
    CFLAGS="-O2"
  else
    CFLAGS=
  fi
fi
])

AC_DEFUN(DX_PROG_CXX,
[AC_BEFORE([$0], [AC_PROG_CXXCPP])dnl
AC_CHECK_PROGS(CXX, $CCC c++ g++ gcc CC cxx cc++ cl, gcc)

AC_PROG_CXX_WORKS
DX_PROG_CXX_GNU

if test $ac_cv_prog_gxx = yes; then
  GXX=yes
else
  GXX=
fi

dnl Check whether -g works, even if CXXFLAGS is set, in case the package
dnl plays around with CXXFLAGS (such as to build both debugging and
dnl normal versions of a library), tasteless as that idea is.
ac_test_CXXFLAGS="${CXXFLAGS+set}"
ac_save_CXXFLAGS="$CXXFLAGS"
CXXFLAGS=
AC_PROG_CXX_G
if test "$ac_test_CXXFLAGS" = set; then
  CXXFLAGS="$ac_save_CXXFLAGS"
elif test $ac_cv_prog_cxx_g = yes; then
  if test "$GXX" = yes; then
    CXXFLAGS="-g -O2"
  else
    CXXFLAGS="-g"
  fi
else
  if test "$GXX" = yes; then
    CXXFLAGS="-O2"
  else
    CXXFLAGS=
  fi
fi
])
AC_DEFUN(DX_ARCHITECTURE,
[
    AC_MSG_CHECKING(architecture type)
    unameS=`uname -s`
    unameM=`uname -m`
    ARCH=unknown
    if test $unameS = "CYGWIN_95-4.0" ; then
    	ARCH=cygwin
    fi
    if test $unameS = "Linux" ; then
	isit=`echo $unameM | egrep "i.86"`
	if test ! -z "$isit" ; then
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
    if test $unameS = "SunOS" ; then
        ARCH=solaris
    fi
    AC_MSG_RESULT($ARCH)
    AC_SUBST(ARCH)
    AC_DEFINE_UNQUOTED($ARCH)
    AC_DEFINE_UNQUOTED(DXD_ARCHNAME, "$ARCH")
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
