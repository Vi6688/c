#include "../Common/BasicTypes.h"
#include "../Common/Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* unions only hold the one type at a time
the memory size is of the largest dataType includes inside the union
*/

union data {
  int max;
  char s;
  double a;
};

int main() {
  union data a;
  a.max = 40;
  a.s = 'a';
  a.a = 10000;
  printf("Response : %d%c", a.max, a.s);
  newline printf("Response %lld", sizeof(a));
  printf("Response %lf", a.a);
  newline
}