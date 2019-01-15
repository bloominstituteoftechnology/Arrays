#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // Number of elements or size/length of array (How many states does the array currently hold?)
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
// Use malloc() if you are going to set everything that you use in the allocated space.
// Use calloc() if you're going to leave parts of the data uninitialized - and it would be beneficial to have the unset parts zeroed.
Array *create_array (int capacity) {
  // Allocate memory for the Array struct
  Array *newArr = malloc(sizeof(Array)); // allocates memory for a size of 1 struct Array
  
  // Set initial values for capacity and count
  newArr->capacity = capacity;
  newArr->count = 0;

  // Allocate memory for elements
  // hint: use `calloc`, code from lecture
  newArr->elements = calloc(capacity, sizeof(char *));

  return newArr;
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
  char **doubleCapacity = calloc((arr->capacity * 2), sizeof(char *));

  // Copy elements into the new storage
  for (int i=0; i< arr->count; i++) {
    doubleCapacity[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  if (arr->elements != NULL) {
    free(arr->elements);
  }

  // Update the elements and capacity to new values
  arr->elements = doubleCapacity; // set elements array with newly, expanded array
  arr->capacity *= 2; // set the new capacity by 2
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
// fprintf writes formatted text to the output stream you specify.
// printf is equivalent to writing fprintf(stdout, ...) and
// writes formatted text to wherever the standard output stream is currently pointing.
// sprintf writes formatted text to an array of char, as opposed to a stream.
char *arr_read(Array *arr, int index) {
  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    fprintf(stderr, "Index is out of range.");
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
    fprintf(stderr, "Index is out of range.");
    exit(1);
  }

  // Resize the array if the number of elements is equal to or over capacity
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i=arr->count; i > index; i--) {
    arr->elements[i] = arr->elements[i-1]; // repointing the new address to previous element's address
  }

  // Copy the element and add it to the array
  char *new_element = element; // copy the element so it doesn't get lost
  arr->elements[index] = new_element; // setting a value at specified index

  // Increment count by 1
    arr->count += 1;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  // Resize the array if the number of elements is equal to or over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = element;

  // Increment count by 1
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
  // MY TESTS
  Array *arr = create_array(3);
  arr_append(arr, "first");
  arr_append(arr, "second");
  arr_append(arr, "third");
  printf("%s \n", arr_read(arr, 1));
  arr_print(arr);
  arr_insert(arr, "fourth", 0);
  arr_print(arr);
  arr_insert(arr, "fifth", 2);
  arr_print(arr);
  arr_append(arr, "sixth");
  arr_append(arr, "seventh");
  arr_print(arr);
  destroy_array(arr);

  // PRESET TESTS
  // Array *arr = create_array(1);

  // arr_insert(arr, "STRING1", 0);
  // arr_append(arr, "STRING4");
  // arr_insert(arr, "STRING2", 0);
  // arr_insert(arr, "STRING3", 1);
  // arr_print(arr);
  // arr_remove(arr, "STRING3");
  // arr_print(arr);

  // destroy_array(arr);

  return 0;
}
#endif
