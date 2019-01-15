#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;     // How many elements can this array hold?
  int count;        // How many states does the array currently hold?
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
Array *create_array (int capacity) {       // This needs to return a pointer to an Array
  // Allocate memory for the Array struct
  Array *array = malloc(sizeof(Array));

  // Set initial values for capacity and count
  array->capacity = capacity;
  array->count = 0;

  // Allocate memory for elements
  array->elements = calloc(capacity, sizeof(char *)); // calloc takes 2 args: # of blocks to allocate, and size of each block
                                                      // use sizeof(char *) because elements holds char *'s not actual char's

  return array;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Set elements equal to NULL and then free all elements
  for(int i = 0; i < arr->count; i++){ 
    arr->elements[i] = NULL; 
    free(arr->elements[i]);
  }

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
  char **newElements = calloc((arr->capacity * 2), sizeof(char *));
  // Copy elements into the new storage
    //step through length of arr->elements, meaning step through arr->count
    //for each i set newElements[i] = arr->elements[i]
  for (int i = 0; i < arr->count; i++) {
    newElements[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  for (int i = 0; i < arr->count; i++) {
    arr->elements[i] = NULL;
    free(arr->elements[i]);
  }
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = newElements;
  arr->capacity = arr->capacity * 2;
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
  if(index > arr->count){
    fprintf(stderr, "Index is greater than current count.");
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
  if(index > arr->count){
    fprintf(stderr, "Index is greater than current count.");
    exit(1);
  }
  // Resize the array if the number of elements (after insert) is over capacity
  if (arr->count + 1 > arr->capacity) {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = arr->count - 1; i >= index; i--) {
    arr->elements[i + 1] = arr->elements[i];
  }
  // Copy the element and add it to the array
  arr->elements[index] = element;
  // Increment count by 1
  arr->count++;
  // insert seems to be working based on prints in main()
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if(arr->count >= arr->capacity){
		resize_array(arr);
	}
  // Copy the element and add it to the end of the array
  char *new_element = strdup(element);
  arr->elements[arr->count] = new_element;
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
