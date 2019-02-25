# Array
Array: a single block of contiguous memory of the same type stored sequentially

Python uses pointers to pointers to implement arrays of different types.

# malloc & realloc
malloc: allocates memory dynamically, i.e., allocated at runtime
realloc: return a new pointer to a block of resized memory
realloc
```c
// space for 25 integers
int *a = malloc(100);
int *b = malloc(100 * sizeof(int));

for (int i = 0; i < 5; i++) {
  b[i] = i;
}

for (int i = 0; i < 5; i++) {
    printf("%d\n", b[i]);
}

b = realloc(b, 10 * sizeof(int));

for (int i = 0; i < 5; i++) {
    printf("%d\n", b[i]);
}

for (int i = 0; i < 10; i++) {
    b[i] = i;
}

for (int i = 0; i < 10; i++) {
    printf("%d\n", b[i]);
}

```

# realloc
  Return a new pointer resize memory block
realloc







# Implementation of a Stack

1. Create a struct Stack (capacity *data, top)
   1) Establish capacity (i.e., total number of elements a stack can hold).
   2) Create pointer to our data
   3) Create index for the element at the top of the stack;

2. Create a Stack
   1) Parameter is size of memory allocated
   2) Malloc a chunk of memory for the Stack struct (malloc sizeof Stack)
   3) Initialize struct values (stack->capacity = capacity, stack->top = -1, stack->)
   4) Malloc additional memory for our data pointer(malloc capacity * sizeof(int))

3. Create Stack Method: Max Capacity
   1) Check if stack is at max capacity (top == capcity - 1)

4. Create Stack Method: Push
   1) Max Capacity Checker, if at max capacity:
      - increase capacity by 2
      - realloc data pointer
   2) Add item to top
   3) Update top to be item;

5. Create Stack Method: Empty Stack
   1) Check if stack is empty (stack->top == -1)

3. Create Stack Method: Pop
   1) Check if Stack is empty, if so:
      return -1
   2) Store element at the top into a variable (rv = stack->data[stack->top])
   3) Decrement our top index (stack->top--)
   4) return stored element (return rv)
   5) Combine steps 2-4 => return stack->data[stack->top--]

4. Free Stack 
   1) Check all malloc calls
   2) Free data
   3) Free stack





# sizeof

  printf("Null: %d\n", sizeof(NULL)); // 8
  printf("Zero: %d\n", sizeof(0)); // 4
  printf("Null Terminator: %d\n", sizeof('\0'));  // 4
  printf("Int: %d\n", sizeof(int)); // 4
  printf("Char: %d\n", sizeof(char)); // 1










