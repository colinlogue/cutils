# cutils
Some utilities I've made for C programs.

## General utilities

### intmath
Some basic math functions for integers such as max and min.

### memshuffle
Shuffles memory in place using the Fisher-Yates algorithm.

Usage example: shuffling an array of ints
```c
// allocate memory for array outside of memshuffle function
size_t unit_size = sizeof(int);
int n_units = 5;
int arr[5] = {1,2,3,4,5};

// shuffle array
mem_shuffle(arr, n_units, unit_size);

// order after shuffle: 3 5 1 2 4
```

## Template utilities
These are templates for creating .c and .h files. They are some basic abstract
data types such as a linked list and binary search tree that can be used for
any data type. There are some python scripts for creating the source files from the templates that replace `<<TYPE>>` with the data type you would like the
list/tree/etc. to hold.

### templates/bst_base
Template for a binary search tree struct and associated functions.

### templates/list_base
Template for a doubly linked list.
