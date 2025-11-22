// AllocTracker.c
// Efficient pointer-tracker using an open-addressing hash table.
// Public API: newChar, newAlloc, newReAlloc, freeAlloc, destruct

#include "BasicTypes.h"
#include "Thread.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 Note:
 - This file intentionally avoids any external macro 'newline' or non-standard
 helpers.
 - If your project already defines 'string' (typedef char*), change newChar's
 return type accordingly.
*/

// If 'string' isn't available in your headers, uncomment the typedef below.
// typedef char *string;

/* -------------------- Configuration -------------------- */
#define INITIAL_TABLE_SIZE 16
#define LOAD_FACTOR 0.75

/* -------------------- Hash Table State -------------------- */
static void **pointerTable = NULL; // buckets array (NULL means empty slot)
static long long tableSize = 0;    // number of buckets
static long long trackedCount = 0; // number of active pointers stored

/* -------------------- Utilities -------------------- */

// A simple pointer hash: mix and multiply (64-bit friendly)
static inline unsigned long long hashPtr(void *p) {
  // Convert to integer
  uintptr_t x = (uintptr_t)p;
  // shift away low bits (alignment) and mix
  unsigned long long h = (unsigned long long)(x >> 3);
  // multiplicative hash (Knuth-like)
  h ^= h >> 33;
  h *= 0xff51afd7ed558ccdULL;
  h ^= h >> 33;
  h *= 0xc4ceb9fe1a85ec53ULL;
  h ^= h >> 33;
  return h;
}

/* -------------------- Table management -------------------- */

static void initTableIfNeeded(void) {
  if (pointerTable != NULL)
    return;
  tableSize = INITIAL_TABLE_SIZE;
  pointerTable = calloc((size_t)tableSize, sizeof(void *));
  if (!pointerTable) {
    fprintf(stderr, "AllocTracker: out of memory during init\n");
    exit(1);
  }
  trackedCount = 0;
}

// Reallocate and rehash into a new (bigger) table
static void growTable(void) {
  long long oldSize = tableSize;
  void **oldTable = pointerTable;

  long long newSize = (oldSize == 0) ? INITIAL_TABLE_SIZE : (oldSize * 2);
  void **newTable = calloc((size_t)newSize, sizeof(void *));
  if (!newTable) {
    fprintf(stderr, "AllocTracker: out of memory during grow\n");
    exit(1);
  }

  // swap in new table
  pointerTable = newTable;
  tableSize = newSize;
  trackedCount = 0;

  // reinsert existing pointers
  if (oldTable) {
    for (long long i = 0; i < oldSize; ++i) {
      void *p = oldTable[i];
      if (p != NULL) {
        // insert p into new table
        unsigned long long h = hashPtr(p) % (unsigned long long)tableSize;
        while (pointerTable[h] != NULL) {
          h = (h + 1) % (unsigned long long)tableSize;
        }
        pointerTable[h] = p;
        trackedCount++;
      }
    }
    free(oldTable);
  }
}

/* -------------------- Core operations -------------------- */

// Find the bucket index of ptr, or -1 if not present
static long long findIndex(void *ptr) {
  if (pointerTable == NULL)
    return -1;
  unsigned long long h = hashPtr(ptr) % (unsigned long long)tableSize;
  unsigned long long start = h;
  while (pointerTable[h] != NULL) {
    if (pointerTable[h] == ptr)
      return (long long)h;
    h = (h + 1) % (unsigned long long)tableSize;
    if (h == start)
      break; // full loop (shouldn't normally happen)
  }
  return -1;
}

// Insert ptr if not already present
static void insertPtr(void *ptr) {
  if (ptr == NULL)
    return;
  initTableIfNeeded();

  // grow if load factor exceeded
  if ((double)(trackedCount + 1) / (double)tableSize > LOAD_FACTOR) {
    growTable();
  }

  unsigned long long h = hashPtr(ptr) % (unsigned long long)tableSize;
  while (pointerTable[h] != NULL) {
    if (pointerTable[h] == ptr) {
      // already present
      return;
    }
    h = (h + 1) % (unsigned long long)tableSize;
  }
  pointerTable[h] = ptr;
  trackedCount++;
}

// Remove ptr from table if present
static void removePtr(void *ptr) {
  if (pointerTable == NULL || ptr == NULL)
    return;
  long long idx = findIndex(ptr);
  if (idx < 0)
    return; // not present

  // Remove entry
  pointerTable[idx] = NULL;
  trackedCount--;

  // Rehash the cluster following the removed slot
  long long i = (idx + 1) % tableSize;
  while (pointerTable[i] != NULL) {
    void *movedPtr = pointerTable[i];
    pointerTable[i] = NULL;
    trackedCount--; // insertPtr will increment
    insertPtr(movedPtr);
    i = (i + 1) % tableSize;
  }
}

/* -------------------- Public API -------------------- */

// Allocate a zero-terminated char buffer (like newChar in your original)
char *newChar(const int size) {
  if (size <= 0)
    return NULL;
  char *p = (char *)malloc((size_t)size * sizeof(char));
  if (!p) {
    fprintf(stderr, "newChar: malloc failed for size %d\n", size);
    exit(1);
  }
  // Optional: zero-initialize so strings are safe
  memset(p, 0, (size_t)size * sizeof(char));
  insertPtr((void *)p);
  return p;
}

// Generic allocator
void *newAlloc(const size_t size) {
  if (size == 0) {
    // follow standard: malloc(0) may return NULL or unique pointer
    void *p = malloc(0);
    if (p != NULL)
      insertPtr(p);
    return p;
  }
  void *p = malloc(size);
  if (!p) {
    fprintf(stderr, "newAlloc: malloc failed for size %zu\n", size);
    exit(1);
  }
  insertPtr(p);
  return p;
}

// Realloc wrapper: updates tracking. Behaves like realloc:
// - if ptr == NULL, acts like malloc
// - if size == 0, behavior is implementation-defined: treat as free + return
// NULL for simplicity
void *newReAlloc(void *ptr, const size_t size) {
  if (ptr == NULL) {
    return newAlloc(size);
  }
  if (size == 0) {
    // free and return NULL (explicit choice for clarity)
    removePtr(ptr);
    free(ptr);
    return NULL;
  }

  // Perform realloc
  void *newPtr = realloc(ptr, size);
  if (!newPtr) {
    fprintf(stderr, "newReAlloc: realloc failed for size %zu\n", size);
    exit(1);
  }

  // Update tracking: remove old ptr (if different) and insert new
  if (newPtr == ptr) {
    // same address, nothing to change
    // ensure it is tracked (it probably is)
    insertPtr(newPtr);
  } else {
    // address changed
    removePtr(ptr);
    insertPtr(newPtr);
  }
  return newPtr;
}

// Free wrapper: only frees if tracked
void freeAlloc(void *ptr) {
  if (ptr == NULL)
    return;
  long long idx = findIndex(ptr);
  if (idx < 0) {
    // not tracked => still free to avoid leak but warn optional
    // fprintf(stderr, "freeAlloc: pointer not tracked; freeing anyway\n");
    free(ptr);
    return;
  }
  removePtr(ptr);
  free(ptr);
}

// Free everything and cleanup. Also calls destroyAllThreads() as in your
// original.
void destruct(void) {
  destroyAllThreads();

  printf("\nFreeing tracked allocations. Count = %lld\n", trackedCount);

  if (pointerTable) {
    for (long long i = 0; i < tableSize; ++i) {
      void *p = pointerTable[i];
      if (p != NULL) {
        free(p);
      }
    }
    free(pointerTable);
    pointerTable = NULL;
  }
  tableSize = 0;
  trackedCount = 0;
  printf("Done.\n");
}

/* -------------------- (Optional) Debug helpers -------------------- */

#ifdef ALLOCTRACKER_DEBUG
#include <inttypes.h>
void printTableStats(void) {
  printf("Table size: %lld, tracked: %lld\n", tableSize, trackedCount);
  if (!pointerTable)
    return;
  for (long long i = 0; i < tableSize; ++i) {
    if (pointerTable[i]) {
      printf(" bucket %3lld: %p\n", i, pointerTable[i]);
    }
  }
}
#endif

/* End of AllocTracker.c */
