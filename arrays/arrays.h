#ifndef arrays_h
#define arrays_h

typedef struct Array {
  int capacity;
  int count;
  char **elements;
} Array;

Array *create_array (int capacity);

void destroy_array(Array *arr);

char *arr_read(Array *arr, int index);

void arr_append(Array *arr, char *element);

void arr_insert(Array *arr, char *element, int index);

void arr_remove(Array *arr, char *element);

#endif