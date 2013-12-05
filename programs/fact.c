#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t fact ( int32_t x , int32_t * p ) 
 { 
int32_t temp0 = fact ((x - 1),p);
int32_t temp1 =  x * temp0 ;
int32_t temp2 = 1;
int32_t temp3 =  x ? temp1  : temp2 ;
*p = temp3;
return temp4;

 } 

