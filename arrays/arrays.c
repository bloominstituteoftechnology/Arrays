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
  Array *arr = malloc(sizeof(Array));
  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;
  // Allocate memory for elements
  arr -> elements = malloc(sizeof(char *) * capacity);

  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  //Create loop to free elements
  for(int i=0; i <arr->count; i++) {
    free(arr->elements[i]);
  }

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
  char **doubleCapacityStorage = malloc(sizeof(char *) * (arr->capacity * 2));
  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++) {
    doubleCapacityStorage[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  if (arr->elements != NULL) {
    free(arr->elements);
  }
  // Update the elements and capacity to new values
  arr->elements = doubleCapacityStorage;
  arr->capacity = arr->capacity * 2;

  printf("Resize");
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

  // Throw an error if the index is greater or equal to than the current count
  if (index >= arr->count) {
    fprintf(stderr, "IndexError: Array index is out of range.");
    return NULL;
  }
  // Otherwise, return the element at the given index
  return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *
 * Store the VALUE of the given string, not the REFERENCE
 *****/
void arr_insert(Array *arr, char *element, int index) 
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    //print standard error
    fprintf(stderr, "Attempted to insert but index is out of range");
    //exit(1);
    return;
  }
  // Resize the array if the number of elements is over capacity
  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = arr->count; i >= 0; i--) {
    arr->elements[i - 1] = arr->elements[i];
  }
  // Copy the element (hint: use `strdup()`) and add it to the array
  char *element_copy = strdup(element);
  arr->elements[index] = element_copy;
  // Increment count by 1
  arr->count++;

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) 
{
  
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->capacity <= arr->count) {
    resize_array(arr);
    //fprintf(stderr, "Yo, error!/n");
    return;
  }

  //otherwise, let's copy elements and append to the back of the array
  //strdup is recommended => hidden malloc inside here
  char *element_copy = strdup(element);
  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = element_copy;
  // Increment count by 1
  arr->count++;

}


/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) 
{

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  for (int i = 0; i < arr->count; i++) {
    if (strcmp(arr->elements[i], element) == 0) {

      free(arr->elements[i]);
      for (int x = 1; x < arr->count - i; x++) {

        // Shift over every element after the removed element to the left one position
        arr->elements[x] = arr->elements[x + 1];

      }
    }
  }
  // Decrement count by 1
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
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  //arr_insert(arr, "STRING3", 1);
  //arr_print(arr);
  //arr_remove(arr, "STRING3");
  //arr_print(arr);

  // destroy_array(arr);

  return 0;
}
#endif
