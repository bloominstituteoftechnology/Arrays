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
 * DAY 2
    2. `arr_remove()`

 ************************************/

/*****
 * DAY 1 ------------------------------
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
  
  // Allocate memory for the Array struct
  Array *new_array = malloc(sizeof(Array));

  // Set initial values for capacity and count
  new_array->capacity = capacity; //passed in parameter 
  new_array->count = 0;

  // Allocate memory for elements 
  // The calloc() function takes two arguments: the number of elements to allocate and the storage size of those elements
  new_array->elements = calloc(capacity, sizeof(int));
  

  return new_array;

}


/*****
 * DAY 1 ------------------------------
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  free(arr->elements); 
  
  // Free array
  free(arr); 

}

/*****
 * DAY 2 ------------------------------
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  char **double_capacity = calloc((arr->capacity * 2), sizeof(char *)); //** = a pointer to a pointer

  // Copy elements into the new storage
  for (int i=0; i< arr->count; i++) 
  {
    double_capacity[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  if (arr->elements != NULL) 
  {
    free(arr->elements);
  }

  // Update the elements and capacity to new values
  arr->elements = double_capacity; 
  arr->capacity *= 2; //*= multiplication syntax 

}



/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/***** DAY 1 ------------------------------
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    fprintf(stderr, "index out of range");
    exit(1);
  }

  // Otherwise, return the element at the given index
  return arr->elements[index];

  
}


/*****
 * DAY 2 ------------------------------
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    fprintf(stderr, "index out of range");
    exit(1);
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count > arr->capacity) {
    resize_array(arr); 
  } 

  // Move every element after the insert index to the right one position
  for (int i=arr->count; i > index; i--) {
    arr->elements[i+1] = arr->elements[i]; //shift the array values from the end to make space for the new element
  }

  // Copy the element and add it to the array
  char *new_element = element; // copy 
  arr->elements[index] = new_element; //add

  // Increment count by 1
  arr->count++;
  

}

/***** DAY 1 ------------------------------
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements(count) is over capacity
  if (arr->count > arr->capacity) {
    resize_array(arr); 
  } 
  // or throw an error if resize isn't implemented yet.
  if (arr->count > arr->capacity) {
    fprintf(stderr, "number of elements is over capacity");
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = element; //the element at count (which will be empty - zero indexing)will equal element 
  // Increment count by 1
  arr->count++;

}

/*****
 * DAY 2 ------------------------------
 * Remove the first occurrence of the given element from the array,
 * then shift every element after that occurrence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurrence of the element and remove it.

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
