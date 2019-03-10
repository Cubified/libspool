# libspool v0.0.1

A small, single-header memory pool implementation.

## Why

libspool (libsmallpool) aims to be a relatively fast solution for situations which require some form of dynamic array or list allocation.  It accomplishes this by avoiding individual calls to `malloc()` and `free()`, instead opting for a single call to each at pool creation and destruction respectively.

This project was developed to replace the linked list implementation used by my window manager [ntwm](https://github.com/Cubified/ntwm), and its limited use has already seen an improvement in speed and memory usage (albeit fairly minor).

## Example

Barebones usage of libspool is as follows:

```c
     int n = 5;
     int newvar = 10;

     void *d;
     int v;

     pool *p = pool_init(10);   /* Create a pool with 10 available slots - malloc() is called once here */

     pool_push(&n, p);          /* Push a pointer to a variable to the first available slot */
     pool_pop(0, p);            /* Remove the first item in the pool */
     pool_push(&newvar, p);     /* Push a pointer to another variable into this newly-freed slot */

     pool_foreach(p){           /* Iterate over each used item in the pool */
       d = pool_get(ind, p);    /* Get the pointer to the item in the pool which is currently being iterated over */
       v = pool_astype(d, int); /* Dereference pointer into an int (same as *(int*)d) */
     }

     pool_free(p);              /* Frees the entire pool - free() is called once here */

```

## Testing

To compile the provided test program, simply run:

     make

This will generate `libspool_test`, which should (hopefully) output something along the lines of:

     Added 97 to pool.
       Available slots = 11111110
     Added 36 to pool.
       Available slots = 11111100
     Added 32 to pool.
       Available slots = 11111000
     Added 1 to pool.
       Available slots = 11110000
     Added 53 to pool.
       Available slots = 11100000
     Added 18 to pool.
       Available slots = 11000000
 
     Popped element 1, available slots now = 11000010
 
     Slot values:
       Index 0: 97
       Index 2: 32
       Index 3: 1
       Index 4: 53
       Index 5: 18

## Using

As libspool is a single header, copy `libspool.h` into your source tree and include it accordingly.

## Limitations

By design, libspool is limited in the number of items it can hold, with the exact amount depending on `sizeof(int)` on the host system - in the majority of cases, this means libspool cannot hold more than __31 items__ by default.  While this may sound limiting, the project for which this was designed is an example of an ideal use-case - a window manager likely has no more than this number of items at a time, but must be able to quickly (and constantly) remove and replace them.  If a relatively large number of items must be managed, then libspool likely isn't the best solution.

However, to expand this limit, the `avail` member of the `pool` struct can be changed to an `unsigned int` or `uint64_t`, thereby expanding the maximum number to 32 or 64 items respectively.
