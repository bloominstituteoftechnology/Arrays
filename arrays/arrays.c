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
  Array *arr = malloc(sizeof(Array));
  arr->capacity = capacity;
  arr->count = 0;
  arr->elements = malloc(capacity * sizeof(char *)); // or sizeof int or size 
  return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  // Free array
  // for (int i = 0; i < arr->count; i++) {
  //     free(arr->elements[i]);
  // } 
  // free(arr->elements[0]);
  free(arr->elements);
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  // Copy elements into the new storage
  // Free the old elements array (but NOT the strings they point to)
  // Update the elements and capacity to new values
  
  int doubled = 2 * arr->capacity;
  char **new_storage = malloc(doubled * sizeof(char*));
  for (int i = 0; i < arr->count; i++) {
    new_storage[i] = arr->elements[i];
  }
  // free(arr->elements);
  arr->capacity = doubled;
  arr->elements = new_storage;
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

  if (index > arr->count) {
    fprintf(stderr, "Arr-Read IndexError: Index %d out of range\n", index);
    exit(1);
    // return NULL;
  }
    return arr->elements[index];
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
  if (index > arr->count) {
    fprintf(stderr, "Arr_Insert IndexError: Index %d out of range\n", index);
    exit(1);
  }

  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }

  
  for (int i = arr->count - 1; i >= index; i--) {
    arr->elements[i + 1] = arr->elements[i];
  }
  arr->elements[index] = element;
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  // Copy the element and add it to the end of the array
  // Increment count by 1
  if(! (arr->count < arr->capacity)) {
    printf("ERROR");
    return;
  }

  if (arr->capacity <= arr->count) {
    resize_array(arr);
  }
  char *copy = strdup(element); 
  arr->elements[arr->count] = copy;
  arr->count++;
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


int pos = -1;
  for (int i = 0; i < arr->count; i++) {
    if (element == arr->elements[i]) {
      pos = i;
      arr->elements[pos] = NULL;
      break;
    }
  }
  for (int j = pos; j < arr->count - 1; j++) {
    arr->elements[j] = arr->elements[j+1]; 
  }
  arr->elements[arr->count-1] = NULL;
  // free(arr->elements[arr->count-1]);
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
  // printf("(%d/%d)", arr->count, arr->capacity);
  // printf("(%p)", (void*) &arr->elements);
  printf("]\n");
}


#ifndef TESTING
int main(void)
{
  printf("*********\n");
  Array *arr = create_array(1); // []
  
  arr_print(arr);
  resize_array(arr);  // []
  arr_print(arr);
  arr_insert(arr, "STRING1", 0); // [STRING1]
  // printf("(%s)\n", arr_read(arr, 0));
  arr_print(arr);
  arr_append(arr, "STRING4"); // [STRING1,STRING4]
  arr_print(arr);
  arr_insert(arr, "STRING2", 0); // [STRING2,STRING1,STRING4]
  arr_print(arr);
  arr_insert(arr, "STRING3", 1); // [STRING2,STRING3,STRING1,STRING4]
  arr_print(arr);
  arr_remove(arr, "STRING3"); // [STRING2,STRING1,STRING4]
  // printf("(%s)\n", arr_read(arr, 0));
  // printf("(%s)\n", arr_read(arr, 1));
  // printf("(%s)\n", arr_read(arr, 2));
  arr_print(arr);

  

  destroy_array(arr);
  // arr_print(arr);

  return 0;
}
#endif


// typedef struct llist {
//   char **elements;
//   int capacity;
//   int count;
//   struct llist *next_head;
// } Array;

// /*****
//  * Allocate memory for a new array
//  *****/
// Array *create_array (int capacity) {
//   // Allocate memory for the Array struct
//   // Set initial values for capacity and count
//   // Allocate memory for elements
//   Array* arr = malloc(sizeof(Array));
//   arr->capacity = capacity;
//   arr->count = 0;
//   arr->elements = malloc(capacity * sizeof(char*));
//   arr->next_head = malloc(sizeof(struct llist));
  
//   return arr;
// }

// void destroy_array(Array *head) {
//   // Free all elements
//   // Free array
//   while(head != NULL) {
//     struct llist * next_head = head->next_head; 
//     free(head);
//     head = next_head;
//   }
//   // free(head->elements);
//   // free(head);
// }

// void resize_array(Array *head) {

//   // Create a new element storage with double capacity
//   // Copy elements into the new storage
//   // Free the old elements array (but NOT the strings they point to)
//   // Update the elements and capacity to new values
  
//   int doubled = 2 * head->capacity;
//   char **new_storage = malloc(doubled * sizeof(char*));
//   // for (int i = 0; i < head->count; i++) {
//   new_storage = head->elements;
//   // }
//   free(head->elements);
//   head->capacity = doubled;
//   head->elements = new_storage;
// }

// /*****
//  * Return the element in the array at the given index.
//  *
//  * Throw an error if the index is out of range.
//  *****/
// char *arr_read(Array *head, int index) {

//   // Throw an error if the index is greater than the current count
//   // Otherwise, return the element at the given index

//   if (index >= head->count) {
//     fprintf(stderr, "IndexError: Index %d out of range\n", index);
//     // exit(1);
//     return NULL;
//   }
//     return head->elements[index];
// }

// /*****
//  * Insert an element to the array at the given index
//  *****/
// void arr_insert(Array *head, char *element, int index) {

//   // Throw an error if the index is greater than the current count
//   // Resize the array if the number of elements is over capacity
//   // Move every element after the insert index to the right one position
//   // Copy the element and add it to the array
//   // Increment count by 1
//   if (index > head->count) {
//     fprintf(stderr, "IndexError: Index %d out of range\n", index);
//     exit(1);
//   }

//   if (head->capacity <= head->count) {
//     resize_array(head);
//   }

//   if (index == 0) {
//     *head->elements = element;
//     if (head->count == 0) {
//       head->next_head = NULL;
//     } else {
//       *head->next_head = *head;
//     }
    
//     // *head->elements = element;
//   } else {
//     Array * curr_node = head;
//     while(curr_node->next_head != NULL) {
//       curr_node = curr_node->next_head;
//     }
//     curr_node->next_head = NULL;
//     // curr_node->elements = &element;
//     *curr_node->elements = element;

//   }
//   head->count++;
// }
// void arr_append(Array *head, char *element) {
//   // Resize the array if the number of elements is over capacity
//   // or throw an error if resize isn't implemented yet.
//   // Copy the element and add it to the end of the array
//   // Increment count by 1
//   if (head->capacity <= head->count) {
//     resize_array(head);
//   }
//   if (head->next_head == NULL) {
//     *head->next_head = &element;
//   }
//   Array * curr_node = head;
//   while(curr_node != NULL) {
//     // printf("%p", curr_node);
//     struct llist * next_head = curr_node->next_head;
//     curr_node = next_head;
//   }
//   *curr_node->elements = element;
//   curr_node->next_head = NULL;
//   head->count++;
// }

// /*****
//  * Remove the first occurence of the given element from the array,
//  * then shift every element after that occurence to the left one slot.
//  *
//  * Throw an error if the value is not found.
//  *****/
// void arr_remove(Array *head, char *element) {

//   // Search for the first occurence of the element and remove it.
//   // Don't forget to free its memory!
//   // Shift over every element after the removed element to the left one position
//   // Decrement count by 1
  
//   if (head->next_head == NULL) {    // if there is only 1 item in the list
//     free(head);

//   } else if (head->elements == &element) { // if element is head of the list
//     Array * first_head = head;
//     first_head = first_head->next_head;
//     free(first_head->next_head);
//     first_head->next_head = NULL;
//     // head->elements = head->next_head;
//     // head->next_head = *head->elements->next_head;

//   } else {            // element is not head & there is > 1 item in the list
//     Array * curr_node = head;
//     while(curr_node->elements != &element) {
//       curr_node = curr_node->next_head;
//     }
//     free(curr_node->next_head);
//     curr_node->next_head = NULL;
//   }
//   head->count--;
// }

// void arr_print(Array *head) {
//   printf("[");
//   for (int i = 0 ; i < head->count ; i++) {
//     printf("%s", head->elements[i]);
//     printf("%s", (void*)head->next_head);
//     if (i != head->count - 1) {
//       printf(",");
//     }
//   }
//   printf("(%d/%d)", head->count, head->capacity);
//   printf("(%p, %p)", (void*) &head->elements, head->next_head);
//   printf("]\n");
// }



// // void llist_insert(llist *next_val) {

// // }


// #ifndef TESTING
// int main(void)
// {
//   printf("*********\n");
//   Array *arr = create_array(1); // []
//   arr_print(arr);
//   // resize_array(arr);  // []
//   // arr_print(arr);
//   arr_insert(arr, "STRING1", 0); // [STRING1]
//   arr_print(arr);
//   resize_array(arr);  // []
//   arr_print(arr);
//   arr_append(arr, "STRING4"); // [STRING1,STRING4]
//   arr_print(arr);
//   // arr_insert(arr, "STRING2", 0); // [STRING2,STRING1,STRING4]
//   // arr_print(arr);
//   // arr_insert(arr, "STRING3", 1); // [STRING2,STRING3,STRING1,STRING4]
//   // arr_print(arr);
//   // arr_remove(arr, "STRING3"); // [STRING2,STRING1,STRING4]
//   // arr_print(arr);

//   destroy_array(arr);
//   // arr_print(arr);

//   return 0;
// }






// #endif
