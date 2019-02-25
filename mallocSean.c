#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Dynamically allocate arrays on the heap
    // These can be resized with realloc()

    char *a = malloc(100); // 100 bytes
    char *b = malloc(200 * sizeof(char)); // 200 bytes, sizeof(char) always 1
    int *c = malloc(300 * sizeof(int));  // 300 ints, sizeof(int) is always greater than 1

    // Allocate arrays on the stack
    // These cannot be resized with realloc()

    char d[100];
    char e[200];
    int f[300];

    // pointer and array equivalence mean that you can use either
    // notation with either type.

    printf("%d\n", a[2] == *(a+2)); // True

    printf("%d\n", f[10] == *(f+10)); // True

    // Free dynamically-allocated data
    free(a);
    free(b);
    free(c);

    // This demo doesn't use these; they're here to stop compiler warnings:
    (void)d; (void)e;

    return 0;
}