#pragma once
#include <stddef.h>

typedef double Num;
typedef char *string;
typedef unsigned int uint;
typedef uint sizeT;
typedef unsigned long int uint64;
typedef int Boolean;
typedef long long Time;
typedef void *voidPtr;
typedef voidPtr Mutex;
typedef unsigned long ThreadFunc;
#define funcPtr void(*func)

// Easy loop for the for loop

#define true 1
#define false 0
#define newline printf("\n");
#define loopI(SIZE) for (int i = 0; i < SIZE; i++)
#define loopJ(SIZE) for (int j = 0; j < SIZE; j++)
#define loopK(SIZE) for (int k = 0; k < SIZE; k++)

#define print(VALUE) printf(VALUE);

#define printl(VALUE)                                                          \
  {                                                                            \
    printf(VALUE);                                                             \
    newline;                                                                   \
  }
#define PI 3.14