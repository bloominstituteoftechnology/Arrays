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
  Array *arr = malloc(sizeof(Array));

  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;

  // Allocate memory for elements
  arr->elements = calloc(capacity, sizeof(char *));

  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  for (int i = 0 ; i < arr->count ; i++) {
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

  int new_capacity = arr->capacity * 2;

  // Create a new array with double capacity
  char **new_elements = calloc(new_capacity, sizeof(char *));

  // Copy elements into the new array
  for (int i = 0 ; i < arr->count ; i++) {
    new_elements[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);

  // Update the elements and capacity to new values
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

  // Throw an error if the index is greater than the current count
  if (index >= arr->count) {
    fprintf(stderr, "IndexError: Index %d out of range\n", index);
    return NULL;
  }

  return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    fprintf(stderr, "IndexError: Index %d out of range", index);
    return;
  }

  // Resize the array if the number of elements is over capacity
  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }

  for (int i = arr->count ; i > index ; i--) {
    arr->elements[i] = arr->elements[i - 1];
  }

  // Copy the element and add it to the array
  char *new_element = strdup(element);
  arr->elements[index] = new_element;
  arr->count++;

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Hint: You can do this in one line of code
  // by calling arr_insert()
  arr_insert(arr, element, arr->count);

}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

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
 * Remove the element in the given position and return it.
 * Then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
char *arr_pop(Array *arr, int index) {

  if (index >= arr->count) {
    fprintf(stderr, "IndexError: Pop index %d out of range\n", index);
    return NULL;
  }

  char *return_value = strdup(arr->elements[index]);

  for (int i = index + 1; i < arr->count ; i++) {
    arr->elements[i - 1] = arr->elements[i];
  }

  arr->count--;
  arr->elements[arr->count] = NULL;

  return return_value;
}




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
  arr_print(arr);
  arr_pop(arr, 0);
  arr_print(arr);
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
