/* kd.h - v1.0.1 - Krzysztof Dobrzynski's main library -- https://github.com/Sejoslaw/kd_c

    No warranty is offered or implied; use this code at your own risk !!!

    This is a single header file for getting stuff done in C/C++.

    ====================================================================
    Before you start doing anything you must define:

    #define KD_DEFINE
    #include "kd.h"

    In other files you must just include "kd.h" without the #define.
    ====================================================================

    For the license please see: https://github.com/Sejoslaw/kd_c/blob/master/LICENSE

    Versions:
        1.0.1 - Moved more common stuff from other libraries
        1.0.0 - Initial version
*/

#ifdef KD_DEFINE

/* 
    Include standard C libraries / headers

    Full list of standard C libraries can be found here: https://en.wikipedia.org/wiki/C_standard_library
*/
#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
// #include <stdalign.h>
#include <stdarg.h>
// #include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// #include <stdnoreturn.h>
#include <string.h>
// #include <tgmath.h>
// #include <threads.h>
// #include <pthread.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>

/*
    C++ specific stuff
*/
#ifdef __cplusplus
#define KD_EXTERN extern "C"
#else
#define KD_EXTERN extern
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif

/*
    System constants
*/
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif // !NULL

/*
    Boolean operators
*/
#ifndef TRUE
#define KD_TRUE 1
#define KD_FALSE 0
#endif // !TRUE

/*
    Arithmetic
*/
#define kd_min(a, b) (a < b ? a : b)
#define kd_max(a, b) (a > b ? a : b)

/*
    Geometry
*/
#define KD_PI 3.14159265358979323846f
#define kd_deg2rad(a) (a * (KD_PI / 180))
#define kd_rad2deg(a) (a * (180 / KD_PI))

/*
    Files
*/
#define KD_FILE_READ "r"
#define KD_FILE_READ_BINARY "rb"
#define KD_FILE_WRITE "w"
#define KD_FILE_WRITE_BINARY "wb"
#define KD_FILE_APPEND "a"
#define KD_FILE_APPEND_BINARY "ab"
#define KD_FILE_READ_WRITE "r+"
#define KD_FILE_READ_WRITE_BINARY "r+b"
#define KD_FILE_READ_WRITE_CREATE "w+"
#define KD_FILE_READ_WRITE_CREATE_BINARY "w+b"
#define KD_FILE_READ_WRITE_CREATE_APPEND "a+"
#define KD_FILE_READ_WRITE_CREATE_APPEND_BINARY "a+b"

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KD_DEFINE

/*
    Just as a reminder: (if you need it see: https://en.wikipedia.org/wiki/C_data_types)

    char	                1 byte	            -128 to 127 _OR_ 0 to 255
    signed char	            1 byte	            -128 to 127
    unsigned char	        1 byte	            0 to 255
    int	                    2 or 4 bytes	    -32,768 to 32,767 _OR_ -2,147,483,648 to 2,147,483,647
    unsigned int	        2 or 4 bytes	    0 to 65,535 _OR_ 0 to 4,294,967,295
    short	                2 bytes	            -32,768 to 32,767
    unsigned short	        2 bytes	            0 to 65,535
    long	                4 bytes	            -2,147,483,648 to 2,147,483,647
    unsigned long	        4 bytes	            0 to 4,294,967,295
    float	                4 bytes	            1.2E-38 to 3.4E+38	                => 6 decimal places
    double	                8 bytes	            2.3E-308 to 1.7E+308	            => 15 decimal places
    long long               8 bytes             -9.223372E-18 to 9.223372E-18
    unsigned long long      8 bytes             0 to 18,446,744,073,709,551,615
    long double	            12 or 16 bytes      3.4E-4932 to 1.1E+4932	            => 19 decimal places
*/