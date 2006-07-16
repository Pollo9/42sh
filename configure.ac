# Require a recent version of autotools
AC_PREREQ(2.59)

# Auto conf init
AC_INIT([42sh],[1.0],[seblu@seblu.net], [42sh])

# Define configure generator directory
AC_CONFIG_AUX_DIR([build])

# Auto Make init
AM_INIT_AUTOMAKE([foreign dist-bzip2 no-dist-gzip])

echo "Checking locale CFLAGS"
# Check platform
AC_CANONICAL_HOST

case $host_os in
  *netbsd*)
	AC_SUBST([CFLAGS], ['-Wall -Werror -W -ansi -pedantic'])
	;;
  *osf*)
	AC_SUBST([CFLAGS], ['-Wall -Werror -W -ansi -pedantic -D_XOPEN_SOURCE=600'])
	;;
  *solaris*)
	AC_SUBST([CFLAGS], ['-Wall -Werror -W -ansi -pedantic -D_XOPEN_SOURCE=600'])
	;;
  *linux*)
	AC_SUBST([CFLAGS], ['-Wall -Werror -W -ansi -pedantic -D_XOPEN_SOURCE=600'])
	;;
  *)
	pl="`uname -s`"
	AC_MSG_ERROR([Platform $pl not supported.])
	;;
esac

# Check for C compiler
AC_LANG([C])
AC_PROG_CC

# Check for Make
AC_PROG_MAKE_SET

# check for ranlib
AC_PROG_RANLIB

# Check for lib efence
AC_CHECK_LIB([efence], [malloc], [EFENCELIB=-lefence])
AC_SUBST([EFENCELIB])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_REALLOC
AC_FUNC_FORK
AC_FUNC_STAT
AC_FUNC_ALLOCA
AC_HEADER_DIRENT
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_FUNCS([strtol])
AC_CHECK_FUNCS([dup])
AC_CHECK_FUNCS([dup2])
AC_CHECK_FUNCS([strchr])
AC_CHECK_FUNCS([strdup])
AC_CHECK_FUNCS([getcwd])
AC_CHECK_FUNCS([setenv])
AC_CHECK_FUNCS([strdup])
AC_CHECK_FUNCS([strstr])
AC_CHECK_FUNCS([get_current_dir_name])
AC_CHECK_FUNCS([atexit])
AC_CHECK_FUNCS([putenv])
AC_CHECK_FUNCS([strtoul])

AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Check for headers
AC_CHECK_HEADERS([sys/param.h unistd.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([stddef.h])

dnl Memo:
dnl AC ARG WITH(package, help-string, [action-if-given], [action-if-not-given])

AC_ARG_WITH([debug],
  [AS_HELP_STRING([--with-debug], [use -g and don't use -DNDEBUG -O3])],
  [dnl action-if-given: --with-debug => -g || --without-debug => -DNDEBUG
    if test x$withval = xyes; then
      CFLAGS="$CFLAGS -g"
    else
      CFLAGS="$CFLAGS -DNDEBUG -O3"
    fi
  ],
  [dnl action-if-not-given: MAINTAINER_MODE => -g || !MAINTAINER_MODE => -DNDEBUG
    # If we are in maintainer mode, we want to have DEBUG (NDEBUG==NO DEBUG)
    # So we simply replace -DNDEBUG by -g
    if test x$MAINTAINER_MODE = xyes; then
      CFLAGS="$CFLAGS -g"
    else
      CFLAGS="$CFLAGS -DNDEBUG -O3"
    fi
  ]
)

AC_ARG_WITH([leaktrack],
  [AS_HELP_STRING([--with-leaktrack], [add a builtin leak track for debug])],
  [
    if test x$withval = xyes; then
      CFLAGS="$CFLAGS -DLEAK_TRACK"
    fi
  ],
)

AC_SUBST([CFLAGS])

# define Autoconf config header
AC_CONFIG_HEADERS([config.h])

# define Autoconf config files
AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	check/Makefile
	check/leaktrack/Makefile
	src/Makefile
	src/parser/Makefile
	src/evalexpr/Makefile
])

AC_CONFIG_FILES([check/checker_wrapper.sh],
                [chmod a=rx check/checker_wrapper.sh])

AC_OUTPUT
