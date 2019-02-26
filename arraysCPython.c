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

  Array *arr = malloc(sizeof(Array));
  arr->capacity = capacity;
  arr->count = 0;
  arr->elements = malloc(capacity * sizeof(char *)); // or sizeof int or size 
  return arr;
}


void destroy_array(Array *arr) {

  // Free all elements
  // Free array
  // for (int i = 0; i < arr->count; i++) {
  //     free(arr->elements[i]);
  // } 
  // free(arr->elements[0]);
  free(arr->elements);
  free(arr);
}


void resize_array(Array *arr) {


  int doubled = 2 * arr->capacity;
  char **new_storage = malloc(doubled * sizeof(char*));
  for (int i = 0; i < arr->count; i++) {
    new_storage[i] = arr->elements[i];
  }
  // free(arr->elements);
  arr->capacity = doubled;
  arr->elements = new_storage;
}





char *arr_read(Array *arr, int index) {


  if (index > arr->count) {
    fprintf(stderr, "Arr-Read IndexError: Index %d out of range\n", index);
    exit(1);
    // return NULL;
  }
    return arr->elements[index];
}


void arr_insert(Array *arr, char *element, int index) {


  if (index > arr->count) {
    fprintf(stderr, "Arr_Insert IndexError: Index %d out of range\n", index);
    exit(1);
  }

  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }

  
  for (int i = arr->count - 1; i >= index; i--) {
    arr->elements[i + 1] = arr->elements[i];
  }
  arr->elements[index] = element;
  arr->count++;
}


void arr_append(Array *arr, char *element) {


  if(! (arr->count < arr->capacity)) {
    printf("ERROR");
    return;
  }

  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }
  char *copy = strdup(element); 
  arr->elements[arr->count] = copy;
  arr->count++;
}


void arr_remove(Array *arr, char *element) {


int pos = -1;
  for (int i = 0; i < arr->count; i++) {
    if (element == arr->elements[i]) {
      pos = i;
      arr->elements[pos] = NULL;
      break;
    }
  }
  for (int j = pos; j < arr->count - 1; j++) {
    arr->elements[j] = arr->elements[j+1]; 
  }
  arr->elements[arr->count-1] = NULL;
  // free(arr->elements[arr->count-1]);
  arr->count--;
}


void arr_print(Array *arr) {
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  // printf("(%d/%d)", arr->count, arr->capacity);
  // printf("(%p)", (void*) &arr->elements);
  printf("]\n");
}


// #ifndef TESTING
int main(void)
{
  printf("*********\n");
  Array *arr = create_array(1); // []
  
  arr_print(arr);
  resize_array(arr);  // []
  arr_print(arr);
  arr_insert(arr, "STRING1", 0); // [STRING1]
  // printf("(%s)\n", arr_read(arr, 0));
  arr_print(arr);
  arr_append(arr, "STRING4"); // [STRING1,STRING4]
  arr_print(arr);
  arr_insert(arr, "STRING2", 0); // [STRING2,STRING1,STRING4]
  arr_print(arr);
  arr_insert(arr, "STRING3", 1); // [STRING2,STRING3,STRING1,STRING4]
  arr_print(arr);
  arr_remove(arr, "STRING3"); // [STRING2,STRING1,STRING4]
  // printf("(%s)\n", arr_read(arr, 0));
  // printf("(%s)\n", arr_read(arr, 1));
  // printf("(%s)\n", arr_read(arr, 2));
  arr_print(arr);

  

  destroy_array(arr);
  // arr_print(arr);

  return 0;
}
// #endif