#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t main (  ) 
 { 
int32_t temp0 = 5;
int32_t x = temp0;
int32_t * temp1 = &x;
int32_t * p = temp1;
int32_t temp2 = *p;
int32_t y = temp2;
printf("%d", x);
int32_t temp3 = x;

printf("%d", y);
int32_t temp4 = y;

printf("%p", (void *) p);
int32_t * temp5 = p;

int32_t temp6 = 0;
return temp6;

 } 

