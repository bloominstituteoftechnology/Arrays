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
    arr->capacity = capacity;  //dont need malloc these bc not dynamically adding these
    arr->count = 0;

    // Allocate memory for elements
    //we can malloc dynamically for newly added elements
    arr->elements = malloc(capacity * sizeof(char *)); //storing pointers not actual chars so need size of pointer
    //want to initialize to null. can use calloc. null until we update it to something.
    //arr->elements = calloc(capacity, sizeof(char *));

    return arr;
  }


/*****
 * Free memory for an array and all of its stored elements
 *****/
  //anytime malloc ALWAYS have to free to prevent memory leaks
  void destroy_array(Array *arr) {
  //need to free up elements that are dynamically created also
  for (int i = 0; i < arr->count; i++)
    {
      free(arr->elements[i]);
    }
  // Free all elements
  free(arr->elements); //once we free this we lose the point so had to loop thru above to free other elements

  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  arr->capacity *= 2;

  // Copy elements into the new storage
  arr->elements = realloc(arr->elements, arr->capacity * sizeof(char *));  //int v char?

  // Free the old elements array (but NOT the strings they point to)
  // Update the elements and capacity to new values

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
  if (index > arr->count) 
  {
    fprintf(stderr, "index can not be greater than count");
  }
  else
  {
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
//  * Append an element to the end of the array
//  *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->capacity <= arr->count) 
  {
    fprintf(stderr, "not enough capacity");
    return;
  }
  else
  {
     // Copy the element and add it to the end of the array
    //arr->elements[arr->capacity] = element; //this passes but is not really correct. it cant be freed bc not allocated. something about immutability of static strings.
    //want to copy so dont get leaks
    //could also use strcpy and strdup(has hidden malloc in it)
    char *new_str = strdup(element);
    arr->elements[arr->count] = new_str;


  // Increment count by 1
    arr->count++;
  }
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
