dnl
dnl  Check for the CYGWIN environment
dnl  -------------------------------------------------------------
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

dnl
dnl  If using CYGWIN, then the extensions to the filenames need to be
dnl  different than that of UN*X. This sets that up.
dnl
AC_DEFUN(DX_EXEEXT,
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


dnl
dnl  Learn what an object files extension is. Somebody with more info explain why?
dnl  -------------------------------------------------------------
AC_DEFUN(DX_OBJEXT,
[AC_MSG_CHECKING([for object file suffix])
AC_CACHE_VAL(ac_cv_objext,
[
  rm -f conftest*
  echo 'int main () { return 0; }' > conftest.$ac_ext
  ac_cv_objext=
  if AC_TRY_EVAL(ac_compile); then
    for file in conftest.*; do
      case $file in
      *.c ) ;;
      *) ac_cv_objext=`echo $file | sed -e s/conftest.//` ;;
      esac
    done
  else
    AC_MSG_ERROR([installation or configuration problem: compiler cannot create executables.])
  fi
  rm -f conftest*
  test x"${ac_cv_objext}" = x && ac_cv_objext=no
])
OBJEXT=""
test x"${ac_cv_objext}" != xno && OBJEXT=${ac_cv_objext}
AC_MSG_RESULT(${ac_cv_objext})
ac_objext=$OBJEXT
AC_SUBST(OBJEXT)])


dnl
dnl  Check the headers for the DX build. This is similar to AC_CHECK_HEADER, but
dnl  avoids putting every header in the dxconfig.h file.
dnl  -------------------------------------------------------------
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


dnl
dnl  Check the headers for the DX build. This is similar to AC_CHECK_HEADERS, but
dnl  avoids putting every header in the dxconfig.h file.
dnl  -------------------------------------------------------------
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


dnl
dnl  Try out if the C++ compiler works
dnl  DX_TRY_CPP(INCLUDES, [ACTION-IF-TRUE [, ACTION-IF-FALSE]])
dnl  -------------------------------------------------------------
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


dnl
dnl  Require finding the C or C++ preprocessor, whichever is the
dnl  current language.
dnl  -------------------------------------------------------------
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


dnl
dnl  Check whether using GNU C
dnl  -------------------------------------------------------------
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


dnl
dnl  Check whether using GNU C++
dnl  -------------------------------------------------------------
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


dnl
dnl  Find which C++ to use
dnl  -------------------------------------------------------------
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


dnl
dnl  Determine the architecture that this is being run on.
dnl  -------------------------------------------------------------
AC_DEFUN(DX_ARCHITECTURE,
[
    AC_MSG_CHECKING(architecture type)
    if test "$ARCH" = "" ; then
	unameS=`uname -s`
	unameM=`uname -m`
	ARCH=unknown
	if test $unameS = "FreeBSD" ; then
	    ARCH=freebsd
	fi
	if test `echo $unameS | tr A-Z a-z | sed "s/^.*cygwin.*$/yes/"` = "yes" ; then
	    ARCH=cygwin
	fi
	if test $unameS = "Linux" ; then
	    ARCH=linux 
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
	if test $unameS = "HP-UX" ; then
	    ARCH=hp700
	fi
	if test $unameS = "SunOS" ; then
	    ARCH=solaris
	fi
    fi
    AC_MSG_RESULT($ARCH)
    AC_SUBST(ARCH)
    AC_DEFINE_UNQUOTED($ARCH)
    AC_DEFINE_UNQUOTED(DXD_ARCHNAME, "$ARCH")
])


dnl
dnl  Set up some architecture specific, primarily to handle AIX's
dnl  export flags. (This needs to be fixed if using gcc)
dnl  -------------------------------------------------------------
AC_DEFUN(DX_ARCH_SPECIFIC,
[
    AC_MSG_CHECKING(architecture specific stuff)
    case $ARCH in
	ibm6000)
	    DXEXEC_EXP='-bE:$(EXP)'
	    DXEXEC_IMP='-bI:$(EXP)'
	    AC_DEFINE_UNQUOTED(DXEXEC_EXP, $DXEXEC_EXP)
	    AC_DEFINE_UNQUOTED(DXEXEC_IMP, $DXEXEC_IMP)
	    ;;
    esac
    AC_MSG_RESULT(done)
])


dnl
dnl  It is possible that the optimizer can cause problems with fstream.
dnl  Check for this problem.
dnl  -------------------------------------------------------------
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


dnl
dnl  Check whether header file contains a symbol.
dnl  DX_HEADER_HAS_SYMBOL[ header-file, symbol ]
dnl  -------------------------------------------------------------
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


dnl
dnl Borrowed from acspecific  and modified to add paths to Xm headers
dnl and libs if different from X11
dnl Set xm_includes and/or xm_libraries.
dnl  -------------------------------------------------------------
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
AC_TRY_LINK( , [${xm_direct_test_function}()],
[LIBS="$ac_save_LIBS"
# We can link Motif programs with no special library path.
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


dnl
dnl  Figure out what the type is needed for the select function.
dnl  -------------------------------------------------------------
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


dnl
dnl  Figure out what the type is needed for getsockname.
dnl  -------------------------------------------------------------
AC_DEFUN(DX_CHECK_SOCK_LENGTH_TYPE,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
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
AC_LANG_RESTORE
])


dnl
dnl  More information for setting up CYGWIN
dnl  -------------------------------------------------------------
AC_DEFUN(DX_CYGWIN_MOUNTS,
[
    changequote(<<,>>)dnl
    AC_MSG_CHECKING(intelnt under cygwin)
    mnts="none"
    if test "$ARCH" = "intelnt" ; then
	    tt=`uname -s  | tr A-Z a-z | sed "s/^.*cygwin.*$/yes/"`
	    if test "$tt" = "yes" ; then
	    	    AC_MSG_RESULT(yes)
		    AC_MSG_CHECKING(mounted disks)
		    mnts="`mount | sed '1d' | grep "^[^cC]:" | sed "s?\(.:\)[ ]*\([^ ][^ ]*\).*?-mount:\2=\1?"`"
		    if test ! -z "$mnts" ; then
			    CFLAGS="$CFLAGS $mnts"
			    CPPFLAGS="$CPPFLAGS $mnts"
			    CXXFLAGS="$CXXFLAGS $mnts"
		    else
			    mnts="none"
		    fi
		    AC_MSG_RESULT($mnts)
	    fi
	    AC_MSG_RESULT(no)
    else
	    AC_MSG_RESULT(no)
    fi
    changequote([,])dnl
])


dnl
dnl this is AC_CHECK_TYPE with windows.h for DX intelnt port
dnl  -------------------------------------------------------------
AC_DEFUN(DX_CHECK_TYPE,
[ AC_REQUIRE([AC_HEADER_STDC])dnl
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


dnl
dnl  Determine whether the stdc++ libraries are needed to compile successfully.
dnl  -------------------------------------------------------------
AC_DEFUN(DX_NEEDS_STDCXX,
[
    AC_MSG_CHECKING(whether -lstdc++ is needed)
    tmpLIBS=$LIBS
    AC_CACHE_VAL(ac_cv_requires_lstdcxx,
    [
	AC_LANG_SAVE
	AC_LANG_CPLUSPLUS
	AC_TRY_LINK(
	    [
		#include <stream.h>
	    ],
	    [
		cout << "foo";
	    ],
	    ac_cv_requires_lstdcxx="no",
	    [
		LIBS="$LIBS -lstdc++"
		AC_TRY_LINK(
		    [
			#include <stream.h>
		    ],
		    [
			cout << "foo";
		    ],
		    ac_cv_requires_lstdcxx="yes",
		    [
			AC_MSG_RESULT(failed even with lstdc++)
			exit 1
		    ]
		)
	    ]
	)
	AC_LANG_RESTORE
    ])
    AC_MSG_RESULT(${ac_cv_requires_lstdcxx})
])


dnl Java Stuff ----------------------------------------------------------
dnl Adding the functionality to locate the appropriate Java Architecture
dnl information to compile JavaDX. These functions have been proposed on the
dnl autoconf mailing list.
dnl
dnl For compiling the javadx stuff, we need to have available, the compiler,
dnl the jar packager, the javah generator, the appropriate classes, 
dnl and the jni headers.
dnl
dnl After much discussion as to how this info needs to be found, I propose
dnl the following:
dnl   JavaC, Jar, and JavaH are being found appropriately--if an appropriate
dnl     program exists for one of these types that I'm not checking, please
dnl     let me know and it can be added.
dnl   The big debate is what to do for the jni and jars. For the jni, the list
dnl     has propsed (from my conclusion) the following (LOSE the prompting):
dnl			a configure path flag, 
dnl			search for an environment variable,
dnl			then use Pete's old code for searching for it,
dnl			then try some standard location (I guesss /usr/include).
dnl   As for the jars, Pete had not finished that: so I suggest
dnl			a configure path flag,
dnl			an environment variable set,
dnl			search for standard location (/usr/lib/netscape/java/classes?)


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
dnl  DX_PROG_JAVAH([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_PROG_JAVAH,[
AC_CHECKING(for javah)
if test -n "$JAVAH"; then
  AC_MSG_WARN(JAVAH was preset)
  AC_CHECK_PROG(JAVAH, $JAVAH)
else
  AC_CHECK_PROGS(JAVAH, javah gcjh)
fi
if test -z "$JAVAH"; then
  AC_MSG_WARN([no acceptable jni header generator found in \$PATH])
  ifelse([$2], , , [$2])
else
  ifelse([$1], , , [$1])
fi
])

dnl
dnl DX_FIND_JNI_WITH_PATH(JNI-PATH,[ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_JNI_WITH_PATH, 
[
AC_MSG_CHECKING([for valid jni headers path])
AC_CACHE_VAL([ac_cv_include_jni],
[
dnl Now we need to perform the search starting at the specified path root.

dnl Need to construct JINC from the given colon separated path, ie $1="/path:/path2" now
dnl needs JINC = "-I/path -I/path ...". Test the directories to see if they exist; if not,
dnl then don't include them. Then look for jni.h and jni_md.h within these directories.
dnl If they don't exist, then do ACTION-IF-FALSE.

dx_jniinc=''
dx_jnimdinc=''

list=`echo $1 | sed -e "s/:/ /g"`
for i in $list 
do
	if test -r "$i/jni.h" ; then
	   dx_jniinc=$i
	fi
	if test -r "$i/jni_md.h" ; then
	   dx_jnimdinc=$i
	fi
done

dnl Now determine how successful the search was and return to configure

if test -n "$dx_jniinc" && test -n "$dx_jnimdinc" ; then
  JINC="-I$dx_jniinc -I$dx_jnimdinc"
  ac_cv_include_jni="$JINC"
fi
])
if test -z "$ac_cv_include_jni" ; then
  AC_MSG_RESULT(no)
  ifelse([$3], , , [$3])
else
  AC_MSG_RESULT(yes)
  ifelse([$2], , , [$2])
  if test -z "$JINC"; then
    JINC="$ac_cv_include_jni"
  fi
fi
])


dnl
dnl  DX_JAVA_ARCHITECTURE is similar to DX_ARCHITECTURE, but the result
dnl  is used for part of the search path when looking for jni_md.h
dnl  This is a problem, since the pathname for linux may not always
dnl  be genunix. Could there be a better solution here?
dnl  -------------------------------------------------------------
AC_DEFUN(DX_JAVA_ARCHITECTURE,
[
    AC_MSG_CHECKING(java architecture type)
    if test "$JAVA_ARCH" = "" ; then
	lc=`uname -s | tr "A-Z" "a-z"`
        case $lc in
	    irix*)     JAVA_ARCH=irix ;;
	    cygwin*)   JAVA_ARCH=win32 ;;
	    aix)       JAVA_ARCH=aix ;;
	    alpha)     JAVA_ARCH=alpha ;;
	    osf1)      JAVA_ARCH=alpha ;;
	    hp-ux)     JAVA_ARCH=hp-ux ;;
	    sunos)     JAVA_ARCH=solaris ;;
	    linux)     JAVA_ARCH=genunix ;;
	    *)         JAVA_ARCH=$lc ;;
	esac
    fi
    AC_MSG_RESULT($JAVA_ARCH)
])


dnl
dnl DX_FIND_JNI([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_JNI, [

AC_MSG_CHECKING([for jniheaders path])
AC_CACHE_VAL([ac_cv_jdk_base],
[
dnl Now start the search using the java -verbose search algorithm.
dnl Continue on with the search of standard directories [/usr/include].

dnl We cannot perform the check if not using Sun's javac, thus we must fallback
dnl to checking with default paths. More can be added if there are any.

if test "$JAVAC" != "javac" ; then
AC_MSG_RESULT([trying default path])
DX_FIND_JNI_WITH_PATH("/usr/include:/usr/include/$JAVA_ARCH", $1, $2)
fi

dnl Create a basic program and run javac -verbose on it. Only works if
dnl we are using javac, thus test which java.
dnl This should work for both 1.1.x and 1.2.
AC_MSG_RESULT([trying javac -verbose])

AC_MSG_CHECKING([jni install path with javac -verbose ])

cat > jdkpath.java <<EOF
//   used to find jdk path via -verbose option to javac
public class jdkpath extends Object {
 public static void main() {
   }
}
EOF

javac -verbose jdkpath.java >jdkpath.out 2>jdkpath.err

dnl Examine "loaded" line for default classes. Output is similar to
dnl [loaded /usr/jdk_base/lib/classes.zip(java/lang/Object.class) in 738 ms]
dnl Trim off leading stuff and stuff trailing after the left paren to get classes 
dnl (classes.zip, rt.jar, whatever)
DX_JDK_CLASSES=`grep loaded jdkpath.err | tr '\134' '\057' | sed -e "s/.loaded //" -e "s&(.*$&&"`

dnl Get anything that isn't between "/"'s
DX_JDK_TRAILING=`echo $DX_JDK_CLASSES | sed -e "s&.*/&&"`

dnl Now trim off /lib/whatever to get to the base of the jdk installation
dnl The result should look something like /usr/jdk_base for 1.1.x and
dnl /usr/jdk_base/jre for 1.2.
DX_ALMOST_BASE=`echo $DX_JDK_CLASSES | sed -e "s&/lib/$DX_JDK_TRAILING&&"`
DX_JBASE=`echo $DX_ALMOST_BASE | sed -e "s&/jre&&"`

dnl Cleanup the files that were created.
rm -f jdkpath.*

dnl Now we need to find the subdirectory within the include directory that
dnl has jni_md.h for the appropriate architecture.

AC_MSG_RESULT(ok)

DX_JAVA_ARCHITECTURE

dnl The path that should be used now is DX_JBASE/include and DX_JBASE/include/JAVA_ARCH.
DX_FOUND_PATH="$DX_JBASE/include:$DX_JBASE/include/$JAVA_ARCH"

ac_cv_jdk_base="$DX_FOUND_PATH"
dx_ran_cts="yes"
])
if test -z $dx_ran_cts ; then
  AC_MSG_RESULT(ok)
fi
DX_FIND_JNI_WITH_PATH( $ac_cv_jdk_base, $1, $2)

])


dnl
dnl DX_FIND_COSMO(PATH [, ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_COSMO, [
AC_MSG_CHECKING([for cosmo jar files])
AC_CACHE_VAL([ac_cv_class_cosmo],
[ 
if test -r $1; then
  ac_cv_class_cosmo=$1
fi
])
if test -n "$ac_cv_class_cosmo" ; then
  AC_MSG_RESULT(yes)
  ifelse([$2], , , [$2])
else
  AC_MSG_RESULT(no -- comso support will not be complete)
  ifelse([$3], , , [$3])
fi
])


dnl
dnl DX_FIND_DEFAULT_COSMO
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_DEFAULT_COSMO, [

dnl Set the default to be Netscape's default class directory.
dnl   You got a better idea--let us hear about it 
dnl   (opendx-dev@opendx.watson.ibm.com).

DX_FIND_COSMO(/usr/lib/netscape/java/classes/npcosmop211.jar)

])


dnl
dnl DX_FIND_NETSCAPE(PATH [, ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_NETSCAPE, 
AC_MSG_CHECKING([for netscape jar files])
[AC_CACHE_VAL([ac_cv_class_netscape],
[
if test -r $1; then
  ac_cv_class_netscape=$1
fi
])
if test -n "$ac_cv_class_netscape" ; then
  AC_MSG_RESULT(yes)
  ifelse([$2], , , [$2])
else
  AC_MSG_RESULT(no -- netscape support will not be complete)
  ifelse([$3], , , [$3])
fi
])


dnl
dnl DX_FIND_DEFAULT_NETSCAPE
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_DEFAULT_NETSCAPE, [

dnl Set the default to be Netscape's default class directory.
dnl   You got a better idea--let us hear about it 
dnl   (opendx-dev@opendx.watson.ibm.com).

DX_FIND_NETSCAPE(/usr/lib/netscape/java/classes/java40.jar)

])


dnl End of the JavaDX stuff -------------------------------------------------

