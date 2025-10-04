#pragma once
#include "List.h"

/* -------- IntList -------- */
typedef struct IntList {
  List list;
  int (*dataAt)(struct IntList *, int);
} IntList;

IntList *createIntList(void);
void appendInt(IntList *, int);

/* -------- DoubleList -------- */
typedef struct DoubleList {
  List list;
  double (*dataAt)(struct DoubleList *, int);
} DoubleList;

DoubleList *createDoubleList(void);
void appendDouble(DoubleList *, double);

/* -------- StringList -------- */
typedef struct StringList {
  List list;
  char *(*dataAt)(struct StringList *, int);
} StringList;

StringList *createStringList(void);
void appendString(StringList *, const char *);
void destroyStringList(StringList *);
