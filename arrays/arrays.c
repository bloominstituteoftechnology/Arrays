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

  // Set initial values for capacity and count

  // Allocate memory for elements
  Array * array = malloc(sizeof(Array));

  array->capacity = capacity; 
  array->count = 0;
  array->elements = calloc(capacity, sizeof(char));  // equilavanet to  sizeof(char) * capacity  
  //difference between calloc and malloc is that calloc will set the memory to zero

}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  for(int i = 0; i < arr->count; i++){
    free(arr->elements[i]);
  }

  free(arr->elements);
  free(arr);

  // Free array

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  int new_capacity = arr->capacity * 2;
  // Create a new element storage with double capacity
  char **new_elements = calloc(new_capacity, sizeof(char *));

  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++){
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
  if (index > arr->count)
  {
    printf(stderr, "Index out of range");
  }


  // Otherwise, return the element at the given index
  return arr->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count){
    fprintf(stderr, "Index %d out of range", index);
  }
  // Resize the array if the number of elements is over capacity
  if (arr->capacity <= arr->count){
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = arr->count; i > index; i--){
    arr->elements[i] = arr->elements[i-1];
  }
  // Copy the element and add it to the array
  char * new_element = strdup(element);
  arr->elements[index] = new_element;
  arr->count++; 
  // Increment count by 1


}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.

  /*This should keep us from going out of bounds out of allocated memory*/
  // if (arr->capacity <= arr->count)
  // {
  //   fprintf(stderr, "IndexError: Index is out of range");
  //   return;
  // }
  // // Copy the element and add it to the end of the array
  // char *new_element = strdup(element);
  // //strudup is malloc and strcpy combined together  
  // //allocates memory for the size of the string and then copys the string

  // arr->elements[arr->count] = new_element;
  // // Increment count by 1
  // arr->count += 1; 

  // //arr->count++;  but not every language I know has ++ they all have += 
  // //So I try to stay in the habit. 
  arr_insert(arr, element, arr->count);

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
  int removed = 0; 
  for (int i = 0; i < arr->count; i++)
  {
    if (removed){
      arr->elements[i-1] = arr->elements[i];
    } else if (strcmp(arr->elements[i], element) == 0)
    {
      free(arr->elements[i]);
      removed = 1; 
      arr->count -= 1;
    }
  }
  if (removed){
    arr->elements[arr->count] = NULL;
  } else {
    fprintf(stderr, "Value %s not found", element);
  }

}

char *pop(Array *arr){
  // stretch goal


  //Grab the last element 
  char * popped = arr->elements[arr->count-1];
  free(arr->elements[arr->count-1]);
  arr->elements[arr->count-1] = NULL;
  arr->count--; 

  //return the last element 
  return popped;
}

void reverse(Array *arr)
{
  char **new_elements = calloc(arr->capacity, sizeof(char *));

  int j = 0; // for the reverse 
  for( int i = arr->count - 1; i >= 0; i--)
  {
    new_elements[j] = arr->elements[i];
    free(arr->elements[i]);
  }

  free(arr->elements);

  arr->elements = new_elements; 
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
  arr_append(arr, "STRING1");
  arr_append(arr, "STRING2");
  arr_append(arr, "STRING3");
  arr_append(arr, "STRING4");
  printf("\n %d %d\n", arr->capacity, arr->count);
  arr_print(arr);
  destroy_array(arr);
  // arr_insert(arr, "STRING1", 0);
  // arr_append(arr, "STRING4");
  // arr_insert(arr, "STRING2", 0);
  // arr_insert(arr, "STRING3", 1);
  // arr_print(arr);
  // arr_remove(arr, "STRING3");
  // arr_print(arr);

  // destroy_array(arr);

  return 0;
}
#endif
