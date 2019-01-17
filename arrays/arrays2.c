#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

typedef struct Array { //typedef struct{}Arrow is the definition of the Arrow type
  int capacity;  // How many elements can this array hold?total size of the underlying array
  int count;  // How many states does the array currently hold?currant size
  char **elements;  // The string elements contained in the array-pointer to the first element
} Array;//now we can use Array without "struct"


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity)
 {

 Array *arr = malloc(sizeof( Array));

  arr->capacity = capacity;
  arr->count = 0;
  arr->elements=malloc(capacity * sizeof(char*));

  return arr;
 }
  // Allocate memory for the Array struct

  // Set initial values for capacity and count


  // Allocate memory for elements




/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  //assert(arr != NULL);
  for(int i = 0; i < arr->count; i++){
    arr->elements[i] =NULL;
    free(arr->elements[i]);

  }
    free(arr->elements);
    free(arr);

  // Free all elements

  // Free array

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  char **arr_storage = calloc((2 * arr-> capacity), sizeof(char*));
  for (int i=0;  i < arr->count; i++)
  {
    arr_storage[i] = arr->elements[i];
  }
   for(int i = 0; i < arr->count; i++){
   arr->elements[i] = NULL;
     free(arr->elements[i]);
   }
  free(arr->elements);
  arr->elements=arr_storage;
  arr->capacity= arr ->capacity * 2;
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
  if (arr->count<index){//(index >=sizeof(arr) || index<0){ //index>=arr->count
    printf("Index is not here");
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
  if (index > arr->count){
    
    printf("Index is not here\n");
    exit(1);
  }
  if (arr->count + 1 > arr->capacity)
  {
    resize_array(arr); //call resize funct above
  }
  // Throw an error if the index is greater than the current count
  // Resize the array if the number of elements is over capacity
  // Move every element after the insert index to the right one position
  for (int i = index; i<arr->count; i++)
  {
    arr->elements[i+1]=arr->elements[i];
  }
  arr->elements[index]= element;

  arr->count++;
}
  // Copy the element and add it to the array

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {
    
    if (arr->count +1 > arr->capacity)
    {
      resize_array(arr); //call func resize from above 
    }

    //char *el_end =strdup(element);//duplicate
    arr->elements[arr->count] = element;

    arr->count++;

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.

  // Copy the element and add it to the end of the array

  // Increment count by 1

}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
 
void arr_remove(Array *arr, char *element) {
  int key=0;
  //while (strcmp(element, arr->elements[key]!=0)
  for(int i= 0; i<arr->count; i++)
  {
    if (arr->elements[i]==element){
      key=i;
      arr->elements[i] = NULL;
      free(arr->elements[i]);
    }
  }
  // for(int i = key; i<arr->count; i++) {
  //   arr->elements[i] = arr->elements[i+1];
  // }
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
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
