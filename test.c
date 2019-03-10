/*
 * test.c: a simple test for libspool
 */

#include <stdio.h>
#include <time.h>

#include "libspool.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x800 ? '1' : '0'), \
  (byte & 0x400 ? '1' : '0'), \
  (byte & 0x200 ? '1' : '0'), \
  (byte & 0x100 ? '1' : '0'), \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

int main(){
  pool *p;
  int i, r, ind;

  srand(time(NULL));

  p = pool_init(rand()%15 + 1);

  printf("Created pool of size %i.\n\n", p->size);

  for(i=0;i<p->size;i++){
    r = rand() % 100;
    pool_push((void*)r, p);
    printf("Added %i to pool.\n", r);
    printf("  Available slots = " BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(p->avail));
  }

  printf("\n");
  
  r = rand() % p->size;
  pool_pop(r, p);
  printf("Popped element %i, available slots now = " BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN "\n", r, BYTE_TO_BINARY(p->avail));
  
  printf("\nSlot values:\n");

  pool_foreach_nodecl(p){
    printf("  Index %i: %i\n", ind, (int)pool_get(ind, p));
  }

  printf("\nTesting overflow catching:\n  ");

  pool_push((void*)r, p);
  pool_push((void*)r, p);

  pool_free(p);

  return 0;
}
