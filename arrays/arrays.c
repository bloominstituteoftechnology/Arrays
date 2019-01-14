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
  arr->capacity = capacity; 
  arr->count = 0;
  // Allocate memory for elements
  arr->elements = calloc(capacity,sizeof(char *)); //Why char * not char?
  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  for(int i =0; i<arr->count; i++) {
    free(arr->elements[i]);
  };
  // Free array
free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
// void resize_array(Array *arr) {

//   // Create a new element storage with double capacity
//   Array *newarr = calloc(capacity, sizeof(Array)*2);
//   int capacity = arr->capacity;
//   newarr->elements =  malloc((capacity*sizeof(char))*2); 

//   // Copy elements into the new storage 
//   for(int i=0; i<arr->count; i++){
//     newarr[i] = arr->elements[i];
//   }

//   // Free the old elements array (but NOT the strings they point to)
// free(arr->elements);

//   // Update the elements and capacity to new values
// newarr->elements = sizeof(newarr)/sizeof(char);
// newarr->capacity = capacity*2;
 
// }



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
if(index > arr->count){
   exit(1);
} else { 
  return arr->elements[index];
  } 
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

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
    if((arr->count+1) > arr->capacity){
      int newsize = arr->count+1;
      malloc(newsize*sizeof(char *));
    }
  // Copy the element and add it to the end of the array
   
    arr->elements[arr->count] = element;
  // Increment count by 1
  arr->count = arr->count+1;


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
