#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Array Notes
// list of elements of same type in a sequential (contiguous) memory block
// Can access data in constant time with this equation: 
// memory_address = starting_address + index * data_size

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
  arr->elements = calloc(sizeof(char*), capacity);
  for (int i = 0; i < capacity; i++) {
  arr->elements[i] = NULL;
  }
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
  // Free array
free(arr->elements);
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
    printf("Index out of range!");
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
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
   printf("Index out of range!\n");
   return;
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  int i = (arr->count);

  for (i; i > index; i--) {
    arr->elements[i] = arr->elements[i - 1];
  }
  // Copy the element (hint: use `strdup()`) and add it to the array
  arr->elements[index] = strdup(element);
  // Increment count by 1
  arr->count += 1;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);

  // Increment count by 1
  arr->count += 1;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  // for (int i = 0; i < arr->count; i++) {
  //   if (arr->elements[i] == element) {
  //     free(arr->elements[i]);
  //     for (i; i < (arr->count - 1); i++) {
  //       arr->elements[i] = arr->elements[i + 1];
  //     }
  //     arr->elements[arr->count-1] = NULL;
  //     arr->count -= 1;
  //   }
  // }
  // Don't forget to free its memory!

  // Shift over every element after the removed element to the left one position

  // Decrement count by 1
  


  int removed = 0;
  for (int i = 0 ; i < arr->count ; i++) {
    if (removed) {
      arr->elements[i - 1] = arr->elements[i];
    } else if (strcmp(arr->elements[i], element) == 0) {
      // Free element
      free(arr->elements[i]);
      removed = 1;
    }
  }

  if (removed) {
    arr->count--;
    arr->elements[arr->count] = NULL;
  } else {
    fprintf(stderr, "ValueError: %s not in array", element);
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

  arr_print(arr);
  arr_insert(arr, "STRING1", 0);
  arr_print(arr);
  arr_append(arr, "STRING4");
  arr_print(arr);
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_remove(arr, "STRING1");
  arr_print(arr);
  arr_remove(arr, "STRING4");
  arr_print(arr);
  arr_print(arr);
  destroy_array(arr);
 
  printf("Array capacity: %d, array count: %d\n", arr->capacity, arr->count);


  return 0;
}
#endif