#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t p (  ) 
 { 
int32_t temp0 = 5;
int32_t x = temp0;
int32_t x = &x;
int32_t * y = x;
int32_t * y = *y;
int32_t z = y;
return z;

 } 

