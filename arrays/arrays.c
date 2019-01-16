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
    free(arr->elements[i]);
  };
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

  // Create a new element storage with double capacity
  char **storage = malloc((2 * arr->capacity) * sizeof(char *));
  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    storage[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  for (int i = 0; i < arr->count; i++)
  {
    arr->elements[i] = NULL;
    free(arr->elements[i]);
  }

  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = storage;
  arr->capacity = arr->capacity * 2;
}

char *arr_read(Array *arr, int index)
{
  if (arr->capacity <= arr->count)
  {
    return NULL;
  }
  else
  {
    return arr->elements[index];
  }
}

void arr_insert(Array *arr, char *element, int index)
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    printf("Index is too high.");
    return NULL;
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count + 1 > arr->capacity)
  {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for (int i = index; i < arr->count; i++)
  {
    arr->elements[i + 1] = arr->elements[i];
  }
  // Copy the element and add it to the array
  arr->elements[index] = element;
  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{
  if ((sizeof(arr->count)) >= (arr->capacity))
  {
    fprintf(stderr, "Index is out of range");
    resize_array(arr);
  }
  // Copy the element and add it to the end of the array
  char *new_element = strdup(element);

  arr->elements[arr->count] = new_element;
  // Increment count by 1

  arr->count++;
}

void arr_remove(Array *arr, char *element)
{
  int new;

  // Search for the first occurence of the element and remove it.
  for (int i = 0; i < arr->count; i++)
  {
    if (arr->elements[i] == element)
    {
      new = i;
      arr->elements[i] = NULL;
      // Don't forget to free its memory!
      free(arr->elements[i]);
    }
  }

  for (int i = new; i < arr->count; i++)
  {
    arr->elements[i] = arr->elements[i + 1];
  }

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
