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
  Array *array = malloc(sizeof(Array));

  // Set initial values for capacity and count
  array->capacity = capacity;
  array->count = 0;

  // Allocate memory for elements
  array->elements = malloc(capacity * sizeof(char *));
  
  return array;

}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  for (int i = 0; i < arr->count; i++) {
    // Free pointers inside the array
    free(arr->elements[i]);
  }

  // Free the array
  free(arr->elements);

  // Free the struct Array
  free(arr);

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  arr->capacity *= 2;
  
  // Realloc will do the next 4 steps for us!
//  arr->elements = realloc(elements, arr->capacity * sizeof(char *));   
  
  char **elements = malloc(arr->capacity * sizeof(char *));

  // Copy elements into the new storage
//  for (int index = 0; index < arr->count; index++) {
//    elements[index] = arr->elements[index];
//  }
  memcpy(elements, arr->elements, arr->count*sizeof(char *));

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);

  // Update the elements and capacity to new values
  arr->elements = elements;

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
  if (index >= arr->count) {
    perror("Error getting value at index:");
  } else {
    // Otherwise, return the element at the given index
    return arr->elements[index];
  }
  return NULL;
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    perror("Error getting value at index:");
  }

  // Resize the array if the number of elements is over capacity
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  // Shifting over to the right by 1 gets complicated if we use a temp variable to hold on to the next element so it doesn't get erase while we move the previous element over, which is in another temp variable
//  char *elementToInsert = element;
//  for (int i = index; i < arr->count; i++) {
//    char *nextElement = arr->elements[i+1];
//    arr->elements[i+1] = arr->elements[i];
//    arr->elements[i] = elementToInsert;
//    elementToInsert = nextElement;
//  }  // ==> doesn't work!, refer to notes
  
  // Shifting backwards up until the index
  for (int i = arr->count; i > index; i--) {
    arr->elements[i] = arr->elements[i-1];
  }
  
  // We are given a pointer to a string and we need to copy its contents. First we allocate memory for that new copy, then copy the contents over
  int stringLength = strlen(element);
  char *newElement = malloc((stringLength+1) * sizeof(char));
  strcpy(newElement, element);
  
  // Finally we save the reference to our new copy in the array
  arr->elements[index] = newElement;

  // Increment count by 1
  arr->count += 1;

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  
  arr_insert(arr, element, arr->count); // Inserting at position "count", which is at the end of the array

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
  for (int i = 0; i < arr->count; i++) {
    if (strcmp(arr->elements[i], element) == 0) {
      // Don't forget to free its memory!
      free(arr->elements[i]);
      
      // Shift over every element after the removed element to the left one position
      for (int j = i; j < arr->count-1; j++) {
        arr->elements[j] = arr->elements[j+1];
      }
      
      // Decrement count by 1
      arr->count -= 1;
      break;
    }
  }
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
