#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

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
  arr->elements = malloc(capacity * sizeof(char *));

  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  for (int i = 0; i < arr->count; i++) {
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
  int capacity = arr->capacity;
  // Create a new element storage with double capacity
  char **elems = malloc((capacity * 2) * sizeof(char *));

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++) {
    elems[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);

  // Update the elements and capacity to new values
  arr->elements = elems;
  arr->capacity = capacity * 2;

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
  if (index > arr->count) {
    switch(errno) {
      default:
        fprintf(stderr, "Reading index of array -> Error: Index is out of bounds \n");
    }

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
    switch(errno) {
      default:
        fprintf(stderr, "Inserting into array -> Error: Index is out of bounds \n");
    }

    exit(1);
  }

  // Resize the array if the number of elements is over capacity
  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }

  for (int i = arr->count; i > index; i--) {
    arr->elements[i] = arr->elements[i-1];
  }

  // Copy the element and add it to the array
  char *elem = strdup(element); // Also adding this line here and adding that to the arr->elements[index] causes a segmentation fault
  arr->elements[index] = elem;

  // Increment count by 1
  arr->count++;

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
  char *elem = strdup(element);
  arr->elements[arr->count] = elem;


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
  int index = 0;
  int found = -1;

  // Loop through the elements in the array
  for (int i = 0; i < arr->count; i++) {
    // Use string copy so we can check if the two elements match
    int res = strcmp(arr->elements[i], element);
    if (res == 0) {

      // arr->elements[i] = NULL;
      // Free the element
      free(arr->elements[i]);

      // Set index and set found
      index = i;
      found = 1;
      break;
    }
  }

  // Check if element was found, if not, return error
  if (found  != -1) {
    // Shift each element at the index to the left
    for (int i = index; i < arr->count; i++) {
      arr->elements[i] = arr->elements[i + 1];
    }

    // Decrement the count
    arr->count--;
  } else {
    fprintf(stderr, "Removing element from array -> Error: Index was not found \n");
    return;
  }
}

/*****
 * Remove the first element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the array is empty
 *****/
void arr_pop(Array *arr) {
  if (arr->count == 0) {
    fprintf(stderr, "Index out of range");
  }
  free(arr->elements[0]);

  for (int i = 0; i < arr->count; i++) {
    arr->elements[i] = arr->elements[i + 1];
  }

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
  arr_append(arr, "STRING4");
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_append(arr, "STRING6");
  arr_print(arr);
  arr_remove(arr, "STRING4");
  arr_print(arr);
  arr_remove(arr, "STRING4");
  arr_print(arr);
  arr_pop(arr);
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
