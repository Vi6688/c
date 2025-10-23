#include "List.h"
#include "BasicTypes.h"
#include "Memory.h"
#include "Vector.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListPtr createList(const size_t sizeOfElement) {
  ListPtr list = newAlloc(sizeof(List));
  if (!list) {
    perror("Failed to allocate list");
    exit(EXIT_FAILURE);
  }
  list->data = NULL;
  list->size = 0;
  list->elementSize = sizeOfElement;
  list->capacity = 0;
  return list;
}

void printList(List *list) {
  List *newList = list;
  printf("{");
  loopI(list->size) { printf(" %d,", ((int *)(newList->data))[i]); }
  printf("}");
  newline
}
void *valueAt(List *list, int idx) {
  if (idx < 0 || (size_t)idx >= list->size) {
    return NULL;
  }
  return (char *)list->data + idx * list->elementSize;
}

void appendList(List *list, const void *value) {
  if (list->size == list->capacity) {
    size_t newCapacity = (list->capacity == 0) ? 1 : list->capacity * 2;
    void *newData = newReAlloc(list->data, newCapacity * (list->elementSize));
    if (!newData) {
      perror("Failed to realloc memory");
      exit(EXIT_FAILURE);
    }
    list->data = newData;
    list->capacity = newCapacity;
  }

  // Copy the new element into the list
  char *target = (char *)list->data + list->size * list->elementSize;
  memcpy(target, value, list->elementSize);
  list->size++;
}