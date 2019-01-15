#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  //  How many elements can this array hold?
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
  	arr->elements = calloc(capacity, sizeof(char *));
	
	printf("Creating an Array\n");
	return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
	for(int i=0; i < arr->count; i++){
		arr->elements[i] = NULL;
		free(arr->elements[i]);
	}
  // Free array
  	//free(arr->elements);
  	free(arr);
	printf("Array Destroyed\n");

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

	int capacity = ((arr->capacity) * 2);

  // Create a new element storage with double capacity
        //char **new_elem = calloc(capacity, sizeof(char *));
	
	//Another way of creating new element storage by creating a new Array
	Array *new_arr = create_array (capacity);
  
	// Copy elements into the new storage
        for(int i=0; i< arr->count; i++){
                new_arr->elements[i] = arr->elements[i];    //new_elem[i] = arr->elements[i]
        }

  // Free the old elements array (but NOT the strings they point to)
        /*for(int i=0; i< arr->count; i++){
		arr->elements[i] = NULL;
		free(arr->elements[i]);
	}*/

	free(arr->elements);
	
  // Update the elements and capacity to new values
	arr->capacity = capacity;
	arr->elements = new_arr->elements;    // arr->elements = new_elem;
	
	printf("Resizing an array complete\n");
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
	if(index > arr->count){
		fprintf(stderr, "Error: Index value is greater than the current count");
		exit(1);   //or return NULL; works too
	}
	else{
		printf("Reading a value from array\n");
		return (arr->elements[index]);
	}

  // Otherwise, return the element at the given index
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
	if(index > arr->count){
		fprintf(stderr, "Error: Index value greater than current count");
		exit(1);
	}
  
  // Resize the array if the number of elements is over capacity
	if(arr->count >= arr->capacity){
		resize_array(arr);
	}

  // Move every element after the insert index to the right one position
	for(int i = (arr->count-1); i >= index; i--){
		arr->elements[i+1] = arr->elements[i];
	}	
	
  // Copy the element and add it to the array
  	char *copy_e = element;
	//char *copy_es = strdup(element);
	arr->elements[index] = copy_e;

  // Increment count by 1
  	arr->count+=1;
	

  printf("Inserting value to array \n");

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  	if(arr->count >= arr->capacity){
		resize_array(arr);
	}
  
  // or throw an error if resize isn't implemented yet.
	
  // Copy the element and add it to the end of the array
	//char *copy_e = element; 
	char *copy_element = strdup(element);    //using strdup to make a copy of the element
	arr->elements[arr->count] = copy_element;	

  // Increment count by 1
	arr->count+=1; 

	printf("Appending value to array\n");
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

	int index = 0;
  // Search for the first occurence of the element and remove it.
  	for(int i=0; i< arr->count; i++){
		if(arr->elements[i] == element){
			index = 1;
			arr->elements[i] = NULL;
			free(arr->elements[i]);	
		}
	}
  // Don't forget to free its memory!
	free(arr->elements);
  
  // Shift over every element after the removed element to the left one position
	for(int i = index; i < arr->count; i++){
		arr->elements[i] = arr->elements[i+1];
	}	

  // Decrement count by 1
  	arr->count-=1;
  
	printf("Removing element from array \n");

}

void arr_clear(Array *arr){

	printf("Clearing the array\n");	
	char **new_elements = calloc(arr->capacity, sizeof(char *));

	for(int i=0; i< arr->count; i++){
		arr->elements[i] = NULL;
		free(arr->elements[i]);
	}
	free(arr->elements);

	arr->count = 0;
	arr->elements = new_elements;
}

char *arr_pop(Array *arr){
	
	printf("Poping the last element of the array \n");
	char *last_element = strdup(arr->elements[(arr->count)-1]);

	arr->elements[(arr->count)-1] = NULL;
	free(arr->elements[(arr->count)-1]);
	arr->count-=1;
 	
	return last_element;
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
  printf("Poped element is: %s\n",arr_pop(arr));
  arr_print(arr);
  arr_clear(arr);
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
