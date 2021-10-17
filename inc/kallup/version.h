// ------------------------------------------------------------------
// file:   version.h
// desc:   example file for creating executeable's for Windows 10 Pro.
//         with the AsmJit by:
//         available under:
//
// autor:  Jens Kallup - <kallup.jens@web.de>
//         kallup.net * non-profit
// date:   2021-10-12
//
// policy: only for education usage !!! - no commercial use allowed.
//         free to distribute if copyright notice is intact.
// ------------------------------------------------------------------
#pragma  once
#ifndef  VERSION_H_
# define VERSION_H_

// Example of __DATE__ string: "Jul 27 2012"
//                              01234567890
# define BUILD_YEAR_CH0 (__DATE__[ 7])
# define BUILD_YEAR_CH1 (__DATE__[ 8])
# define BUILD_YEAR_CH2 (__DATE__[ 9])
# define BUILD_YEAR_CH3 (__DATE__[10])

# define BUILD_DAY_CH0 ((__DATE__[ 4] >= '0') ? (__DATE__[4]) : '0')
# define BUILD_DAY_CH1  (__DATE__[ 5])

# define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
# define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
# define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
# define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
# define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
# define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
# define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
# define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
# define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
# define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
# define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
# define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')

# define BUILD_MONTH_CH1    ( \
        (BUILD_MONTH_IS_JAN) ? "01" : \
        (BUILD_MONTH_IS_FEB) ? "02" : \
        (BUILD_MONTH_IS_MAR) ? "03" : \
        (BUILD_MONTH_IS_APR) ? "04" : \
        (BUILD_MONTH_IS_MAY) ? "05" : \
        (BUILD_MONTH_IS_JUN) ? "06" : \
        (BUILD_MONTH_IS_JUL) ? "07" : \
        (BUILD_MONTH_IS_AUG) ? "08" : \
        (BUILD_MONTH_IS_SEP) ? "09" : \
        (BUILD_MONTH_IS_OCT) ? "10" : \
        (BUILD_MONTH_IS_NOV) ? "11" : \
        (BUILD_MONTH_IS_DEC) ? "12" : "?" )

# define BUILD_VERSION_MAJOR "1"
# define BUILD_VERSION_MINOR "0"
# define BUILD_VERSION_BUILD "2"

# define __BUILD_VERSION__         \
	BUILD_VERSION_MAJOR << "."  << \
	BUILD_VERSION_MINOR << "."  << \
	BUILD_VERSION_BUILD << ": " << \
	BUILD_YEAR_CH0  <<     \
	BUILD_YEAR_CH1  <<     \
	BUILD_YEAR_CH2  <<     \
	BUILD_YEAR_CH3  <<     \
	"/"             <<     \
	BUILD_MONTH_CH1 <<     \
	"/"             <<     \
	BUILD_DAY_CH0   <<     \
	BUILD_DAY_CH1

#endif
