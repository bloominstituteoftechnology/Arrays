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
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}

Array *create_array (int capacity) {
  // Allocate memory for the Array struct
  // Set initial values for capacity and count
  // Allocate memory for elements
  Array *arr = malloc(sizeof(Array));
  arr->capacity = capacity;
  arr->count = 0;
  arr->elements = calloc(capacity, sizeof(char *));

  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {
  // Free all elements
  // Free array
  for (int i = 0; i < arr->count; i++)
  {
    if (arr->elements[i] != NULL) free(arr->elements[i]);
  }
    if (arr->elements != NULL) free(arr->elements); 
    if (arr != NULL) free(arr);
}

// ["hello"]
// ["h","e","l","l","o"]
// 

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {
  // Create a new element storage with double capacity
  // Copy elements into the new storage
  // Free the old elements array (but NOT the strings they point to)
  // Update the elements and capacity to new values.
  int new_size = 2 * arr->capacity;
  char **new_elements = calloc(new_size, sizeof(char *));
  // strdup = string duplicate 
  for (int i = 0; i < arr->capacity; i++) new_elements[i] = strdup (arr->elements[i]);

  if (arr->elements != NULL) free(arr->elements);

  arr->elements = new_elements;
  arr->capacity = new_size;
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
  // Otherwise, return the element at the given index

    if (index >= arr->count)
  {
    fprintf(stderr, "index out of range\n");
    exit(1);
  }

  return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {
  // Throw an error if the index is greater than the current count
  // Resize the array if the number of elements is over capacity
  // Move every element after the insert index to the right one position
  // Copy the element and add it to the array
  // Increment count by 1

  if (index > arr->count)
  {
    fprintf(stderr, "index out of range\n");
    exit(1);
  }
  if (arr->count >= arr->capacity)
  {
    resize_array(arr);
  }
  for (int i = arr->count - 1; i >= index; i--)
  {
    arr->elements[i + 1] = arr->elements[i];
  }
  char *new_element = strdup(element);
  arr->elements[index] = new_element;
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  // Copy the element and add it to the end of the array
  // Increment count by 1
  if (arr->count >= arr->capacity)
  {
    resize_array(arr);
  }
  char *new_element = strdup(element);
  arr->elements[arr->count] = new_element;
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/

// do this later

void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  // Shift over every element after the removed element to the left one position
  // Decrement count by 1
  int i = 0;
  // this is a flag to find the intrest of elements.
  int found = -1; 


  while (i < arr->count && found == -1)
  {
    if(strcmp(arr = arr->elements[i])) {
    }
    arr->elements[i -  1] = arr->elements[i];
    if (arr->elements != NULL) free(arr->elements);
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
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  // dont forget this
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
