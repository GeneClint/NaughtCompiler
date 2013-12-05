#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t complex ( int32_t a , int32_t b ) 
 { 
int32_t temp0 =  a + b ;
int32_t x = temp0;
int32_t temp1 = 2;
int32_t temp2 =  temp1 * b ;
int32_t temp3 = 3;
int32_t temp4 =  temp2 * temp3 ;
int32_t temp5 = temp4;
int32_t temp6 = 3;
int32_t temp7 =  temp6 * a ;
int32_t temp8 =  temp7 * a ;
int32_t temp9 = temp8;
int32_t temp10 =  temp5 + temp9 ;
a = temp10;
int32_t temp11 = a;

return a;

 } 

int32_t main (  ) 
 { 
int32_t temp12 = 1;
int32_t x = temp12;
int32_t temp13 = 3;
int32_t z = temp13;
int32_t temp14 = 1;
int32_t temp15 =  x + temp14 ;
int32_t y = temp15;
int32_t temp16 =  z + y ;
z = temp16;
int32_t temp17 = z;

int32_t temp18 = complex (z, x);

return z;

 } 

