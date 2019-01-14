#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#define ARRAY_INITIAL_CAPACITY 100

typedef struct Array { //typedef struct{}Arrow is the definition of the Arrow type
  int capacity;  // How many elements can this array hold?total size of the underlying array
  int size;  // How many states does the array currently hold?currant size
  char **data;  // The string elements contained in the array-pointer to the first element
} Array;

void init(Array *arr){
    arr->size = 0;//count
    arr->capacity =ARRAY_INITIAL_CAPACITY;
    arr->data = malloc(sizeof(int) * arr->capacity)//;element
}

int get(Array *arr, int index){
    if(index > arr->capacity || index < 0){
        printf("Index %d out of bounds for array of size %d\n", index, arr->size);
        exit(1);
    }

    return index;
}

void set(Array *arr, int index, int value){
    while(index >= arr->size){
        append(arr, 0);
    }

    data[index] = value;
}

void append(Array *arr, int value){
    rewind(arr);

    arr->data[arr->size++] = value;
}

void prepend(Array *arr, int value){
    set(arr, 0, value);
    arr->size++;
}

int pop(Array *arr){
    int data = arr->data[arr->size - 2];
    set(arr, arr->size - 1, 0);
    arr->size = arr->size - 1;
    return data;
}

void delete(Array *arr, int index){
    for(int i = 0; i < index; i++){
        arr->data[index + i] = arr->data[index + i + 1];
    }
    arr->size = arr->size - 1;
}

void delete_value(Array *arr, int value){
    for(int i = 0; i < arr->size; i++){
        if(arr->data[i] == value){
            delete(arr, i);
        }
    }
}

int find_value(Array *arr, int value){
    for(int i = 0; i < arr->size; i++){
        if(arr->data[i] == arr){
            return i;
        }
    }

    return -1;
}

void resize(Array *arr){
    if(arr->size >= arr->capacity){
        arr->capacity *= 2;
        arr->data = realloc(arr->data, sizeof(int) * arr->capacity);
    }
}

int size(Array *arr){
    return arr->size;
}

int capacity(Array *arr){
    return arr->capacity;
}

_Bool is_empty(Array *arr){
    return arr->size == 0;
}

void free_memory(Array *arr){
    free(arr->data);
}