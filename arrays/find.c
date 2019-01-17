#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int find_index(int a[], int num_elements, int value);
void print_array(int a[], int num_elements);

void main(void)
{
   int a[10] = {1, 2, 0, 0, 4, 5, 6, 9, 9, 17};
   int index, value;

   printf("\nArray:\n");
   print_array(a, 10);

   value = 1;
   index = find_index(a, 10, value);
   if (index == -1)
   {
	 printf("The value %d was not found.\n", value);
   }
   else
   {
	 printf("The value %d was found at %d\n", value, index);
   }

   value = 9;
   index = find_index(a, 10, value);
   if (index == -1)
   {
	 printf("The value %d was not found.\n", value);
   }
   else
   {
	 printf("The value %d was found at %d\n", value, index);
   }

   value = 10;
   index = find_index(a, 10, value);
   if (index == -1)
   {
	 printf("The value %d was not found.\n", value);
   }
   else
   {
	 printf("The value %d was found at %d\n", value, index);
   }
}

int find_index(int a[], int num_elements, int value)
{
   int i;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i] == value)
	 {
	    return(value);  /* it was found */
	 }
   }
   return(-1);  /* if it was not found */
}

void print_array(int a[], int num_elements)
{
   int i;
   for(i=0; i<num_elements; i++)
   {
	 printf("%d ", a[i]);
   }
   printf("\n");
}