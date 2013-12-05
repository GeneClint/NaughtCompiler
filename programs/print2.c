#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t main (  ) 
 { 
int32_t temp0 = 1;
int32_t x = temp0;
int32_t temp1 = 2;
int32_t y = temp1;
int32_t temp2 = 3;
int32_t z = temp2;
printf("%d", y);
int32_t temp4 = y;
printf("%d", x);
int32_t temp6 = x;
int32_t temp7 =  temp4 + temp6 ;
int32_t a = temp7;
printf("%d", y);
int32_t temp9 = y;
printf("%d", x);
int32_t temp11 = x;
int32_t temp12 =  temp9 * temp11 ;
int32_t b = temp12;
int32_t temp13 = 0;
return temp13;

 } 

