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
  

  // Set initial values for capacity and count

  // Allocate memory for elements
  Array *arrayPtr = (Array*) malloc(sizeof(Array));
  arrayPtr->capacity = capacity;
  arrayPtr->count = 0;

  arrayPtr->elements = malloc(capacity*sizeof(char*));
  return arrayPtr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  for(int i = 0; i< arr->count;i++){
    free(arr->elements[i]);
  }
  free(arr->elements);
  free(arr);

  arr = NULL;

  // Free array

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Copy elements into the new storage
  char **resized = malloc(arr->capacity*2*sizeof(char*));
  for(int i = 0; i< arr->count; i++){
    resized[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = resized;
  arr->capacity = arr->capacity*2;
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
  if (index >= arr->count){
    fprintf(stderr, "IndexError: index out of bounds");
    return NULL;
  }
  // Otherwise, return the element at the given index
  return arr->elements[index]; 
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if(index >= arr->count){
    fprintf(stderr, "IndexError: index out of bounds");
    return;
  }
  // Resize the array if the number of elements is over capacity
  if(arr->count >= arr->capacity){
    resize_array(arr);
  }
  
  // Move every element after the insert index to the right one position
  for(int i = arr->count; i>index; i--){
    arr->elements[i] = arr->elements[i-1];
  }
  // Copy the element and add it to the array
  char *copy = strdup(element);
  arr->elements[index] = copy;
  // Increment count by 1
  arr->count = arr->count + 1;

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count + 1 > arr->capacity){
    resize_array(arr);
    return;
  } 
  // Copy the element and add it to the end of the array
  char *copy = strdup(element);
  *(arr->elements+arr->count) = copy;
  
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
  int index = -1;

  for (int i = 0; i<arr->count; i++){
    if(strcmp(arr->elements[i],element) == 0){
      arr->elements[i] = NULL;
      index = i;
      break;    
    }   
  }
  if (index < 0) {
    fprintf(stderr, "Value not found");
    return;
  }
  // Shift over every element after the removed element to the left one position
  for(int i = index; i<arr->count-1; i++){
    arr->elements[i] = arr->elements[i+1];
  }
  arr->elements[arr->count-1] = NULL;
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

  Array *arr = create_array(3);
  arr_append(arr,"STRING1");
  arr_append(arr,"STRING2");
  arr_append(arr,"STRING3");
  arr_append(arr,"STRING4");
  arr_append(arr,"STRING5");
  arr_insert(arr, "BANG!", 0);
  arr_remove(arr,"STRING3");
  // arr_insert(arr, "STRING3", 1);
  // arr_print(arr);
  // arr_remove(arr, "STRING3");
  // arr_print(arr);
  for(int i = 0; i< arr->count; i++){
    printf("ELEMENT: %s\n", arr->elements[i]);
  }
  printf("Capacity:%d\n", arr->capacity);
  destroy_array(arr);

  return 0;
}
#endif
