#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;

// function prototypes
// Array *create_array (int capacity);
// void resize_array(Array *arr);
// void destroy_array(Array *arr);
// void resize_array(Array *arr);
// char *arr_read(Array *arr, int index);
// void arr_print(Array *arr);

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
  printf("Creating array with size of \"%d\"\n", capacity);
  // Allocate memory for the Array struct
  Array *new_array = malloc(sizeof(Array));

  // Set initial values for capacity and count
  new_array->count = 0;
  new_array->capacity = capacity;

  // Allocate memory for elements
  new_array->elements = calloc(capacity, sizeof(char*));

  return new_array;

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

  // Create a new element storage with double capacity
  int new_capacity = arr->capacity * 2 * sizeof(char*); // in bytes
  printf("resizing arr with cap: %d to: %d\n", arr->capacity, new_capacity);
  char ** new_elements = calloc(arr->capacity * 2, sizeof(char*));

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++) {
    new_elements[i] = arr->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);

  // Update the elements and capacity to new values
  arr->capacity = new_capacity / sizeof(char*); // get real num
  arr->elements = new_elements;
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
    printf("can not access index: %d out side of array %d\n", index, arr->count);
    // Throw Error;
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
  int errnum;
  if (index >= arr->count) {
    printf("can not insert index: %d outside of array %d\n", index, arr->count);
    // Throw Error;
    errnum = errno;
    fprintf(stderr, "Error num:%d \ncan not insert index: %d outside of array %d\n", errnum, index, arr->count);
    perror("Error\n");
    // fprintf(stderr, "Error inserting outside of array capacity %s\n", stderr( errno ));
  }

  // Resize the array if the number of elements is over capacity
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  // starting from the end is eaiser
  for (int i = arr->count; i > index; i--) {
    arr->elements[i] = arr->elements[i-1];
  }
  printf("array with space missing ");
  // Copy the element and add it to the array
  arr->elements[index] = strdup(element);

  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  printf("Adding %s to array\n", element);
  if (arr->count >= arr->capacity) {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  int length = strlen(element)+1;
  char * new_element = malloc(length * sizeof(char));
  // new_element = element;
  for (int i = 0; i < length; i++) {
    new_element[i] = element[i];
  }

  printf("string %s copied\n", element);
  arr->elements[arr->count] = new_element;
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
  printf("attemping to remove %s from array\n", element);
  // Search for the first occurence of the element and remove it.
  char * ele_to_remove;
  int i = 0;
  int found_str = 0;
   for (; i < arr->count; i++) {
     printf("i: %d\n", i);
     if (!strcmp( arr->elements[i], element)) {
       ele_to_remove = arr->elements[i];
       found_str = 1;
       break;
   }
  }
  if (!found_str || i >= arr->count) {
    fprintf(stderr, "Did not find string %s in array\n", element);
    return;
  }
  // Don't forget to free its memory!
  free(ele_to_remove);
  // Shift over every element after the removed element to the left one position
  for (int j = i; j < arr->count; j++) {
    arr->elements[j] = arr->elements[j+1];
  }
  // Decrement count by 1
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
  // arr_append(arr, "STRING5");
  // arr_append(arr, "STRING6");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif