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
    mu_assert(arr_read(arr, 2) == NULL, "Should throw index error");
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


/* NOTE: you will need to add your 
    function declarations in arrays.h and 
    implement them in arrays.c for each test 
    to work as expected. Comment these out
    as you complete them. */
char *stretch_array_tests()
{
    Array *arr = create_array(10);

    /* CLEAR */
    // arr_append(arr, "VALUE-1");
    // arr_append(arr, "VALUE-2");
    // mu_assert(arr->count == 2, "Count should be updated after append.");

    // arr_clear(arr);
    // mu_assert(arr->count == 0, "Array should be empty after clear.");

    // arr_append(arr, "VALUE-3");
    // mu_assert(strcmp(arr_read(arr, 0), "VALUE-3") == 0, "Append after clear failed.");

    /* COPY */
    // Array *cpy_arr = arr_copy(arr);

    // mu_assert(strcmp(arr_read(arr, 0), arr_read(cpy_arr, 0)) == 0, "Copied arr's first element did not match.");
    // mu_assert(arr->capacity == cpy_arr->capacity, "Copied capacity did not match.");
    // mu_assert(arr->count == cpy_arr->count, "Copied count did not match.");

    // arr_append(cpy_arr, "VALUE-4");
    // mu_assert(arr->count+1 == cpy_arr->count, "Count was not incremented in copied array.");
    // mu_assert(strcmp(arr_read(cpy_arr, arr->count), "VALUE-4") == 0, "Did not append correct value on copied array.");

    /* EXTEND */
    // int expected_count = arr->count + cpy_arr->count;
    // arr_extend(arr, cpy_arr);
    // mu_assert(arr->count == expected_count, "Count wasn't increased after extend.");
    // mu_assert(strcmp(arr_read(arr, arr->count-1), arr_read(cpy_arr, cpy_arr->count-1)) == 0, "Extend altered ordering incorrectly.");

    // destroy_array(cpy_arr);

    /* INDEX */
    // mu_assert(arr_index(arr, "VALUE-3") == 0, "Index did not find first matching element correctly.");
    // arr_remove(arr, "VALUE-3");
    // mu_assert(arr_index(arr, "VALUE-4") == 1, "Index did not find matching element correctly.");
    // mu_assert(arr_index(arr, "VALUE-1001") == -1, "Index did not return -1 for non-existing element.");

    /* POP */
    // int previous_count = arr->count;
    // arr_pop(arr, 1);
    // mu_assert(arr->count == --previous_count, "Count was not decremented correctly during pop.");
    // mu_assert(arr_pop(arr, 100) == NULL, "Should return null with non-existent indices.");

    // arr_append(arr, "VALUE-5");
    // char *tmp = arr_pop(arr, -1);
    // mu_assert(strcmp(tmp, "VALUE-5") == 0, "Negative indices should work if in range (like in Python).");
    // free(tmp);
    // mu_assert(arr->count == previous_count, "Count was not decremented correctly during pop.");

    /* REVERSE */
    // arr_append(arr, "VALUE-5");
    // arr_append(arr, "VALUE-6");
    // arr_append(arr, "VALUE-7");

    // arr_reverse(arr);
    // mu_assert(arr->count-3 == previous_count, "Count was not maintained correctly during reverse.");
    // mu_assert(strcmp(arr_read(arr, 0), "VALUE-7") == 0, "Array was not reversed correctly.");

    /* SORT */
    // arr_sort(arr);
    // mu_assert(strcmp(arr_read(arr, arr->count-1), "VALUE-7") == 0, "Array was not sorted correctly.");

    destroy_array(arr);

    return NULL;
}


char *all_tests()
{
    mu_suite_start();

    mu_run_test(day_1_array_tests);
    mu_run_test(day_2_array_tests);
    mu_run_test(stretch_array_tests);

    return NULL;
}

RUN_TESTS(all_tests);