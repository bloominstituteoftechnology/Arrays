#include <stdio.h>

struct Point
{
    int x;
    int y;
    char name[10];
};

int main(void) 
{
    // struct Point p1 = {10, 70, "Casper"};
    // // struct Point *p2 = &p1; 
    
    // printf("p1: x = %d, y = %d, name = %s\n", p1.x, p1.y, p1.name);


    double balance[5] = {10.0, 20.0, 30.0, 40.0, 50.0};
    double *p;
    int i;
    p = balance;

    for (i = 0; i < 5; i++) {
        printf("balance[%d]: %f\n", i, *(balance+i));
    }

    // printf("%f", balance);

    return 0;
}