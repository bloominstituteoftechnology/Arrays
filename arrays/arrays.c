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
  Array  *array = malloc(sizeof(Array));
  // Set initial values for capacity and count
  array->capacity = capacity;
  array->count = 0;
 
  // Allocate memory for elements
  array->elements = malloc(capacity * sizeof(char *));
  arr_print(array);
  
  return array;
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
  arr->capacity *= 2;
  arr->elements = realloc(arr->elements, arr->capacity * sizeof(char *));
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
  if(index >  arr->capacity -1) {
    fprintf(stderr, "Index greater than the current count");
    exit(1);
  }
  
  return arr->elements[index];

  // Throw an error if the index is greater than the current count

  // Otherwise, return the element at the given index
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if(index > arr->count) {
    fprintf(stderr, "Index greater than current count");
  }
  // Resize the array if the number of elements is over capacity
  if(arr->count > arr->capacity-1) {
    resize_array(arr);
  }

  fprintf(stderr, "Element %s\n", element);
  // Move every element after the insert index to the right one position
  
  if(arr->count == 0) {
    arr->elements[0] = element;
    
  } else {
    char *temp = arr->elements[index];
    char *temp2;
    for(int i = index; i <= arr->count; i++) {
      temp2 = arr->elements[i+1];
      arr->elements[i+1] = temp;
      temp = temp2;
    
    }
  }
  
  
  
  // Copy the element and add it to the array
  arr->elements[index] = element;
  fprintf(stderr, "testing 0%s ", arr->elements[0]);
  fprintf(stderr, "testing 1%s ]\n", arr->elements[1]);
  arr->count += 1;
  // Increment count by 1

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
  
  // Resize the array if the number of elements is over capacity
  if(arr->count > arr->capacity - 1) {
    resize_array(arr);
  }
  // or throw an error if resize isn't implemented yet.

  // Copy the element and add it to the end of the array
  
  arr->elements[arr->count++] = element;
  for(int i  = 0; i < arr->capacity-1; i++) {
    fprintf(stderr, "%s\n", arr->elements[i]);
  }
  // Increment count by 1

}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {
  int index;
  
  
  for(int i = 0; i < arr->count; i++) {
    if(strcmp(arr->elements[i], element) == 0) {
      index = i;
     
      break;

    }
  }
   
  fprintf(stderr, "%s", arr->elements[0]);
  fprintf(stderr, "%s", arr->elements[1]);
  fprintf(stderr, "%s\n", arr->elements[2]);
  fprintf(stderr, "%i\n", arr->count);
  arr->count -= 1;
  for(int j = index; j < arr->count; j++) {
    
    arr->elements[j] = arr->elements[j+1];
    
  }
  fprintf(stderr, "%s", arr->elements[0]);
  fprintf(stderr, "%s", arr->elements[1]);
  fprintf(stderr, "%s\n", arr->elements[2]);
  fprintf(stderr, "%i\n", arr->count);
  arr->elements[arr->count] = NULL;
  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!

  // Shift over every element after the removed element to the left one position

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
