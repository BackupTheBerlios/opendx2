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
    if test "$ARCH" = "" ; then
	unameS=`uname -s`
	unameM=`uname -m`
	ARCH=unknown
	if test $unameS = "FreeBSD" ; then
	    ARCH=freebsd
	    JAVA_ARCH=fixme
	fi
	if test `echo $unameS | tr A-Z a-z | sed "s/^.*cygwin.*$/yes/"` = "yes" ; then
	    ARCH=cygwin
	    JAVA_ARCH=fixme
	fi
	if test $unameS = "Linux" ; then
	    ARCH=linux 
	    JAVA_ARCH=genunix
	fi
	if test $unameS = "IRIX" || test $unameS = "IRIX64" ; then
	    ARCH=sgi
	    JAVA_ARCH=irix
	fi
	if test $unameS = "AIX" ; then
	    ARCH=ibm6000
	    JAVA_ARCH=aix
	fi
	if test $unameM = "alpha" ; then
	    ARCH=alphax
	    JAVA_ARCH=alpha
	fi
	if test $unameS = "HP-UX" ; then
	    ARCH=hp700
	    JAVA_ARCH=hp-ux
	fi
	if test $unameS = "SunOS" ; then
	    ARCH=solaris
	    JAVA_ARCH=solaris
	fi
    fi
    AC_MSG_RESULT($ARCH)
    AC_SUBST(ARCH)
    AC_DEFINE_UNQUOTED($ARCH)
    AC_DEFINE_UNQUOTED(DXD_ARCHNAME, "$ARCH")
])

AC_DEFUN(DX_STREAM_O2,
[
    AC_MSG_CHECKING(whether -O2 interferes with fstream in C++)
    AC_LANG_CPLUSPLUS
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

dnl Borrowed from acspecific  and modified to add paths to Xm headers
dnl and libs if different from X11
dnl Set xm_includes and/or xm_libraries.
AC_DEFUN(DX_PATH_XM,
[
  # Guess where to find include files, by looking for this one Xm .h file.
  test -z "$xm_direct_test_include" && xm_direct_test_include=Xm/Xm.h

  # First, try using that file with no special directory specified.
AC_TRY_CPP([#include <$xm_direct_test_include>],
[# We can compile using X headers with no special include directory.
xm_includes=],
[# Look for the header file in a standard set of common directories.
# Check X11 before X11Rn because it is often a symlink to the current release.
  for ac_dir in               \
    /usr/X11/include          \
    /usr/X11R6/include        \
    /usr/X11R5/include        \
    /usr/X11R4/include        \
                              \
    /usr/include/X11          \
    /usr/include/X11R6        \
    /usr/include/X11R5        \
    /usr/include/X11R4        \
                              \
    /usr/local/X11/include    \
    /usr/local/X11R6/include  \
    /usr/local/X11R5/include  \
    /usr/local/X11R4/include  \
                              \
    /usr/local/include/X11    \
    /usr/local/include/X11R6  \
    /usr/local/include/X11R5  \
    /usr/local/include/X11R4  \
                              \
    /usr/X386/include         \
    /usr/x386/include         \
    /usr/XFree86/include/X11  \
                              \
    /usr/include              \
    /usr/local/include        \
    /usr/unsupported/include  \
    /usr/athena/include       \
    /usr/local/x11r5/include  \
    /usr/lpp/Xamples/include  \
                              \
    /usr/openwin/include      \
    /usr/openwin/share/include \
    ; \
  do
    if test -r "$ac_dir/$xm_direct_test_include"; then
      xm_includes=$ac_dir
      break
    fi
  done])

  # Check for the libraries.

  test -z "$xm_direct_test_library" && xm_direct_test_library=Xm
  test -z "$xm_direct_test_function" && xm_direct_test_function=XmGetDestination

  # See if we find them without any special options.
  # Don't add to $LIBS permanently.
  ac_save_LIBS="$LIBS"
  LIBS="-l$xm_direct_test_library $LIBS"
AC_TRY_LINK(, [${xm_direct_test_function}()],
[LIBS="$ac_save_LIBS"
# We can link X programs with no special library path.
xm_libraries=],
[LIBS="$ac_save_LIBS"
# First see if replacing the include by lib works.
# Check X11 before X11Rn because it is often a symlink to the current release.
for ac_dir in `echo "$xm_includes" | sed s/include/lib/` \
    /usr/X11/lib          \
    /usr/X11R6/lib        \
    /usr/X11R5/lib        \
    /usr/X11R4/lib        \
                          \
    /usr/lib/X11          \
    /usr/lib/X11R6        \
    /usr/lib/X11R5        \
    /usr/lib/X11R4        \
                          \
    /usr/local/X11/lib    \
    /usr/local/X11R6/lib  \
    /usr/local/X11R5/lib  \
    /usr/local/X11R4/lib  \
                          \
    /usr/local/lib/X11    \
    /usr/local/lib/X11R6  \
    /usr/local/lib/X11R5  \
    /usr/local/lib/X11R4  \
                          \
    /usr/X386/lib         \
    /usr/x386/lib         \
    /usr/XFree86/lib/X11  \
                          \
    /usr/lib              \
    /usr/local/lib        \
    /usr/unsupported/lib  \
    /usr/athena/lib       \
    /usr/local/x11r5/lib  \
    /usr/lpp/Xamples/lib  \
    /lib/usr/lib/X11	  \
                          \
    /usr/openwin/lib      \
    /usr/openwin/share/lib \
    ; \
do
dnl Don't even attempt the hair of trying to link an X program!
  for ac_extension in a so sl; do
    if test -r $ac_dir/lib${xm_direct_test_library}.$ac_extension; then
      xm_libraries=$ac_dir
      break 2
    fi
  done
done])
])

AC_DEFUN(DX_CHECK_SELECT_ARG,
[
select_argtype=
cat > selectHdrs.h << EOF
EOF
AC_CHECK_HEADER(unistd.h, [ echo "#include <unistd.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(sys/types.h, [ echo "#include <sys/types.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(select.h, [ echo "#include <select.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(sys/select.h, [ echo "#include <sys/select.h>" >> selectHdrs.h ])
for try in sellist fd_set int void
do
AC_TRY_LINK(
[
#include <stdio.h>
#include "selectHdrs.h"
],
[
int i = select(1, ($try *)NULL, ($try *)NULL, ($try *)NULL, (struct timeval *)NULL)
],
[
select_argtype=$try 
AC_DEFINE_UNQUOTED(SELECT_ARG_TYPE, $try)
])
if test ! -z "$select_argtype" ; then
    break
fi
done
echo the second third and fourth args to select are pointers to $select_argtype
rm selectHdrs.h
])

AC_DEFUN(DX_CHECK_SOCK_LENGTH_TYPE,
[
socket_argtype=
cat > socketHdrs.h << EOF
EOF
AC_CHECK_HEADER(unistd.h, [ echo "#include <unistd.h>" >> socketHdrs.h ])
AC_CHECK_HEADER(sys/types.h, [ echo "#include <sys/types.h>" >> socketHdrs.h ])
AC_CHECK_HEADER(sys/socket.h, [ echo "#include <sys/socket.h>" >> socketHdrs.h ])
for try in socklen_t size_t int
do
AC_TRY_LINK(
[
#include <stdio.h>
#include "socketHdrs.h"
],
[
$try *foo = NULL;
int i = getsockname(1, (struct sockaddr *)NULL, foo);
],
[
socket_argtype=$try 
AC_DEFINE_UNQUOTED(SOCK_LENGTH_TYPE, $try)
])
if test ! -z "$socket_argtype" ; then
    break
fi
done
echo the third arg to getsockname is pointer to $socket_argtype
rm socketHdrs.h
])

AC_DEFUN(DX_CYGWIN_MOUNTS,
[
    changequote(<<,>>)dnl
    AC_MSG_CHECKING("if intelnt on cygwin, check for mounts")
    mnts="none"
    if test "$ARCH" = "intelnt" ; then
	    tt=`uname -s  | tr A-Z a-z | sed "s/^.*cygwin.*$/yes/"`
	    if test "$tt" = "yes" ; then
		    mnts="`mount | sed '1d' | grep "^[^cC]:" | sed "s?\(.:\)[ ]*\([^ ][^ ]*\).*?-mount:\2=\1?"`"
		    if test ! -z "$mnts" ; then
			    CFLAGS="$CFLAGS $mnts"
			    CPPFLAGS="$CPPFLAGS $mnts"
			    CXXFLAGS="$CXXFLAGS $mnts"
		    else
			    mnts="none"
		    fi
	    fi
    fi
    AC_MSG_RESULT($mnts)
    changequote([,])dnl
])

dnl this is AC_CHECK_TYPE with windows.h for DX intelnt port
AC_DEFUN(DX_CHECK_TYPE,
[AC_REQUIRE([AC_HEADER_STDC])dnl
AC_MSG_CHECKING(for $1)
AC_CACHE_VAL(ac_cv_type_$1,
[AC_EGREP_CPP(dnl
changequote(<<,>>)dnl
<<$1[^a-zA-Z_0-9]>>dnl
changequote([,]), [#include <sys/types.h>
#if STDC_HEADERS
#include <stdlib.h>
#include <stddef.h>
#endif
#if defined(HAVE_WINDOWS_H)
#include <windows.h>
#endif], ac_cv_type_$1=yes, ac_cv_type_$1=no)])dnl
AC_MSG_RESULT($ac_cv_type_$1)
if test $ac_cv_type_$1 = no; then
  AC_DEFINE($1, $2)
fi
])


dnl DX_FIND_JDK
AC_DEFUN(DX_FIND_JDK,
[
dx_sedtest=`echo sed should strip everything in this line | sed -e "s&sed should .*&&"`
AC_MSG_CHECKING([sed syntax OK if the rest of this is blank])
AC_MSG_RESULT([$dx_sedtest])

cat > jdkpath.java <<EOF

//   used to find jdk path via -verbose option to javac
public class jdkpath extends Object {
 public static void main() {
   }
}


EOF
dnl 
dnl javac must be in the path for this to work
dnl 
JBASE=
AC_MSG_CHECKING([for JDK install path via javac -verbose ])
(unset CLASSPATH ; javac -verbose jdkpath.java >jdkpath.out 2>jdkpath.err )
dnl
dnl examine "loaded" line for default classes
dnl output is similar to
dnl [loaded /usr/jdk_base/lib/classes.zip(java/lang/Object.class) in 738 ms]
dnl
dnl trim off leading stuff and stuff trailing after lparen to get classes (classes.zip, rt.jar, whatever)
dnl
JDK_CLASSES=`grep loaded jdkpath.err | sed -e "s/.loaded //" | sed -e "s&(.*$&&"`
dnl echo JDK_CLASSES $JDK_CLASSES
dnl
dnl get anything that isn't between "/"'s
dnl 
dx_jdk_trailing=`echo $JDK_CLASSES | sed -e "s&/.*/&&"`
dnl echo dx_jdk_trailing $dx_jdk_trailing
dnl
dnl now trim off /lib/whatever to get to the base of the jdk installation
dnl 
JBASE=`echo $JDK_CLASSES | sed -e "s&/lib/$dx_jdk_trailing&&"`
AC_MSG_RESULT(${JBASE})
JDKBIN=
AC_MSG_CHECKING([for jar not in path])
dnl
dnl which output should not have a space if jar is found (syntax varies from "no jar in")
dnl
if test -z "`which jar | grep -v ' '`" ; then
	JDKBIN=$JBASE/bin/
	AC_MSG_RESULT(using ${JDKBIN})
else
	AC_MSG_RESULT(jar found using path)

fi
rm -f jdkpath.*
dnl
dnl determine the existence of netscape/cosmo for building WRLApplication and dependent samples
dnl   don't know how to do this yet, so just use default.  non-default installations must edit the line below:
WRL_CLASSPATH=$JDK_CLASSES:/usr/lib/netscape/java/classes/npcosmop211.jar:./:/usr/lib/netscape/java/classes/java40.jar


])
dnl
