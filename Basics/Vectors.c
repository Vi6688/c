#include "Common/BasicTypes.h"
#include "Common/Memory.h"
#include <stdio.h>

int main() {
  int size = 10;
  IntVector a = newInt(size);
  loopI(size) { a[i] = i * 10; }
  loopI(size) { printf("Response of the value : %d", a[i]); newline }

  String b;
  b = "abcdef";
  printf("Response %s", b);
  newline
  destruct();
  return 0;
}