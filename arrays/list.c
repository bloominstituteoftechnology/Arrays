#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct ArrayList
{
  int count;                   // How many states does the array currently hold?
  struct LinkedList *elements; // The string elements contained in the array
  long indexLong;
} ArrayList;

typedef struct LinkedList
{
  struct ListNode *head;
  struct ListNode *tail;
} LinkedList;

typedef struct ListNode
{
  char *value;
  int index;
  struct ListNode *next;
  struct ListNode *prev;
} ListNode;

ListNode *create_node(char *item)
{

  //Allocate memory for node
  ListNode *node = malloc(sizeof(ListNode));

  //Save data
  node->value = item;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

LinkedList *create_list()
{
  //Allocate memory for list
  LinkedList *linked_list = malloc(sizeof(LinkedList));

  //Save data
  linked_list->head = NULL;
  linked_list->tail = NULL;

  return linked_list;
}

ArrayList *create_array(int capacity)
{

  //Allocate memory for array list
  ArrayList *arr = malloc(sizeof(ArrayList));

  //Initialize data
  arr->count = 0;
  arr->indexLong = 0;
  arr->elements = create_list();

  return arr;
}

/* Array functions
-------- Insert, Remove, Read ---------
*/

/* Read all elements in the array and print to stdout
*/
void arr_read(ArrayList *arr)
{
  // Otherwise, return the element at the given index
  //Loop through and check if index matches, return once it matches;
  ListNode *curr_node = arr->elements->head;
  while (curr_node)
  {
    printf("%s\n", curr_node->value);
    curr_node = curr_node->next;
  }
}

/* Append element to end of the array list
*/
void arr_append(ArrayList *arr, char *item)
{
  printf("lets append this item: %s\n", item);
  LinkedList *list = arr->elements;

  if (list->head == NULL)
  {
    printf("list head is null, lets create a node\n");
    ListNode *node = create_node(item);
    printf("created node:  %s\n", node->value);
    list->head = node;
    list->tail = node;

    node->index = arr->indexLong;
    arr->indexLong++;
    arr->count++;
    printf("new count: %d\n", arr->count);
  }
  else
  {
    printf("list is not empty. the head is %s\n", list->head->value);
    //Create new ListNode
    ListNode *new_node = create_node(item);
    printf("initialized new node: %s\n", new_node->value);
    //Save list's tail in temporary node
    ListNode *tmp_node = list->tail;
    printf("Tail is stored in tmp value: %s\n", tmp_node->value);
    //Assign temporary node's next property to new node
    list->tail->next = new_node;

    //Assign new node's prev property to temporary node
    new_node->prev = list->tail;

    //Save list's tail property to new node
    list->tail = new_node;

    //Update data
    // index breaks if i remove an element ????
    new_node->index = arr->indexLong;
    arr->count++;
    arr->indexLong++;
  }
}

/* Get the element at the given index
*/
char *arr_get(ArrayList *arr, int index)
{
  if (arr->elements->head == NULL)
  {
    return NULL;
  }
  ListNode *curr_node = arr->elements->head;
  while (curr_node)
  {
    if (curr_node->index == index)
    {
      return curr_node->value;
    }
    curr_node = curr_node->next;
  }
}

void arr_remove(ArrayList *arr, char *item)
{
  if (arr->elements->head == NULL)
  {
    //error
  }
  ListNode *curr_node = arr->elements->head;
  while (curr_node)
  {
    if (curr_node->value == item)
    {
      //update prev node to skip curr_node
      curr_node->prev->next = curr_node->next;

      //updaten ext node to skip curr_node
      curr_node->next->prev = curr_node->prev;

      //Update data
      arr->count--;
    }
    curr_node = curr_node->next;
  }
}

int main(void)
{

  ArrayList *arr = create_array(1);
  arr_append(arr, "hello");
  arr_append(arr, "i");
  arr_append(arr, "love");
  arr_append(arr, "you");
  arr_append(arr, "wont");
  arr_append(arr, "you");
  arr_append(arr, "tell");
  arr_append(arr, "me");
  arr_append(arr, "your");
  arr_append(arr, "name");
  //it was giving me a segmentation error if i try to read before inserting any elements
  //printf("%s", arr_read(arr, 0));

  arr_read(arr);
  arr_remove(arr, "me");
  printf("remove 'me' from ArrayList\n");
  arr_read(arr);
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