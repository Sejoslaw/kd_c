// Global define.
#define KD_DEFINE
// Collections-specific define.
#define KD_COLLECTION_DEFINE
#include "../kd.h"

void test_foreach(kd_collection *col, kd_collection_element *element) {
    printf("col = %p ; element = %p ; element value = %i \n", col, element->value, *(int *) element->value);
}

int main(int argc, char *argv[]) {
    kd_collection *col = kd_collection_new();
    printf("Collection created - col: %p ; head: %p ; size: %i \n", col, col->head, (int) col->size);
    printf("Collection is empty: %i \n", kd_collection_is_empty(col));

    printf("Adding elements to collection... \n");

    int i = 0;
    while (i < 10) {
        int *ptr = malloc(sizeof(int));
        *ptr = i;
        printf("ptr: %p ; ptr val: %i \n", ptr, *ptr);
        kd_collection_add(col, ptr);
        i++;
    }

    printf("Added records: %i \n", (int) col->size);
    printf("Collection is empty: %i \n", kd_collection_is_empty(col));

    // This will give you value 5.
    // This is counted from 0.
    kd_collection_element *element = kd_collection_get(col, 6);
    printf("col[5] = %p ; col[5].value = %i \n", element->value, *(int *) element->value);

    printf("Removing value... \n");
    kd_collection_remove(col, 6);

    // Now it will give you the vlaue of 6 because we removed value 5.
    element = kd_collection_get(col, 6);
    printf("col[5] = %p ; col[5].value = %i \n", element->value, *(int *) element->value);

    printf("Testing foreach... \n");
    kd_collection_foreach(col, &test_foreach);

    printf("Setting value... \n");
    element = kd_collection_get(col, 7);
    printf("col[6] = %p ; col[6].value = %i \n", element->value, *(int *) element->value);
    int *ptr = malloc(sizeof(int));
    *ptr = 123;
    kd_collection_set(col, 7, ptr);
    element = kd_collection_get(col, 7);
    printf("col[6] = %p ; col[6].value = %i \n", element->value, *(int *) element->value);

    printf("Testing parse... \n");
    void **table = (void **) malloc(5 * sizeof(void *));
    i = 0;
    while (i < 5) {
        int *ptr = malloc(sizeof(int));
        *ptr = i + 1234;
        table[i] = ptr;
        i++;
    }
    col = kd_collection_parse(table, 5);
    element = kd_collection_get(col, 2);
    printf("col[1] = %p ; col[1].value = %i \n", element->value, *(int *) element->value);
}
