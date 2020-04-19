/* kd_vector.h - v1.0.0 - Krzysztof Dobrzynski's vector library -- https://github.com/Sejoslaw/kd_c

    No warranty is offered or implied; use this code at your own risk !!!

    This is a single header file for getting stuff done in C/C++.

    ====================================================================
    Before you start doing anything you must define:

    #define KD_VECTOR_DEFINE
    #include "kd_vector.h"

    In other files you must just include "kd_vector.h" without the #define.
    ====================================================================

    For the license please see: https://github.com/Sejoslaw/kd_c/blob/master/LICENSE

    Versions:
        1.0.0 - Initial version
*/

// Global define for whole library.
#ifdef KD_VECTOR_DEFINE

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct kd_vector {
    void **data;
    int capacity;
    int count;
} kd_vector;

kd_vector *kd_vector_new(int capacity) {
    kd_vector *vec = malloc(sizeof(kd_vector));

    vec->capacity = capacity;
    vec->count = 0;
    vec->data = malloc(sizeof(void *) * vec->capacity);

    return vec;
}

int kd_vector_count(kd_vector *v) {
    return v->count;
}

void vector_resize(kd_vector *v, int capacity) {
    void **items = realloc(v->data, sizeof(void *) * capacity);
    
    if (items) {
        v->data = items;
        v->capacity = capacity;
    }
}

void kd_vector_add(kd_vector *v, void *element) {
    if (v->capacity == v->count) {
        vector_resize(v, v->capacity * 2);
    }

    v->data[v->count++] = element;
}

void kd_vector_set(kd_vector *v, int index, void *element) {
    if (index >= 0 && index < v->count) {
        v->data[index] = element;
    }
}

void *kd_vector_get(kd_vector *v, int index) {
    if (index >= 0 && index < v->count) {
        return v->data[index];
    }

    return NULL;
}

char kd_vector_delete(kd_vector *v, int index) {
    if (index < 0 || index >= v->count) {
        return 0;
    }

    v->data[index] = NULL;

    for (int i = index; i < v->count - 1; i++) {
        v->data[i] = v->data[i + 1];
        v->data[i + 1] = NULL;
    }

    v->count--;

    if (v->count > 0 && v->count == v->capacity / 4) {
        vector_resize(v, v->capacity / 2);
    }

    return 1;
}

void kd_vector_free(kd_vector *v) {
    free(v->data);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // KD_VECTOR_DEFINE