#include "Map.h"
#include "BasicTypes.h"
#include "Memory.h"
#include <stdio.h>
#include <string.h>

// ---------- Binary Search Helper ----------
static long mapBinarySearch(Map map, string key) {
    long left = 0;
    long right = (long)map->size - 1;

    while (left <= right) {
        long mid = (left + right) / 2;
        int cmp = strcmp(map->entries[mid].key, key);

        if (cmp == 0)
            return mid;       // key found
        else if (cmp < 0)
            left = mid + 1;   // key is greater → go right
        else
            right = mid - 1;  // key is smaller → go left
    }

    return -(left + 1);  
    // Not found → return negative insertion index
}

// ---------- Map Create ----------
Map createMap() {
    Map map = (Map)newAlloc(sizeof(MapStruct));
    if (!map) return NULL;

    map->entries = NULL;
    map->size = 0;
    map->capacity = 0;
    return map;
}

// ---------- Sorted Get ----------
voidPtr mapGet(Map map, string key) {
    if (!map || !key) return NULL;

    long idx = mapBinarySearch(map, key);
    if (idx >= 0) 
        return map->entries[idx].value;

    return NULL;
}

// ---------- Sorted Insert ----------
Boolean mapPut(Map map, string key, voidPtr value) {
    if (!map || !key) {
        printl("Map Key or Map pointer not valid");
        return false;
    }

    long pos = mapBinarySearch(map, key);

    if (pos >= 0) {
        // Key already exists → update value
        map->entries[pos].value = value;
        return true;
    }

    // Convert negative result into proper insertion index
    size_t insertIndex = (size_t)(-pos - 1);

    // Expand capacity if needed
    if (map->size >= map->capacity) {
        size_t newCapacity = (map->capacity == 0 ? 4 : map->capacity * 2);
        MapEntry *newEntries = (MapEntry *)newReAlloc(
            map->entries,
            newCapacity * sizeof(MapEntry)
        );

        if (!newEntries) return false;

        map->entries = newEntries;
        map->capacity = newCapacity;
    }

    // Shift items to make space for sorted insertion
    memmove(
        &map->entries[insertIndex + 1],
        &map->entries[insertIndex],
        (map->size - insertIndex) * sizeof(MapEntry)
    );

    // Insert new key & value
    map->entries[insertIndex].key = key;
    map->entries[insertIndex].value = value;
    map->size++;

    return true;
}

Map destroyMap(Map map) {
    if (!map) return NULL;

    for (size_t i = 0; i < map->size; i++) {
        freeAlloc(map->entries[i].key);
    }

    freeAlloc(map->entries);
    freeAlloc(map);

    return NULL;
}
