#pragma once
#include "BasicTypes.h"
#include "Vector.h"
#include <stddef.h>
typedef struct {
  void *data;
  size_t size;
  size_t elementSize;
  size_t capacity;
} *List;
// typedef List *List;

List createList(const size_t sizeOfElement);
void printList(List list);
void appendList(List list, const void *value);
void *valueAt(List list, int idx);
Boolean deleteElement(List list, size_t index);