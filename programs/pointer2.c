#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t ptrMADNESS ( int32_t * x ) 
 { 
printf("%p\n", (void *) x);
int32_t * temp0 = x;
int32_t temp1 = 1;
int32_t * temp2 =  temp0 + temp1 ;
int32_t * y = temp2;
int32_t temp3 = 1;
int32_t * temp4 =  y - temp3 ;
int32_t temp6 = *(y - 1);
return temp6;

 } 

int32_t main (  ) 
 { 
int32_t temp7 = 5;
int32_t x = temp7;
int32_t * temp8 = &x;
int32_t * y = temp8;
int32_t temp9 = 10;
int32_t z = temp9;
printf("%d\n", x);
int32_t temp10 = x;
printf("%d\n", z);
int32_t temp11 = z;
int32_t temp12 =  temp10 + temp11 ;
int32_t a = temp12;
int32_t res;
printf("%d\n", x);
int32_t temp13 = x;

printf("%p\n", (void *) y);
int32_t * temp14 = y;

int32_t temp15 = ptrMADNESS (y);
res = temp15;
int32_t temp16 = res;

printf("%d\n", res);
int32_t temp17 = res;

int32_t temp18 = 0;
return temp18;

 } 

