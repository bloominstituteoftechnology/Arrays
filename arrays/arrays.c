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

  // Set initial values for capacity and count
  (*arr).capacity = capacity;
  (*arr).count = 0;

  // Allocate memory for elements
  (*arr).elements = malloc(capacity * sizeof(char *));

  return arr;

}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  free((*arr).elements);

  // Free array
  free(arr);

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity

  //char **new_arr = malloc( 2 * ((*arr).capacity * sizeof(char *)) );

  int new_capacity = 2 * (*arr).capacity;

  //Array *new_arr = create_array(new_capacity);

  char **new_elements = calloc(new_capacity, sizeof(char *));

  // Copy elements into the new storage
  int i;
  for(i = 0; i < (*arr).count; i++) {

    char* new_element = strdup((*arr).elements[i]);

    new_elements[i] = (new_element);

  }


  //(*new_arr).elements = (*arr).elements;

  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);

  // Update the elements and capacity to new values
  (*arr).elements = new_elements;
  (*arr).capacity = new_capacity;

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
  if(index > (*arr).count) {
    return NULL;
  }

  // Otherwise, return the element at the given index
  int i = 0;

  while((*arr).elements[i] != (*arr).elements[index]) {
    i++;
  }

  return ((*arr).elements[i]);

}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  /*
  if(index > (*arr).count) {
    fprintf(stderr, "Index out of range.");
  }
  */

  // Resize the array if the number of elements is over capacity
  if( ((*arr).count + 1) > (*arr).capacity ) {

    resize_array(arr);

  }

  // Move every element after the insert index to the right one position
  /*
  int i = index;
  while((*arr).elements[i] != '\0') {

    (*arr).elements[i+1] = (*arr).elements[i];

  }
  */

  for(int i = (*arr).count; i > index; i--) {

    (*arr).elements[i] = (*arr).elements[i-1];

  }


  // Copy the element and add it to the array
  char* new_element = strdup(element);

  (*arr).elements[index] = new_element;

  // Increment count by 1
  (*arr).count++;

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if( ((*arr).count + 1) > (*arr).capacity ) {

    resize_array(arr);

  }


  // Copy the element and add it to the end of the array
  int i = 0;
  while((*arr).elements[i] != NULL) {

    i++;

  }

  char* new_element = strdup(element);

  (*arr).elements[i] = new_element;

  // Increment count by 1
  (*arr).count++;
  
  //arr_insert(arr, element, (*arr).count);

}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  int i = 0;
  while(strcmp((*arr).elements[i], element) != 0) {
    
    i++;
  }


  // Don't forget to free its memory!

  free(arr->elements[i]);

  //(*arr).elements[i] = NULL;

  // Shift over every element after the removed element to the left one position
  for(; i < (*arr).count; i++) {

    (*arr).elements[i] = (*arr).elements[i+1];

  }

/*
  while((*arr).elements[i] != NULL) {

    (*arr).elements[i] = (*arr).elements[i+1];

  }
  */
  



  // Decrement count by 1
  (*arr).count--;

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
