
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
dnl  For intel link, list X libs
dnl  ------------------------------------------------------------
AC_DEFUN(DX_XLIBS,
[
AC_SUBST(DX_XLIBS_LIST)
if test "$ARCH" = "intelnt" ; then
      DX_XLIBS_LIST="hclglx.lib xm.lib xt.lib xlibcon.lib xlib.lib"
else
      DX_XLIBS_LIST=""
fi
])

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
      *.c | *.o | *.obj | *.ilk | *.pdb) ;;
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
AC_PROVIDE(AC_PROG_CXXCPP)
if test -z "$CXXCPP"; then
AC_CACHE_VAL(ac_cv_prog_CXXCPP,
[
AC_LANG_SAVE[]dnl
AC_LANG_CPLUSPLUS[]dnl
  CXXCPP="${CXX-g++} -E"
  DX_TRY_CPP([#include <stdlib.h>], , CXXCPP=/lib/cpp)
  ac_cv_prog_CXXCPP="$CXXCPP"
AC_LANG_RESTORE[]dnl
CXXCPP="$ac_cv_prog_CXXCPP"
fi]
)dnl
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
dnl  Check whether using glibc tgmath, if so add -D_GNU_SOURCE to CFLAGS
dnl  -------------------------------------------------------------
AC_DEFUN(DX_CHECK_TGMATH,
[AC_CACHE_CHECK(whether we are using GNU glibc math, ac_cv_lib_glibcmath,
[dnl The semicolon is to pacify NeXT's syntax-checking cpp.
cat > conftest.c <<EOF
/* Because certain platforms using glibc and gcc will not use certain
   math functions correctly unless they are using the ISO C 9X standard
   we check. If we get a yes, then the define _GNU_SOURCE makes the
   compiler add the ISO C 9X support. */
#if defined __GNUC__ && (__GNUC__ > 2 || __GNUC__ == 2 && __GNUC_MINOR__ >= 7)
  yes;
#endif
EOF
if AC_TRY_COMMAND(${CC-cc} -E conftest.c) | egrep yes > foo 2>&1; then
  ac_cv_lib_glibcmath=-D_GNU_SOURCE
fi
rm foo
])
if test -n "$ac_cv_lib_glibcmath" ; then 
  CFLAGS="$CFLAGS $ac_cv_lib_glibcmath"
fi
])


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
    AC_CACHE_VAL(ac_cv_dx_arch, 
    [
	ac_cv_dx_arch=$ARCH
	if test "$ARCH" = "" ; then
	    unameS=`uname -s`
	    unameM=`uname -m`
	    ac_cv_dx_arch=unknown
	    if test $unameS = "FreeBSD" ; then
		ac_cv_dx_arch=freebsd
	    fi
	    if test `echo $unameS | tr A-Z a-z | sed "s/^.*cygwin.*$/yes/"` = "yes" ; then
		ac_cv_dx_arch=cygwin
	    fi
	    if test $unameS = "Linux" ; then
		ac_cv_dx_arch=linux 
	    fi
	    if test $unameS = "IRIX" || test $unameS = "IRIX64" ; then
		ac_cv_dx_arch=sgi
	    fi
	    if test $unameS = "AIX" ; then
		ac_cv_dx_arch=ibm6000
	    fi
	    if test $unameM = "alpha" ; then
		ac_cv_dx_arch=alphax
	    fi
	    if test $unameS = "HP-UX" ; then
		ac_cv_dx_arch=hp700
	    fi
	    if test $unameS = "SunOS" ; then
		ac_cv_dx_arch=solaris
	    fi
	fi
    ])
    ARCH=$ac_cv_dx_arch
    AC_MSG_RESULT($ARCH)
    AC_SUBST(ARCH)
    AC_DEFINE_UNQUOTED($ARCH)
    AC_DEFINE_UNQUOTED(DXD_ARCHNAME, "$ARCH")
])


dnl
dnl  Set up some architecture specific, primarily to handle AIX's
dnl  export flags. (This needs to be fixed if using gcc)
dnl  (I added the gcc case)
dnl  -------------------------------------------------------------
AC_DEFUN(DX_ARCH_SPECIFIC,
[
    AC_MSG_CHECKING(architecture specific stuff)
    case $ARCH in
	ibm6000)
	    if test "$CC" != "gcc" ; then
		DXEXEC_EXP='-bE:$(EXP)'
		DXEXEC_IMP='-bI:$(EXP)'
		AC_DEFINE_UNQUOTED(DXEXEC_EXP, $DXEXEC_EXP)
		AC_DEFINE_UNQUOTED(DXEXEC_IMP, $DXEXEC_IMP)
	    fi
	    ;;
	linux)
	    DXEXEC_EXP='-Wl,-export-dynamic'
	    AC_DEFINE_UNQUOTED(DXEXEC_EXP, $DXEXEC_EXP)
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
    found="no"
    for i in $1
    do
	AC_EGREP_CPP(yes, 
	    [#include <$i>
	    #ifdef $2
	    yes
	    #endif
	    ], found="yes")
    done
    if test $found = "no" ; then
	for i in $1 
	do
	    AC_EGREP_HEADER($2, $1, found="yes")
	done
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
dnl  What is the correct function name and structure def stat... stat, or _stat?
dnl  -------------------------------------------------------------
AC_DEFUN(DX_CHECK_STAT,
[
AC_CHECK_FUNCS( stat _stat )
if test $ac_cv_func__stat = 'yes' ; then
    AC_DEFINE_UNQUOTED(STATFUNC, _stat)
    dx_stat=_stat
else
    if test $ac_cv_func_stat = 'yes' ; then
	AC_DEFINE_UNQUOTED(STATFUNC, stat)
	dx_stat=stat
    else
 	echo could not find either stat or _stat.... need one or the other
	exit
    fi
fi
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
dx_statstruct=
cat > statHdrs.h << EOF
EOF
AC_CHECK_HEADER(windows.h, [ echo "#include <windows.h>" >> statHdrs.h ])
AC_CHECK_HEADER(unistd.h, [ echo "#include <unistd.h>" >> statHdrs.h ])
AC_CHECK_HEADER(sys/types.h, [ echo "#include <sys/types.h>" >> statHdrs.h ])
AC_CHECK_HEADER(sys/stat.h, [ echo "#include <sys/stat.h>" >> statHdrs.h ])
for try in stat _stat
do
AC_TRY_LINK(
[
#include <stdio.h>
#include "statHdrs.h"
],
[
int i = $dx_stat("foo", (struct $try *) NULL);
],
[
dx_statstruct=$try 
AC_DEFINE_UNQUOTED(STATSTRUCT, $try)
])
if test ! -z "$dx_statstruct" ; then
    break
fi
done
echo stat function is: $dx_stat
echo stat structure is: $dx_statstruct
rm statHdrs.h
AC_LANG_RESTORE
])

dnl
dnl  Figure out what the type is needed for the select function.
dnl  -------------------------------------------------------------
AC_DEFUN(DX_CHECK_SELECT_ARG,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
select_argtype=
cat > selectHdrs.h << EOF
EOF
AC_CHECK_HEADER(windows.h, [ echo "#include <windows.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(unistd.h, [ echo "#include <unistd.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(sys/types.h, [ echo "#include <sys/types.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(select.h, [ echo "#include <select.h>" >> selectHdrs.h ])
AC_CHECK_HEADER(sys/select.h, [ echo "#include <sys/select.h>" >> selectHdrs.h ])
AC_LANG_RESTORE
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
AC_LANG_C
socket_argtype=
cat > socketHdrs.h << EOF
EOF
AC_CHECK_HEADER(unistd.h, [ echo "#include <unistd.h>" >> socketHdrs.h ])
AC_CHECK_HEADER(sys/types.h, [ echo "#include <sys/types.h>" >> socketHdrs.h ])
AC_CHECK_HEADER(sys/socket.h, [ echo "#include <sys/socket.h>" >> socketHdrs.h ])
if test "$ARCH" = "intelnt" ; then
	AC_CHECK_HEADER(winsock2.h, [ echo "#include <winsock2.h>" >> socketHdrs.h ])
fi
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
for try in socklen_t size_t int "unsigned int"
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
    AC_MSG_CHECKING(if intelnt on cygwin, check for mounts)
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
[
    AC_REQUIRE([AC_HEADER_STDC])dnl
    AC_MSG_CHECKING(for $1)
    AC_CACHE_VAL(ac_cv_type_$1,
    [
	 if test "$ac_cv_header_windows_h" = "yes" ; then
	    AC_EGREP_CPP(dnl
changequote(<<,>>)dnl
<<$1[^a-zA-Z_0-9]>>dnl
changequote([,]),
	    [
		#include <sys/types.h>
		#if STDC_HEADERS
		#include <stdlib.h>
		#include <stddef.h>
		#endif
		#include <windows.h>
	    ],
	    ac_cv_type_$1=yes, ac_cv_type_$1=no)
	else
	    AC_EGREP_CPP(dnl
changequote(<<,>>)dnl
<<$1[^a-zA-Z_0-9]>>dnl
changequote([,]),
	    [
		#include <sys/types.h>
		#if STDC_HEADERS
		#include <stdlib.h>
		#include <stddef.h>
		#endif
	    ],
	    ac_cv_type_$1=yes, ac_cv_type_$1=no)

	fi
        if test $ac_cv_type_$1 = no; then
            AC_TRY_COMPILE([], $1 foo;, ac_cv_type_$1=yes, ac_cv_type_$1=no)
        fi
    ])
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
		#include <iostream.h>
	    ],
	    [
		cout << "foo";
	    ],
	    ac_cv_requires_lstdcxx="no",
	    [
		LIBS="$LIBS -lstdc++"
		AC_TRY_LINK(
		    [
			#include <iostream.h>
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
dnl  DX_PATH_JAVA([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_PATH_JAVA,[
if test -n "$JAVA"; then
  AC_MSG_WARN(JAVA was preset)
  AC_PATH_PROG(JAVA, $JAVAH)
else
  AC_PATH_PROGS(JAVA, java)
fi
if test -z "$JAVA"; then
  AC_MSG_WARN([no java executable found in \$PATH])
  ifelse([$2], , , [$2])
else
  DX_JBASE_TRAILING=`echo $JAVA | sed -e "s&.*/&&"`
  JBASE=`echo $JAVA | sed -e "s&/$DX_JBASE_TRAILING&&"`
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
dnl  This is a problem, since the pathname for linux may not always be
dnl  genunix. Workaround is to set JAVA_ARCH (to e.g. linux) before configure.
dnl  Could there be a better solution here?
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
	    linux)     JAVA_ARCH=genunix 
		       JNI_CFLAGS=-DIBM_LINUX;;
	    *)         JAVA_ARCH=$lc ;;
	esac
    fi
    AC_MSG_RESULT($JAVA_ARCH)
])


dnl
dnl  DX_FIND_JDK_CLASSES
dnl  Only works for sun java. Skips if not "javac".
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_JDK_CLASSES, [
dx_find_jdk=""
AC_MSG_CHECKING([for jdk classes])
AC_CACHE_VAL([ac_cv_jdk_classes],
[
ac_cv_jdk_classes=""
dnl We cannot perform the check if not using Sun's javac, so check if javac.

if test "$JAVAC" = "javac" ; then

AC_MSG_RESULT([trying javac -verbose])

dnl Create a basic program and run javac -verbose on it. Only works if
dnl we are using javac, thus test which java.
dnl This should work for both 1.1.x and 1.2.

AC_MSG_CHECKING([for jdk classes verbosely])

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
dnl (classes.zip, rt.jar, whatever) DX_JDK_CLASSES now contains the class
dnl libraries typically used to run and compile with the JRE or JDK. Because
dnl of a bug in some Javas, we need to include this with CLASSPATH environment
dnl variable. (As Of Now--this is IBM's J1.1.8 for rh linux). This appears to be
dnl a problem as it shouldn't need to be included. This will hardcode the
dnl path into runtime areas and could cause problems with upgrades of java.
dnl But as for now this is the way we are going to do it.

ac_cv_jdk_classes=`grep loaded jdkpath.err | tr '\134' '\057' | sed -e "s/.loaded //" -e "s&(.*$&&"`

dnl Cleanup the files that were created.
rm -f jdkpath.*

AC_MSG_RESULT($ac_cv_jdk_classes)
else

AC_MSG_RESULT([none])

fi
dx_find_jdk="yes"
])
if test -z "$dx_find_jdk" ; then
  AC_MSG_RESULT($ac_cv_jdk_classes)
fi
])


dnl
dnl DX_FIND_JNI([ACTION-IF-TRUE [, ACTION-IF-FALSE ]])
dnl  -------------------------------------------------------------
AC_DEFUN(DX_FIND_JNI, [

AC_CACHE_VAL([ac_cv_jdk_base],
[
dnl Now start the search using the java -verbose search algorithm.
dnl Continue on with the search of standard directories [/usr/include].

dnl Find out what system we are on to define $JAVA_ARCH
DX_JAVA_ARCHITECTURE

DX_FIND_JDK_CLASSES

if test -z "$ac_cv_jdk_classes" ; then

dnl Fallback to checking the default paths since it is empty.
  AC_MSG_RESULT([trying default path])
  ac_cv_jdk_base="/usr/include:/usr/include/$JAVA_ARCH"

else

dnl Get anything that isn't between "/"'s
DX_JDK_TRAILING=`echo $ac_cv_jdk_classes | sed -e "s&.*/&&"`

dnl Now trim off /lib/whatever to get to the base of the jdk installation
dnl The result should look something like /usr/jdk_base for 1.1.x and
dnl /usr/jdk_base/jre for 1.2.
DX_ALMOST_BASE=`echo $ac_cv_jdk_classes | sed -e "s&/lib/$DX_JDK_TRAILING&&"`
DX_JBASE=`echo $DX_ALMOST_BASE | sed -e "s&/jre&&"`

dnl Now we need to find the subdirectory within the include directory that
dnl has jni_md.h for the appropriate architecture.

dnl The path that should be used now is DX_JBASE/include and DX_JBASE/include/JAVA_ARCH.
DX_FOUND_PATH="$DX_JBASE/include:$DX_JBASE/include/$JAVA_ARCH"

ac_cv_jdk_base="$DX_FOUND_PATH"

fi

dnl  Set a flag to say that we have already answered the MSG.
])
AC_MSG_CHECKING([for jni headers path])
AC_MSG_RESULT($ac_cv_jdk_base)

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

dnl  
dnl  With the architecture determine flags needed to compile runtime loadable modules etc.
dnl  -------------------------------------------------------------
AC_DEFUN(DX_SET_RTL_FLAGS,
[
dnl autoconfigure variables for building runtime loadables / shared objects that are
dnl used in dx build. They also go into lib_$(ARCH)/arch.mak for building samples and user modules.
dnl These should make it trivial for dx builder or you to construct functional, platform-independent 
dnl makefiles for your modules.
dnl SHARED_LINK
dnl	allows override of default ($(CC)) with e.g. ld ; some cc's seem incapable of passing 
dnl	make-shared-object flags to ld.
dnl DX_RTL_CFLAGS 
dnl	ideally, this, $(DXABI) and -I's should be all $(CC) requires to make the .o .
dnl DX_RTL_LDFLAGS 
dnl	ld flags (prefixed with cc-pass-these-to-ld if SHARED_LINK is a cc) for building any shared object
dnl DX_RTL_DXENTRY
dnl	flags, typically -e DXEntry , the runtime loadable dx module entry point
dnl	not generic to all shared objects
dnl DX_RTL_IMPORTS
dnl	frequently unnecessary, this flag is for declaring dxexec symbols to the runtime loadable module.
dnl	not generic to all shared objects

dnl don't require SHARED_LINK to be set going in, but if set, it overrides any selection here.
	ccld_defaulted=0
	if test "$SHARED_LINK" = "" ; then
		SHARED_LINK="$""(CC)"
		ccld_defaulted=1
	fi
	DX_RTL_SYSLIBS=""
        if test $ac_cv_prog_gcc = "yes" ; then
                MDXLDFLAG="-Wl,"
        else
                MDXLDFLAG=""
        fi
        if test $ARCH = "cygwin" ; then
                DX_RTL_CFLAGS="-DDXD_WIN -DWIN32 -D_X86_ -DNOMENUS -nologo -w -0d -LD -G5"
                DX_RTL_LDFLAGS="-DLL -SUBSYSTEM:console -INCREMENTAL:no -MACHINE:I386 -NOLOGO"
                DX_RTL_SYSLIBS="$SYSLIBS kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib wsock32.lib"
                DX_OUTBOARD_LIBS="$OLIBS $DXINST/lib/DXExport.lib"
        fi
        if test $ARCH = "hp700" ; then
                DX_RTL_CFLAGS="-Dhp700 -Aa +z"
                DX_RTL_LDFLAGS="${MDXLDFLAG}-q ${MDXLDFLAG}-b ${MDXLDFLAG}-E "
		DX_RTL_DXENTRY="${MDXLDFLAG}-eDXEntry"
                DX_RTL_SYSLIBS="$SYSLIBS -ldld"
        fi
        if test $ARCH = "ibm6000" ; then
                DX_RTL_CFLAGS="-Dibm6000"
                DX_RTL_DXENTRY="${MDXLDFLAG}-eDXEntry "
		DX_RTL_LDFLAGS=
		DX_RTL_IMPORT="${MDXLDFLAG}-bI:$DXINST/lib/dxexec.exp"
        fi
        if test $ARCH = "sgi" ; then
                DX_RTL_CFLAGS=" -Dsgi"
        	if test $ac_cv_prog_gcc = "yes" ; then
			DX_RTL_CFLAGS=" -Dsgi -D_GNU_SOURCE"
                	DX_RTL_LDFLAGS=" -shared"
			DX_RTL_DXENTRY=" -e DXEntry -exported_symbol DXEntry"
			if ccld_defaulted ; then 
				SHARED_LINK="ld"
			fi
        	else
                	DX_RTL_LDFLAGS=" -shared -ignore_unresolved "
			if ccld_defaulted ; then
				SHARED_LINK=$CC
			fi
        	fi

        fi
        if test $ARCH = "solaris" ; then
                DX_RTL_CFLAGS=" -Dsolaris"
                # DX_RTL_LDFLAGS=" ${MDXLDFLAG}-G ${MDXLDFLAG}-eDXEntry"
                DX_RTL_LDFLAGS=" -G "
		SHARED_LINK="ld"
        fi
        if test $ARCH = "alphax" ; then
                DX_RTL_CFLAGS=" -Dalphax"
                DX_RTL_LDFLAGS=" -shared -all -expect_unresolved main "
                DX_RTL_DXENTRY=" -e DXEntry"
                DX_RTL_IMPORTS=" -expect_unresolved DX\*"
        fi
        if test $ARCH = "linux" ; then
                DX_RTL_CFLAGS=" -D_GNU_SOURCE -Dlinux"
                DX_RTL_LDFLAGS=" --shared"
		DX_RTL_DXENTRY=" -eDXEntry"
        fi
        if test $ARCH = "freebsd" ; then
                DX_RTL_CFLAGS="-D_GNU_SOURCE -Dfreebsd"
                DX_RTL_LDFLAGS="--shared "
		DX_RTL_DXENTRY="-eDXEntry"
        fi
])

