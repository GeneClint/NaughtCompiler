#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

char * initLabel (  ) 
 { 
int32_t temp0 = 1;
int32_t temp1;
int32_t temp2 = strlen("Result");
nstring_st* temp3 = malloc(sizeof(int32_t) + sizeof(char) * temp2 + 1);
temp3->len = temp2;
strcpy(temp3->str, "Result");
char * temp4 = temp3->str;
int32_t temp5 = strlen("1 is false!");
nstring_st* temp6 = malloc(sizeof(int32_t) + sizeof(char) * temp5 + 1);
temp6->len = temp5;
strcpy(temp6->str, "1 is false!");
char * temp7 = temp6->str;
if (temp0) {
  temp1 = temp4;
} else {
  temp1 = temp7;
}

char * result = temp1;
return result;

 } 

