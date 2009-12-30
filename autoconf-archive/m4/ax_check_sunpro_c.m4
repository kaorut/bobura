# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_check_sunpro_c.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_CHECK_SUNPRO_C([ACTION-IF-YES],[ACTION-IF-NOT])
#
# DESCRIPTION
#
#   Check whether we are using SUN workshop C compiler. The corresponding
#   cache values is ax_cv_check_sunpro_c, which is set to "yes" or "no"
#   respectively.
#
# LICENSE
#
#   Copyright (c) 2008 Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AU_ALIAS([RSSH_CHECK_SUNPRO_C], [AX_CHECK_SUNPRO_C])
AC_DEFUN([AX_CHECK_SUNPRO_C],
[AC_CACHE_CHECK([whether using Sun Worckshop C compiler],
                [ax_cv_check_sunpro_c],

[AC_LANG_SAVE
 AC_LANG_C
 AC_TRY_COMPILE([],
[#ifndef __SUNPRO_C
# include "error: this is not Sun Workshop."
#endif
],
               ax_cv_check_sunpro_c=yes,
                ax_cv_check_sunpro_c=no)
AC_LANG_RESTORE])
if test ${ax_cv_check_sunpro_c} = yes
then
  $2
else
  $3
fi
])dnl
