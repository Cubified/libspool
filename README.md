# libspool v0.0.1

A small, single-header memory pool implementation.

## Why

libspool aims to be a relatively fast solution to situations which require some form of dynamic memory allocation.  It accomplishes this by avoiding individual calls to `malloc()` and `free()`, instead opting for a single call to each, at pool creation and destruction respectively.

libspool was developed to replace the linked list implementation used by my window manager ![ntwm](https://github.com/Cubified/ntwm), and its limited use has already seen an improvement in speed and memory usage (albeit fairly minor).

## Example

Barebones usage of libspool is as follows:

     int n = 5;

     void *d;
     int v;

     pool *p = pool_init(10);  /* Create a pool with 10 available slots - malloc() is called once here */

     pool_push(&n, p);       /* Push a pointer to a variable to the first available slot */
     pool_pop(0, p);           /* Remove the first item in the pool */
     pool_push(&newvar, p)

     pool_foreach(p){          /* Iterate over each used item in the pool */
       d = pool_get(0, p);     /* Get the pointer to the first item in the pool */
       v = pool_astype(d, int) /* Dereference pointer into int (same as *(int*)d) */
     }

     pool_free(p);             /* Frees the entire pool - free() is called once here */

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
