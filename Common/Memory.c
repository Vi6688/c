#include "BasicTypes.h"
#include "Thread.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void **pointersToFree = NULL; // dynamic array of pointers
long long int pointersToFreeCount = 0;
long long int pointersToFreeCapacity = 0;

int findIndexOfAllocatedPtr(void *ptr) {
  loopI(pointersToFreeCount) {
    if (pointersToFree[i] == ptr) {
      return i;
    }
  }
  return pointersToFreeCount + 1;
}

// helper function to grow array
void ensureCapacity() {
  if (pointersToFreeCount >= pointersToFreeCapacity) {
    // grow capacity (start with 10, then double)
    int newCapacity =
        (pointersToFreeCapacity == 0) ? 10 : (pointersToFreeCapacity * 2);
    void **newArray = realloc(pointersToFree, newCapacity * sizeof(void *));
    if (!newArray) {
      fprintf(stderr, "Out of memory!\n");
      exit(1);
    }
    pointersToFree = newArray;
    pointersToFreeCapacity = newCapacity;
  }
}
string newChar(const int size) {
  void *ptr = malloc(size * sizeof(char));
  ensureCapacity();
  pointersToFree[pointersToFreeCount++] = ptr;
  return (string)(ptr);
}

void *newAlloc(const size_t size) {
  void *ptr = malloc(size);
  ensureCapacity();
  int previousPtrIndex = findIndexOfAllocatedPtr(ptr);
  if (previousPtrIndex > pointersToFreeCount)
    pointersToFree[pointersToFreeCount++] = ptr;
  else
    pointersToFree[previousPtrIndex] = ptr;
  return (ptr);
}

void *newReAlloc(void *ptr, const size_t size) {
  void *newPtr = realloc(ptr, size);
  ensureCapacity();
  int previousPtrIndex = findIndexOfAllocatedPtr(ptr);
  if (previousPtrIndex > pointersToFreeCount)
    pointersToFree[pointersToFreeCount++] = newPtr;
  else
    pointersToFree[previousPtrIndex] = newPtr;
  return newPtr;
}

void destruct() {
  destructThreadHandles();
  printf("Freeing allocated pointers. Total pointers freed = %d", pointersToFreeCount);
  for (int i = 0; i < pointersToFreeCount; i++) {
    free(pointersToFree[i]);
  }
  free(pointersToFree); // free the tracking array itself
  pointersToFree = NULL;
  pointersToFreeCount = 0;
  pointersToFreeCapacity = 0;
  newline
}
