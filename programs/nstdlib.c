#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t nstrlen ( char * s ) 
 { 
char * * temp0 = &s;
int32_t * stringAddress = temp0;
int32_t temp1 = 1;
int32_t * temp2 =  stringAddress - temp1 ;
int32_t * lengthAddress = temp2;
int32_t temp3 = *lengthAddress;
int32_t length = temp3;
return length;

 } 

