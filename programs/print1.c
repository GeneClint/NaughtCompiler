#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t main (  ) 
 { 
int32_t temp0 = 1;
int32_t x = temp0;
int32_t temp1 = strlen("hello");
nstring_st* temp2 = malloc(sizeof(int32_t) + sizeof(char) * temp1 + 1);
temp2->len = temp1;
strcpy(temp2->str, "hello");
char * temp3 = temp2->str;
char * s = temp3;
printf("%d\n", x);
int32_t temp4 = x;

printf("%s\n", s);
char * temp5 = s;

int32_t temp6 = 0;
return temp6;

 } 

