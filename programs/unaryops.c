#include <stdio.h>
#include <stdlib.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t * x;
int32_t temp0 = *x;
int32_t y = temp0;
int32_t temp1 = &y;
int32_t * z = temp1;
