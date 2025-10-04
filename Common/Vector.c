#include "Vector.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* -------- IntList -------- */
static int intDataAt(IntList *list, int idx) {
  return ((int *)list->list.data)[idx];
}

IntList *createIntList(void) {
  IntList *l = newAlloc(sizeof(IntList));
  l->dataAt = intDataAt;
  createList(&l->list, sizeof(int));
  return l;
}

void appendInt(IntList *list, int val) { appendList(&list->list, &val); }

/* -------- DoubleList -------- */
static double doubleDataAt(DoubleList *list, int idx) {
  return ((double *)list->list.data)[idx];
}

DoubleList *createDoubleList(void) {
  DoubleList *l = newAlloc(sizeof(DoubleList));
  l->dataAt = doubleDataAt;
  createList(&l->list, sizeof(double));
  return l;
}

void appendDouble(DoubleList *list, double val) {
  appendList(&list->list, &val);
}

/* -------- StringList -------- */
static char *stringDataAt(StringList *list, int idx) {
  return ((char **)list->list.data)[idx];
}

StringList *createStringList(void) {
  StringList *l = newAlloc(sizeof(StringList));
  l->dataAt = stringDataAt;
  createList(&l->list, sizeof(char *));
  return l;
}

void appendString(StringList *list, const char *val) {
  char *copy = strdup(val);
  appendList(&list->list, &copy);
}