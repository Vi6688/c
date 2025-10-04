#pragma once
#include "BasicTypes.h"

int *newInt(const int size);
char *newChar(const int size);
double *newNum(const int size);
void *newAlloc(const size_t size);
void *newReAlloc(void *ptr, const size_t size);
