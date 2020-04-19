// Global define.
#define KD_VECTOR_DEFINE
#include "../kd_vector.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    kd_vector *vec = kd_vector_new(10);

    kd_vector_add(vec, "Simple");
    kd_vector_add(vec, "test");
    kd_vector_add(vec, "if");
    kd_vector_add(vec, "working");

    for (int i = 0; i < kd_vector_count(vec); i++) {
        printf("%s ", (char *) kd_vector_get(vec, i));
    }

    printf("\n");

    kd_vector_delete(vec, 3);
    kd_vector_delete(vec, 2);
    kd_vector_delete(vec, 1);

    kd_vector_set(vec, 0, "Hello");
    kd_vector_add(vec, "World");

    for (int i = 0; i < kd_vector_count(vec); i++) {
        printf("%s ", (char *) kd_vector_get(vec, i));
    }

    printf("\n");

    kd_vector_free(vec);
}
