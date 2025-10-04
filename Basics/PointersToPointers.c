#include "../BasicTypes.h"
#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int **ptr, int size) {
  *ptr = (malloc(size * sizeof(int)));
}
int main() {
  int a = 10;
  int *pa = &a;
  int **ppa = &pa;
  printf("Response from the value a   : %d", a);
  newline printf("Response from the value pa  : %d", *pa);
  newline printf("Response from the value ppa : %d", **ppa);
  newline **ppa = 20;
  printf("Response from the value a   : %d", a);
  newline printf("Response from the value pa  : %d", *pa);
  newline printf("Response from the value ppa : %d", **ppa);
  newline

      int *arr = NULL;
  allocateMemory(&arr, 5);
  for (int i = 0; i < 5; i++)
    arr[i] = i * 10;
  for (int i = 0; i < 5; i++)
    printf("%d ", arr[i]);
}