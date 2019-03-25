Matt Wright 3/25/2019

# Arrays

Arrays are the most common and perhaps the simplest data structures. Are they really so simple though? High-level languages like Python, JavaScript, Swift and Java all have built-in "magic" that hides the complexity of many array functions. Although the complexity is hidden, you still have to pay the performance costs of that complexity.

For this assignment, you will be implementing high-level array functionality from the ground up. You will construct methods from memory and pointers to create, destroy, read and write arrays. Then, you will write code to add and remove elements from your array. Sounds simple, right?

By the end of this assignment, you will gain much appreciation for the magic of high-level coding languages as well as a deeper understanding of the costs associated with their functionality.

Similar to last week's assignment, move into the arrays directory and add your code to `arrays.c`. Run it by typing `make`, then `./arrays`. Run tests with `make tests`.

### Part 1: Create, Destroy, Read and Append

You are given the skeleton of an array implementation in C which you will be responsible for filling out. Start by reviewing the Array struct, then fill out the following functions:

1. `create_array()`
2. `destroy_array()`
3. `arr_append()`
4. `arr_read()`

Create and destroy should be self-explanatory: Initialize your array values and allocate memory on creation, then free that memory on destruction.

Reading from an array is simple as well: Check if the given index is in range, then return the value at that index.

`arr_append()` should work like the Python `append()` list method: Insert an element to the end of the array. Note that you will only be able to add as many elements as you allocated space for when you created the array.

### Part 2: Insert, Delete and Resize

Insertion and deletion should work like the Python `insert()` and `remove()` list methods. Insert should let you add an element to an arbitrary index in the array and delete should look for the first instance of the provided element and remove it. Remember that arrays require each element to be side-by-side like a bookshelf so you will need to move each element after the given index to the right or left for insert/delete respectively.

Resizing involves allocating a block of memory with double the storage, copying elements from the old block to the new, and freeing the old block. You should automatically resize when an insert or append takes your array past the allocated capacity.

1. `arr_insert()`
2. `arr_remove()`
3. `resize_array()`

### Stretch Goals

1. Reimplement your Dynamic Array using a linked list instead of a contiguous array (or if you used a linked list in the first place, use a contiguous array). How does the time complexity of each operation change as a result of swapping out the underlying data structure?

2. How would we go about making our dynamic array be able to handle multiple types in a single instance? Hint: we'll probably want to make use of [C unions](https://www.tutorialspoint.com/cprogramming/c_unions.htm) for this. Think about how you might do this and then implement it!

3. If you finish these goals, try implementing some of the other Python functions:

- `clear()`
- `copy()`
- `extend()`
- `index()`
- `pop()`
- `reverse()`
- `sort()`

Check the official documentation or use Python's `help()` method for implementation details.
