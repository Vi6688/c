#pragma once
#include <stddef.h>

typedef double Num;
typedef char *String;
typedef int *IntVector;
typedef float *FloatVector;
typedef double *NumVector;
typedef unsigned int uint;
typedef uint sizeT;
typedef unsigned long int uint64;



// Easy loop for the for loop

#define newline printf("\n");
#define loopI(SIZE) for (int i = 0; i < SIZE; i++)
#define print(VALUE)                                                           \
  printf(VALUE);                                                               \
  ;
#define printl(VALUE)                                                          \
  printf(VALUE);                                                               \
  newline;
