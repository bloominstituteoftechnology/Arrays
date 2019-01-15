#include <stdio.h>

struct Point
{
    int x;
    int y;
    char name[100];
} Point;

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;

int main(void) 
{

    // struct Point p1 = {10, 70, "Casper"};
    // struct Point *p2 = &p1; 
    
    // printf("p1: x = %d, y = %d, name = %s\n", p1.x, p1.y, p1.name);


    double balance[5] = {10.0, 20.0, 30.0, 40.0, 50.0};
    double *p;
    int i;
    p = balance;

    // for (i = 0; i < 5; i++) {
    //     printf("balance[%d]: %f\n", i, *(balance+i));
    // }

    // printf("%f", balance);

    // printf("size of %zu\n", sizeof(Array));

    // printf("Balance %d size: %lu\n", &balance, sizeof(balance));
    printf("Pointer %f size: %lu\n", *p, sizeof(*p));

    return 0;
}