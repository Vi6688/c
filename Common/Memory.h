#pragma once
#include "BasicTypes.h"

void *newAlloc(const size_t size);
void *newReAlloc(void *ptr, const size_t size);
void destruct();    
void freeAlloc(void *ptr);