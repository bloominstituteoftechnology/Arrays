// Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    fprintf(stderr, "Index is out of range.");
    exit(1);
  }

  // Resize the array if the number of elements is equal to or over capacity
  if (arr->count >= arr->capacity)
  {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i = arr->count; i > index; i--)
  {
    arr->elements[i] = arr->elements[i - 1]; // repointing the new address to previous element's address
  }

  // Copy the element and add it to the array
  char *new_element = element;        // copy the element so it doesn't get lost
  arr->elements[index] = new_element; // setting a value at specified index

  // Increment count by 1
  arr->count += 1;