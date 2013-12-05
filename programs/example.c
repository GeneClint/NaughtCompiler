#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct nstring_st {
  int32_t   len;
  char      str[];
} nstring_st;

int32_t fact ( int32_t x , int32_t * p );

char * initLabel (  );

int32_t globalInt;
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
char * temp5 = initLabel ();
char * label = temp5;
int32_t * p;
int32_t temp6 =  x * y ;
int32_t temp7 =  y + temp6 ;
int32_t temp8 = fact (y,p = &globalInt);
printf("%d", temp8);
int32_t temp9 = temp8;
int32_t temp10 =  temp7 + temp9 ;
z = temp10;

int32_t temp11 = strlen(" = ");
nstring_st* temp12 = malloc(sizeof(int32_t) + sizeof(char) * temp11 + 1);
temp12->len = temp11;
strcpy(temp12->str, " = ");
char * temp13 = temp12->str;
int32_t temp14 = *((int32_t*)label - 1) + *((int32_t*)temp13 - 1);
nstring_st* temp15 =  malloc(sizeof(int32_t) + (temp14 + 1) * sizeof(char));
temp15->len = temp14 ;
char * temp16 = temp15->str;
strcpy (temp16, label);
strcat (temp16, temp13);
char * temp17 =  temp16;

int32_t temp18 = printf ("%s %d\n",label,z);

int32_t temp19 = printf ("The label '%s' has length %d\n",label,nstrlen (label));

int32_t temp20 = printf ("globalInt = %d\n",*p);

int32_t temp21 = 0;
return temp21;

 } 

