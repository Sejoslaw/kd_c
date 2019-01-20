/* kd.h - v1.1.0 - Krzysztof Dobrzynski's main library -- https://github.com/Sejoslaw/kd_c

    No warranty is offered or implied; use this code at your own risk !!!

    This is a single header file for getting stuff done in C/C++.

    ====================================================================
    Before you start doing anything you must define:

    #define KD_DEFINE
    #include "kd.h"

    In other files you must just include "kd.h" without the #define.
    ====================================================================
    If you want to use collections module, you must defile:

    #define KD_COLLECTION_DEFINE
    ====================================================================

    For the license please see: https://github.com/Sejoslaw/kd_c/blob/master/LICENSE

    Versions:
        1.1.0 - Added collections.
        1.0.1 - Moved more common stuff from other libraries
        1.0.0 - Initial version
*/

// Global define for whole library.
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
typedef unsigned char KD_BOOL;
#define KD_TRUE 1
#define KD_FALSE 0

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

// Define made special for collections.
#ifdef KD_COLLECTION_DEFINE

/*
    Collections
*/
typedef long double kd_collection_size;
typedef long double kd_collection_index;

typedef struct kd_collection_element
{
    void *value;
    struct kd_collection_element *next_element;
} kd_collection_element; // Element of a collection.

typedef struct kd_collection
{
    struct kd_collection_element *head;
    kd_collection_size size; // Size of a collection.
} kd_collection; // General definition of a collection (Collection, List, Queue, Stack, etc.).

// Creates new collection.
static kd_collection *kd_collection_new() {
    kd_collection *col = malloc(sizeof(kd_collection));
    col->head = NULL;
    col->size = 0;
    return col;
}

// Converts given value to collection element.
static kd_collection_element *kd_collection_new_element(void *value) {
    kd_collection_element *element = malloc(sizeof(kd_collection_element));
    element->value = value;
    element->next_element = NULL;
    return element;
}

// Returns KD_TRUE if the collection is empty; KD_FALSE otherwise.
static KD_BOOL kd_collection_is_empty(kd_collection *col) {
    if (col->size == 0) {
        return KD_TRUE;
    }
    return KD_FALSE;
}

// Returns KD_TRUE if the element was added to the collection; KD_FALSE otherwise.
static KD_BOOL kd_collection_add(kd_collection *col, void *value) {
    if (col == NULL) {
        return KD_FALSE;
    }

    if (kd_collection_is_empty(col)) {
        col->head = kd_collection_new_element(value);
        col->size++;
        return KD_TRUE;
    }

    kd_collection_element *current = col->head;
    while (current->next_element) {
        current = current->next_element;
    }

    current->next_element = kd_collection_new_element(value);
    col->size++;

    return KD_TRUE;
}

// Returns target collection at the end of source collection.
static KD_BOOL kd_collection_add_collection(kd_collection *source, kd_collection *target) {
    if (target == NULL || target->head == NULL) {
        return KD_FALSE;
    }

    kd_collection_element *current = target->head;
    while (current) {
        kd_collection_add(source, current->value);
        current = current->next_element;
    }

    return KD_TRUE;
}

// Clears given collection.
static void kd_collection_clear(kd_collection *col) {
    col->head = NULL;
    col->size = 0;
}

// Returns the value on index position inside the specified colelction.
static kd_collection_element *kd_collection_get(kd_collection *col, kd_collection_index index) {
    if (index < 0 || kd_collection_is_empty(col)) {
        return NULL;
    }

    if (index == 0) {
        return col->head;
    }

    kd_collection_element *current = col->head;
    kd_collection_index i = 0;

    while (i < index - 1) {
        if (current->next_element == NULL) {
            return NULL;
        }
        current = current->next_element;
        i++;
    }

    return current;
}

// Returns the removed element from the specified position from the given collection.
static void *kd_collection_remove(kd_collection *col, kd_collection_index index) {
    if (index < 0 || kd_collection_is_empty(col)) {
        return NULL;
    }

    kd_collection_element *current = kd_collection_get(col, index - 1);
    kd_collection_element *tmp = current->next_element;
    void *val = tmp->value;
    current->next_element = tmp->next_element;
    col->size--;

    free(tmp);

    return val;
}

// Sets the given value at the specified index in given collection.
static void kd_collection_set(kd_collection *col, kd_collection_index index, void *value) {
    if (index < 0 || kd_collection_is_empty(col)) {
        return;
    }

    kd_collection_element *current = kd_collection_get(col, index);
    current->value = value;
}

// Returns the sublist of elements from specified collection.
static kd_collection *kd_collection_sub_collection(kd_collection *col, kd_collection_index start_index, kd_collection_index end_index) {
    if (kd_collection_is_empty(col) || start_index > end_index || col->size < (end_index - start_index)) {
        return NULL;
    }

    kd_collection *new_col = kd_collection_new();

    kd_collection_element *current = kd_collection_get(col, start_index);

    kd_collection_index i = start_index;
    while (i < end_index) {
        kd_collection_add(new_col, current);
        current = current->next_element;
    }

    return new_col;
}

// Returns, but does NOT remove, the head of the collection.
static kd_collection_element *kd_collection_peek(kd_collection *col) {
    if (kd_collection_is_empty(col)) {
        return NULL;
    }

    return col->head->value;
}

// Returns and removes the head of given collection.
static kd_collection_element *kd_collection_poll(kd_collection *col) {
    if (kd_collection_is_empty(col)) {
        return NULL;
    }

    kd_collection_element *head = col->head;
    col->head = head->next_element;
    col->size--;
    
    return head;
}

// Returns KD_TRUE if the element was added at the front of the collection; otherwise KD_FALSE;
static KD_BOOL kd_collection_push(kd_collection *col, void *value) {
    if (col == NULL) {
        return KD_FALSE;
    }

    kd_collection_element *new_element = kd_collection_new_element(value);
    new_element->next_element = col->head;
    col->head = new_element;
    col->size++;

    return KD_TRUE;
}

// Executes given function on each element of given collection
static void kd_collection_foreach(kd_collection *col, void (*kd_collection_action)(kd_collection *, kd_collection_element*)) {
    if (kd_collection_is_empty(col)) {
        return;
    }

    kd_collection_element *current = col->head;
    while (current) {
        (*kd_collection_action)(col, current);
        current = current->next_element;
    }
}

// Parses given table to a collection.
static kd_collection *kd_collection_parse(void **table, int collection_size) {
    kd_collection *col = kd_collection_new();

    if (!table) {
        return col;
    }

    int i = 0;
    while (i < collection_size) {
        void *value = table[i];
        kd_collection_add(col, value);
        i++;
    }

    return col;
}

#endif // KD_COLLECTION_DEFINE

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KD_DEFINE

/*
    As a reminder - https://en.wikipedia.org/wiki/C_data_types

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