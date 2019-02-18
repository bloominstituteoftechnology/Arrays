#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;

// Note to self after running everything , should have used chars lol

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
  arr->count = 0;// setting to 0 because it contains nothing
  // Allocate memory for elements
  malloc(capacity * sizeof(int));
  return 0;
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
  char **double_capacity = calloc((arr->capacity * 2), sizeof(int));
    // Don't know why I need the ** for this variable but it works so whatever lol
    // Pointer to copy elements in later
  // Copy elements into the new storage
  for(int i = 0; i< arr->count; i++){
    double_capacity[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = double_capacity;   // Sets elements to the new double capacity pointer
  arr->capacity = arr->capacity * 2; //multiplies old capacity by 2
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
    printf("What you doing man!\n That's out of scope\n");
    exit(-1);
  }else{
    return arr->elements[index];
  }
  // Otherwise, return the element at the given index
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if(index > arr->count){
    printf("What you doing man!\n That's out of scope\n");
    exit(-1);
  }
  // Resize the array if the number of elements is over capacity
  else{
    if(arr->count + 1 > arr->capacity){
      resize_array(arr); //checks if count with another element will go over current capacity, if it is call resize
    }
    // Move every element after the insert index to the right one position
    for(int i = 0; i < arr->count; i++){
      arr->elements[i] = arr->elements[i-1];
      // don't know what this will put as a value for the first one;
    }
    // Copy the element and add it to the array
    char *copy = element; //copy
    arr->elements[index] = copy; //changed to index
    // Increment count by 1
    arr->count = arr->count + 1;
  }
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
    if(arr->count + 1 > arr->capacity){
      resize_array(arr); //checks if count with another element will go over current capacity, if it is call resize
    }
  // Copy the element and add it to the end of the array
  char *copy = element;
  arr->elements[arr->count] = copy;
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
  int removed_index = 0;
  for(int i = 0; i < arr->count; i++){
    if(arr->elements[i] == element){
      arr->elements[i] = NULL;
      free(arr->elements[i]);
      removed_index = i;
    }
  }
  for(int i = removed_index; i < arr->count; i++){
    arr->elements[i] = arr->elements[i+1];
  }
  // Shift over every element after the removed element to the left one position
  arr->count = arr->count -1;
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
  printf("RUNNING IN MAIN!!!");
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
