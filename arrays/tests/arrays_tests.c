#include <arrays.h>
#include "../utils/minunit.h"

char *day_1_array_tests()
{
    Array *arr = create_array(3);

    mu_assert(arr->count == 0, "Create failed");
    mu_assert(arr->capacity == 3, "Create failed");

    mu_assert(arr_read(arr, 0) == NULL, "Value initialized not null");

    arr_append(arr, "VALUE-1");

    mu_assert(strcmp(arr_read(arr, 0), "VALUE-1") == 0, "Append value failed");
    mu_assert(arr_read(arr, 1) == NULL, "Append value failed");
    mu_assert(arr->count == 1, "Append value failed");

    arr_append(arr, "VALUE-2");

    mu_assert(strcmp(arr_read(arr, 1), "VALUE-2") == 0, "Append value failed");
    mu_assert(arr_read(arr, 2) == NULL, "Append value failed");
    mu_assert(arr->count == 2, "Append value failed");

    destroy_array(arr);

    return NULL;
}

char *day_2_array_tests()
{
    Array *arr = create_array(1);

    arr_insert(arr, "VALUE-1", 0);

    mu_assert(strcmp(arr_read(arr, 0), "VALUE-1") == 0, "Insert value failed");

    arr_insert(arr, "VALUE-2", 0);

    mu_assert(arr->capacity == 2, "Resize array on insert failed");
    mu_assert(arr->count == 2, "Resize array on insert failed");

    mu_assert(strcmp(arr_read(arr, 0), "VALUE-2") == 0, "Insert value failed");
    mu_assert(strcmp(arr_read(arr, 1), "VALUE-1") == 0, "Insert value failed");

    arr_insert(arr, "VALUE-3", 1);

    mu_assert(arr->capacity == 4, "Resize array on insert failed");
    mu_assert(arr->count == 3, "Resize array on insert failed");

    mu_assert(strcmp(arr_read(arr, 0), "VALUE-2") == 0, "Insert value failed");
    mu_assert(strcmp(arr_read(arr, 1), "VALUE-3") == 0, "Insert value failed");
    mu_assert(strcmp(arr_read(arr, 2), "VALUE-1") == 0, "Insert value failed");

    arr_remove(arr, "VALUE-3");

    mu_assert(arr->count == 2, "Remove count failed");

    mu_assert(strcmp(arr_read(arr, 0), "VALUE-2") == 0, "Remove value failed");
    mu_assert(strcmp(arr_read(arr, 1), "VALUE-1") == 0, "Remove value failed");
    mu_assert(arr_read(arr, 2) == NULL, "Remove value failed");

    destroy_array(arr);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(day_1_array_tests);
    mu_run_test(day_2_array_tests);

    return NULL;
}

RUN_TESTS(all_tests);