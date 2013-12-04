#include <stdio.h>
#include <stdlib.h>

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


return a;

 } 

int32_t main (  ) 
 { 
int32_t temp11 = 1;
int32_t x = temp11;
int32_t temp12 = 3;
int32_t z = temp12;
int32_t temp13 = 1;
int32_t temp14 =  x + temp13 ;
int32_t y = temp14;
id z = z;
id y = y;
int32_t temp15 =  z + y ;
z = temp15;


int32_t temp16 = complex (z,x);


id z = z;
return z;

 } 

