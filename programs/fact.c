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
int32_t temp0;
int32_t temp1 = 1;
int32_t temp2 =  x - temp1 ;
int32_t temp3 = fact (temp2, p);
int32_t temp4 =  x * temp3 ;
int32_t temp5 = 1;
if (x) {
  temp0 = temp4;
} else {
  temp0 = temp5;
}

*p = temp0;
int32_t temp7 = *p;
return temp7;

 } 

