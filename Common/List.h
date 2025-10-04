#pragma once
#include <stddef.h>
typedef struct List {
  void *data;
  size_t size;
  size_t elementSize;
  size_t capacity;
} List;
typedef List *ListPtr;

void createList(ListPtr list, const size_t sizeOfElement);
void printList(List *list);
void appendList(List *list, const void *value);
