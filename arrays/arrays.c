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
  if (!arr) {
    fprintf(stderr, "Error: Memory allocation failed for array.\n");
    exit(1);  // Exit program if malloc fails
  }

  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;

  // Allocate memory for elements
  arr->elements = malloc(capacity * sizeof(char *));
  if (!arr->elements) {
    fprintf(stderr, "Error: Memory allocation failed for elements.\n");
    exit(1);  // Exit if memory for elements cannot be allocated
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
  // Free array elements
  free(arr->elements);

  // Free array structure
  free(arr);
}


/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {
  int new_capacity = arr->capacity * 2;
  char **new_elements = realloc(arr->elements, new_capacity * sizeof(char *));
  if (!new_elements) {
    fprintf(stderr, "Error: Memory reallocation failed.\n");
    exit(1);
  }

  // Update elements and capacity
  arr->elements = new_elements;
  arr->capacity = new_capacity;
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
  // Throw an error if the index is out of range
  if (index < 0 || index >= arr->count) {
    fprintf(stderr, "Error: Index %d out of range.\n", index);
    return NULL;  // Return NULL if index is invalid
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
  // Throw an error if the index is out of range
  if (index < 0 || index > arr->count) {
    fprintf(stderr, "Error: Index %d out of range for insertion.\n", index);
    return;
  }

  // Resize the array if the number of elements is over capacity
  if (arr->count == arr->capacity) {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i = arr->count; i > index; i--) {
    arr->elements[i] = arr->elements[i - 1];
  }

  // Copy the element (using `strdup()`) and add it to the array
  arr->elements[index] = strdup(element);
  if (!arr->elements[index]) {
    fprintf(stderr, "Error: Memory allocation failed for element.\n");
    exit(1);
  }

  // Increment count by 1
  arr->count++;
}


/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  // Resize the array if the number of elements is over capacity
  if (arr->count == arr->capacity) {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);
  if (!arr->elements[arr->count]) {
    fprintf(stderr, "Error: Memory allocation failed for element.\n");
    exit(1);
  }

  // Increment count by 1
  arr->count++;
}


/*****
 * Remove the first occurrence of the given element from the array,
 * then shift every element after that occurrence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {
  int found = 0;  // Flag to check if the element is found
  for (int i = 0; i < arr->count; i++) {
    if (strcmp(arr->elements[i], element) == 0) {
      found = 1;
      free(arr->elements[i]);

      // Shift elements to the left
      for (int j = i; j < arr->count - 1; j++) {
        arr->elements[j] = arr->elements[j + 1];
      }

      arr->count--;
      break;
    }
  }

  if (!found) {
    fprintf(stderr, "Error: Element '%s' not found.\n", element);
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
      printf(", ");
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