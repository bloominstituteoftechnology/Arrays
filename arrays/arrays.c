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
  Array *new_arr = malloc(sizeof(Array));

  // Set initial values for capacity and count 
  new_arr->capacity = capacity;
  new_arr->count = 0;
  // Allocate memory for elements
  new_arr->elements = calloc(capacity, sizeof(char *));
  // --> here we allocate the memory for the amount of elements the array holds
  // --> AND specify the size of char *

  return new_arr;

}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {
  // Free all elements
  free(arr->elements);
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {
  // Create a new element storage with double capacity
  int new_cap = arr->capacity;  
  char **new_elem = calloc(new_cap * 2, sizeof(char *));
  // Copy elements into the new storage  
  for (int i = 0; i < arr->count; i++) {
    new_elem[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = new_elem;  // --> Sets the old elements into the new elements array
  arr->capacity = arr->capacity * 2; // --> array now has double capacity || resize happens here really
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
  if (index < arr->count) {
    fprintf(stderr, "Index greater than count of array (read)\n");
    exit(1);
  }
  // Otherwise, return the element at the given index
  return arr->elements[index];  
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {  
   // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    fprintf(stderr, "Index greater than count of array (insert)\n");
    exit(1);
  }
  // Resize the array if the number of elements is over capacity
  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = 0; i < arr->count; i++) {
    arr->elements[i + 1] = arr->elements[i]; // --> Free up a space for new insert
  }
  // Copy the element and add it to the array
  arr->elements[index] = element; // --> Given an index, we insert the element given here
  // Increment count by 1
  arr->count = arr->count + 1;  
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }
  // Copy the element and add it to the end of the array
  arr->elements[arr->count + 1] = element;
  // Increment count by 1
  arr->count = arr->count + 1;
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
  for (int i = 0; i < arr->count; i++) {

    if (arr->elements[i] == element) { // --> if given element == an item in our elements array
      free(arr->elements[i]); // --> Free its memory
      arr->elements[i] = NULL; // --> Set to NULL
    } else {
      fprintf(stderr, "Could not find element (remove)");
      exit(1);
    }

  }
  // Shift over every element after the removed element to the left one position
  for (int i = 0; i < arr->count; i++) {

  }
  // Decrement count by 1
  arr->count = arr->count - 1;
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
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
