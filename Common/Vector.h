#pragma once
#include <stddef.h>

/* -------- Type Enum -------- */
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
} ValueType;

/* -------- Union for data -------- */
typedef union {
    int i;
    double d;
    char *s;
} ValueData;

/* -------- Vector element -------- */
typedef struct {
    ValueType type;
    ValueData data;
} VectorElement;

/* -------- Vector -------- */
typedef struct {
    VectorElement *data;
    size_t size;
    size_t capacity;
} Vector;

/* -------- Vector functions -------- */

/* Create a new vector */
Vector *createVector(void);

/* Append different types */
void appendInt(Vector *v, int val);
void appendDouble(Vector *v, double val);
void appendString(Vector *v, const char *val);

/* Get element at index */
VectorElement getElement(Vector *v, int idx);

/* Free memory used by vector (including strings) */
void destroyVector(Vector *v);
