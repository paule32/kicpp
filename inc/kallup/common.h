// --------------------------------------------------------------------------
// Datei : common.h
// Autor : Jens Kallup <kallup.jens@web.de>
// Lic   : non-profit
//         (c) 2021 kallup.net - non-profit
//         Nur für Schulungszwecke !
//
// Notes : Simulations-Programm für das verteilte Rechnen von
//         rechenintensiven, mathematischer Aufgaben.
//
// Depend: keine.
// --------------------------------------------------------------------------
#pragma once
#ifndef  COMMON__H		// sanity guardian
# define COMMON__H

# include <libintl.h>   // locales für multi lang
# include <locale.h>

// STD C
# include <signal.h>	// segfault tap
# include <stdio.h>
# include <assert.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>    // für uintN_t
# include <malloc.h>

# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>

// STD C++
# include <iostream>	// std::cout
# include <string>		// std::string
# include <sstream> 	// std::stringstream
# include <ostream>
# include <istream>
# include <fstream>
# include <algorithm>
# include <iomanip>
# include <ctime>
# include <chrono>		// time day
# include <vector>
# include <utility>
# include <compare>
# include <iterator>
# include <map>
# include <bitset>
# include <variant>
# include <typeinfo>

# include <cxxabi.h>	// for C++ demangling (GNU)

// TVision
#ifdef TVISION
# include <strstream>
# include <iomanip>
#endif

// my own proto types:
# include "kallup/demangled.h"
# include "kallup/locales.h"

// --------------------------------------------------------------------------
// Windows 64-Bit Compiler (MinGW64)
// --------------------------------------------------------------------------
#if defined(__MINGW32__) || defined(__MINGW64__)
# include <winsock2.h>		/* tcp/ip für Windows */
# include <ws2tcpip.h>
# include <windows.h>

# undef  gettimeofday
# define gettimeofday mingw_gettimeofday

# define timersub(a, b, result)                       \
  do {                                                \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;     \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec;  \
    if ((result)->tv_usec < 0) {                      \
      --(result)->tv_sec;                             \
      (result)->tv_usec += 1000000;                   \
    }                                                 \
  } while (0)

# define fileno _fileno
# define fstat  _fstat
# define stat   _stat

#endif

#ifndef SUCCESS
# define SUCCESS 0
# define FAILURE 1
#endif

#ifdef MAXPATH
# undef  MAXPATH
# define MAXPATH 260
#endif

extern uint64_t pos;                 /* checker           */
extern struct timeval time_elapsed;  /* verstrichene Zeit */

extern struct timeval time_before;   /* Timer start       */
extern struct timeval time_after ;   /* Timer ende        */
extern struct timeval time_result;   /* Timer Ergebnis    */

extern SOCKET my_sock;               /* socket handle     */

// Proto-Typen für Modulare Programmierung:
extern int init_sockets(void);
extern int init_connect(void);
extern int init_worktui(void);

#endif
