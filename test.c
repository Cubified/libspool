/*
 * test.c: a simple test for libspool
 */

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "libspool.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

int main(){
  srand(time(NULL));

  pool *p = pool_init(rand()%8);

  /*
   * int64 may cause a warning/error on
   * 32-bit systems
   */
  uint64_t i, r;
  for(i=0;i<p->size;i++){
    r = rand() % 100;
    pool_push((void*)r, p);
    printf("Added %i to pool.\n", r);
    printf("  Available slots = " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(p->avail));
  }

  printf("\n");
  
  r = rand() % p->size;
  pool_pop(r, p);
  printf("Popped element %i, available slots now = " BYTE_TO_BINARY_PATTERN "\n", r, BYTE_TO_BINARY(p->avail));
  
  printf("\nSlot values:\n");

  pool_foreach(p){
    printf("  Index %i: %i\n", ind, pool_get(ind, p));
  }

  pool_free(p);

  return 0;
}
