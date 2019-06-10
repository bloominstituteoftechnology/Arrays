#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  // Allocate memory for the Array struct
  Array *arr = malloc(sizeof(Array));
  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;

  // Allocate memory for elements
  arr->elements = malloc(capacity * sizeof(char *));

  return arr;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{
  // Free all elements
  for (int i = 0; i < arr->count; i++)
  {
    /* code */
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
void resize_array(Array *arr)
{
  int new_capacity = arr->capacity * 2;
  // printf("new_capacity: %d\n", new_capacity);
  // Create a new element storage with double capacity
  char **new_array = malloc(new_capacity * sizeof(char *));
  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    new_array[i] = arr->elements[i];
    // printf("new_array[i]: %s\n", new_array[i]);
  }
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = new_array;
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
char *arr_read(Array *arr, int index)
{
  // Throw an error if the index is greater or equal to than the current count
  // printf("count: %d\n", arr->count);
  // printf("index: %d\n", index);
  // printf("element: %s\n", *(arr->elements));
  // printf("element + index: %s\n", *(arr->elements + index));
  if (arr->count <= index)
  {
    fprintf(stderr, "IndexError: Index out of range\n");
    return NULL;
  }
  // Otherwise, return the element at the given index
  else
  {
    return *(arr->elements + index);
  }
}

/*****
 * Insert an element to the array at the given index
 *
 * Store the VALUE of the given string, not the REFERENCE
 *****/
void arr_insert(Array *arr, char *element, int index)
{
  // Throw an error if the index is greater than the current count
  // printf("count: %d\n", arr->count);
  // printf("capacity: %d\n", arr->capacity);
  // printf("index: %d\n", index);
  if (arr->count < index)
  {
    fprintf(stderr, "IndexError: Index out of range\n");
  }
  else
  {
    // Resize the array if the number of elements is over capacity
    if (arr->count >= arr->capacity)
    {
      // printf("resized\n");
      resize_array(arr);
      // fprintf(stderr, "IndexError: need to resize\n"); // need to resize
      // return;
    }
    // Move every element after the insert index to the right one position

    for (int i = arr->capacity - 1; i >= index; i--)
    {
      if (i > index)
      {
        // printf("i > index");
        // printf("arr->elements[i]: %s\n", arr->elements[i]);
        // printf("arr->elements[i - 1]: %s\n", arr->elements[i - 1]);
        arr->elements[i] = arr->elements[i - 1];
        // printf("after switch ---------------------------------\n");
        // printf("arr->elements[i]: %s\n", arr->elements[i]);
        // printf("arr->elements[i - 1]: %s\n", arr->elements[i - 1]);
        // printf("---------------------------------\n");
      }
      else if (i == index)
      {
        // printf("i == index\n");
        arr->elements[i] = strdup(element);
      }
    }

    // Copy the element (hint: use `strdup()`) and add it to the array

    // Increment count by 1
    arr->count++;
  }
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{
  // printf("got here\n");
  // printf("element: %s\n", element);
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  // printf("arr->capacity: %d\n", arr->capacity);
  // printf("arr->count: %d\n", arr->count);
  if (arr->count >= arr->capacity)
  {
    resize_array(arr);
    // fprintf(stderr, "IndexError: Index out of range\n");
    // return;
  }
  // else
  // {
  char *element_copy = strdup(element);
  arr->elements[arr->count] = element_copy;
  // char **pt;
  // printf("arr->elements: %d\n", arr->elements);
  // pt = arr->elements;
  // printf("pt1: %d\n", pt);
  // pt += arr->count;
  // printf("pt2: %d\n", pt);
  // *pt = element;
  // printf("pt3: %s\n", *pt);
  // }
  // Copy the element and add it to the end of the array

  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{
  printf("arr->capacity: %d\n", arr->capacity);
  printf("arr->count: %d\n", arr->count);
  printf("element: %s\n", element);
  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  // char *element_copy = strdup(element);

  int confirmed_index = 0;
  for (int i = 0; i < arr->count; i++)
  {
    // printf("arr->elements[i]: %s\n", arr->elements[i]);
    if (strcmp(arr->elements[i], element) == 0)
    {
      printf("in if statement\n");
      free(arr->elements[i]);
      confirmed_index = i;
      break;
    }
    printf("after remove ---------------------------------\n");
    printf("i: %d\n", i);
    printf("arr->elements[i]: %s\n", arr->elements[i]);
  }
  printf("confirmed_index: %i\n", confirmed_index);
  printf("---------------------------------\n");

  // Shift over every element after the removed element to the left one position
  for (int i = confirmed_index; i < arr->count; i++)
  {
    if (i < arr->count - 1)
    {
      arr->elements[i] = arr->elements[i + 1];
    }
    else if (i == arr->count - 1)
    {
      arr->elements[i] = NULL;
    }
  }
  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{
  Array *arr = create_array(1);
  arr_insert(arr, "VALUE-1", 0);
  arr_read(arr, 0);
  arr_insert(arr, "VALUE-2", 0);
  printf("arr->capacity: %d\n", arr->capacity);
  printf("arr->count: %d\n", arr->count);
  arr_read(arr, 0);
  arr_read(arr, 1);
  arr_insert(arr, "VALUE-3", 1);
  printf("arr->capacity: %d\n", arr->capacity);
  printf("arr->count: %d\n", arr->count);
  arr_read(arr, 0);
  arr_read(arr, 1);
  arr_read(arr, 2);
  arr_remove(arr, "VALUE-3");
  printf("arr->count: %d\n", arr->count);
  arr_read(arr, 0);
  arr_read(arr, 1);
  arr_read(arr, 2);
  destroy_array(arr);
  return 0;
}
#endif
