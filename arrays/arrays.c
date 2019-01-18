#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;

Array *create_array (int capacity) {
    // Allocate memory for the Array struct
    Array *arr = malloc(sizeof(Array));

    // Set initial values for capacity and count
    arr->capacity = capacity;
    arr->count = 0;

    // Allocate memory for elements
    arr->elements = calloc(capacity, sizeof(char*));

    return arr;

}

void destroy_array(Array *arr)
{
    for (int i = 0; i < arr->count; ++i) {
        arr->elements[i] = NULL;
        free(arr->elements[i]);
    }

    free(arr->elements);
    free(arr);
}

void resize_array(Array *arr)
{
    char **storage = calloc((2 * arr->capacity), sizeof(char *));

    for (int i = 0; i < arr->count; ++i) {
        storage[i] = arr->elements[i];
    }

    for (int j = 0; j < arr->count; ++j) {
        arr->elements[j] = NULL;
        free(arr->elements[j]);
    }

    free(arr->elements);

    arr->elements = storage;
    arr->capacity = arr->capacity * 2;
}

char *arr_read(Array *arr, int index) {

    // Throw an error if the index is greater than the current count
    if(arr->count < index) {
        printf("Index is higher that current count.");
        exit(1);
    }

    // Otherwise, return the element at the given index
    return arr->elements[index];
}

void arr_insert(Array *arr, char *element, int index) {

    // Throw an error if the index is greater than the current count
    if(index > arr->count){
        printf("Index is higher than current count.");
        exit(1);
    }

    // Resize the array if the number of elements is over capacity
    if(arr->count + 1 > arr->capacity) {
        resize_array(arr);
    }

    // Move every element after the insert index to the right one position
    for(int i = index; i < arr->count; i++) {
        arr->elements[i + 1] = arr->elements[i];
    }

    // Copy the element and add it to the array
    arr->elements[index] = element;

    // Increment count by 1
    arr->count++;

}

void arr_append(Array *arr, char *element)
{
    if(arr->capacity < arr->count + 1)
    {
        resize_array(arr);
    }

    arr->elements[arr->count] = strdup(element);
    arr->count++;
}

void arr_remove(Array *arr, char *element)
{
    int i = 0;
    while(i < arr->count){
        if(strcmp(arr->elements[i], element) == 0) {
            arr->elements[i] = NULL;
            free(arr->elements[i]);
            break;
        }
        i++;
    }

    if(i == arr->count) {
        fprintf(stderr, "Element not found...");
        exit(1);
    }

    while(i < arr->count) {
        arr->elements[i] = arr->elements[i+1];
        i++;
    }

    arr->count--;
}

void arr_print(Array *arr)
{
    printf("[");
    for (int i = 0; i < arr->count; ++i) {
        printf("%s", arr->elements[i]);
        if(i != arr->count - 1)
        {
            printf(", ");
        }

    }
    printf("]\n");
}

int main(void)
{
    Array *arr = create_array(1);

    arr_insert(arr, "STRING1", 0);
    arr_append(arr, "STRING2");
    arr_insert(arr, "STRING3", arr->count);
    arr_print(arr);
    arr_remove(arr, "STRING2");
    printf("[%s]\n", arr_read(arr, 1));
    arr_print(arr);
    destroy_array(arr);
    arr_insert(arr, "STRING2", 1);
    arr_print(arr);
    return 0;
}
