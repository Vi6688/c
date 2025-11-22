#pragma once
#include "BasicTypes.h"

typedef struct MapEntry {
  string key;
  voidPtr value;
} MapEntry;

typedef struct MapStruct {
  MapEntry *entries; // List of MapEntry
  size_t size;    // Current number of entries
  size_t capacity; // Allocated capacity
} MapStruct;
typedef MapStruct *Map;

Map createMap();
voidPtr mapGet  (Map map, string key);
Boolean mapPut (Map map, string key, voidPtr value);
Boolean mapRemove (Map map, string key);
Map destroyMap(Map map);