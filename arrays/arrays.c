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
  Array *Array = malloc(sizeof(struct Array));  
  // Set initial values for capacity and count
  Array->capacity = capacity;
  Array->count = -1;
  // Allocate memory for elements
  Array->elements = malloc(capacity);
  return Array;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements

  free(arr->elements);
  free(arr);

  // Free array

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  arr->capacity *= 2;

  // Copy elements into the new storage
  arr->elements = realloc(arr->elements, arr->capacity);

  free(*arr->elements);
  return;

  // Free the old elements array (but NOT the strings they point to)

  // Update the elements and capacity to new values

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

  // Otherwise, return the element at the given index
  return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *
 * Store the VALUE of the given string, not the REFERENCE
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count

  // Resize the array if the number of elements is over capacity
  if(arr->count + 1 > arr->capacity){
    resize_array(arr);
  }
  
  for(int i = index; i < arr->count; i++){  
    arr->elements[i+1] = arr->elements[i];
  }
  arr->elements[index] = element;
  ++arr->count;

  // Move every element after the insert index to the right one position

  // Copy the element (hint: use `strdup()`) and add it to the array

  // Increment count by 1

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  if(arr->count + 1 > arr->capacity){
    resize_array(arr);
  }

  arr->elements[++arr->count] = element;

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.

  // Copy the element and add it to the end of the array

  // Increment count by 1

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
  int index;
  for(int i = 0; i < arr->count; i++){
    if(arr->elements[i] == element){
      index = i;
      arr->elements[i] = NULL;
      free(arr->elements[i]);
    }    
  }
  for(int i = index; i < arr->count; i++){
      arr->elements[i] = arr->elements[i+1];
    }
  --arr->count;

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
