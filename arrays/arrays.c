#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
  // Allocate memory for the Array struct
  // Set initial values for capacity and count
  // Allocate memory for elements
  Array* arr = malloc(sizeof(Array));
  arr-> capacity = capacity;
  arr->count = 0;
  arr->elements = malloc(capacity * sizeof(char*)); // or sizeof int or size 
  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  // Free array
  // for (int i = 0; i < arr->count; ++i) {
  //   free(arr->elements[i]);
  // }
  free(arr->elements);
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  // Copy elements into the new storage
  // Free the old elements array (but NOT the strings they point to)
  // Update the elements and capacity to new values
  
  int doubled = 2 * arr->capacity;
  char **new_storage = malloc(doubled * sizeof(char*));
  for (int i = 0; i < arr->count; i++) {
    new_storage[i] = arr->elements[i];
  }
  free(arr->elements);
  arr->capacity = doubled;
  arr->elements = new_storage;
}




/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index) {

  // Throw an error if the index is greater than the current count
  // Otherwise, return the element at the given index

  if (index >= arr->count) {
    fprintf(stderr, "IndexError: Index %d out of range\n", index);
    // exit(1);
    return NULL;
  }
    return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  // Resize the array if the number of elements is over capacity
  // Move every element after the insert index to the right one position
  // Copy the element and add it to the array
  // Increment count by 1
  if (index > arr->count) {
    fprintf(stderr, "IndexError: Index %d out of range\n", index);
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

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  // Copy the element and add it to the end of the array
  // Increment count by 1


  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }
  arr->elements[arr->count] = element;
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  // Shift over every element after the removed element to the left one position
  // Decrement count by 1
  int m = -1;
  for (int i = 0; i < arr->count; i++) {
    if (element == arr->elements[i]) {
      m = i;
    }
    if (m > -1) {
      arr->elements[i] = arr->elements[i+1];
    }
  }
  free(arr->elements[arr->count]);
  arr->count--;
}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("(%d/%d)", arr->count, arr->capacity);
  printf("]\n");
}


#ifndef TESTING
int main(void)
{
  printf("*********\n");
  Array *arr = create_array(1); // []
  arr_print(arr);
  resize_array(arr);  // []
  arr_print(arr);
  arr_insert(arr, "STRING1", 0); // [STRING1]
  arr_print(arr);
  arr_append(arr, "STRING4"); // [STRING1,STRING4]
  arr_print(arr);
  arr_insert(arr, "STRING2", 0); // [STRING2,STRING1,STRING4]
  arr_print(arr);
  arr_insert(arr, "STRING3", 1); // [STRING2,STRING3,STRING1,STRING4]
  arr_print(arr);
  arr_remove(arr, "STRING3"); // [STRING2,STRING1,STRING4]
  arr_print(arr);

  destroy_array(arr);
  // arr_print(arr);

  return 0;
}
#endif
