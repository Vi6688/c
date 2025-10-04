#include "Common/BasicTypes.h"
#include "Common/Vector.h"
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    DoubleList *dlist = createDoubleList();

    // Measure append time
    start = clock();
    for (int i = 0; i < 100000; i++) {
        appendDouble(dlist, i);
    }
    end = clock();
    printf("C append time: %.10f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Measure access time
    start = clock();
    for (int i = 0; i < 100000; i++) {
        volatile double x = dlist->dataAt(dlist, i);  // volatile to avoid optimization
    }
    end = clock();
    printf("C access time: %.10f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}