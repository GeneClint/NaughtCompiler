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
int32_t temp1 = 2;
int32_t temp2 =  temp1 * x ;
int32_t temp3 = 1;
int32_t temp4 =  temp2 + temp3 ;
int32_t y = temp4;
int32_t z;
int32_t temp5 = initLabel ();
char * label = temp5;
int32_t * p;
int32_t temp6 =  x * y ;
int32_t temp7 =  y + temp6 ;
int32_t temp8 = fact (y,p = &globalInt);
printf("%d\n", temp8);
int32_t temp9 = temp8;
int32_t temp10 =  temp7 + temp9 ;
z = temp10;
int32_t temp11 = z;

int32_t temp12 = strlen(" = ");
nstring_st* temp13 = malloc(sizeof(int32_t) + sizeof(char) * temp12 + 1);
temp13->len = temp12;
strcpy(temp13->str, " = ");
char * temp14 = temp13->str;
int32_t temp15 = *((int32_t*)label - 1) + *((int32_t*)temp14 - 1);
nstring_st* temp16 =  malloc(sizeof(int32_t) + (temp15 + 1) * sizeof(char));
temp16->len = temp15 ;
char * temp17 = temp16->str;
strcpy (temp17, label);
strcat (temp17, temp14);
char * temp18 =  temp17;
char * temp18 = label;

int32_t temp19 = printf ("%s %d\n",label,z);

int32_t temp20 = printf ("The label '%s' has length %d\n",label,nstrlen (label));

int32_t temp21 = printf ("globalInt = %d\n",*p);

int32_t temp22 = 0;
return temp22;

 } 

