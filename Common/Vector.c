#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

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
Vector *createVector(void) {
    Vector *v = newAlloc(sizeof(Vector));
    v->size = 0;
    v->capacity = 4;
    v->data = newAlloc(v->capacity * sizeof(VectorElement));
    return v;
}

static void resizeVector(Vector *v) {
    v->capacity *= 2;
    v->data = newReAlloc(v->data, v->capacity * sizeof(VectorElement));
}

void appendInt(Vector *v, int val) {
    if (v->size >= v->capacity) resizeVector(v);
    v->data[v->size].type = TYPE_INT;
    v->data[v->size].data.i = val;
    v->size++;
}

void appendDouble(Vector *v, double val) {
    if (v->size >= v->capacity) resizeVector(v);
    v->data[v->size].type = TYPE_DOUBLE;
    v->data[v->size].data.d = val;
    v->size++;
}

void appendString(Vector *v, const char *val) {
    if (v->size >= v->capacity) resizeVector(v);
    v->data[v->size].type = TYPE_STRING;
    v->data[v->size].data.s = strdup(val);
    v->size++;
}

VectorElement getElement(Vector *v, int idx) {
    if (idx < 0 || (size_t)idx >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return v->data[idx];
}
