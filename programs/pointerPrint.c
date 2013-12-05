#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t s (  ) 
 { 
int32_t temp0 = 5;
int32_t x = temp0;
int32_t x = &x;
int32_t * y = x;
printf("%p", (void *) y);
int32_t * temp4 = y;


int32_t * y = *y;
return y;

 } 

