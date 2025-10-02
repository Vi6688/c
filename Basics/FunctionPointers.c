#include "../BasicTypes.h"
#include <stdio.h>

void print1(const string a, int b) {
  printf("Hii %s this is function %d", a, b);
  newline
}

void print2(const string a, int b) {
  printf("Hii %s this is function %d", a, b);
  newline
}

int process(int x, int (*func)(int)) { return func(x); }
int square(int x) { return x * x; }
int cube(int x) { return x * x * x; }

int main() {
  string a = "vijay";
  void (*greet)(const string, int);
  greet = print1;
  greet(a, 1);
  greet = print2;
  greet(a, 2);

  newline printf("Starting the square and cube using the function call");
  newline printf("Response for square of 2: is %d", process(2, square));
  newline printf("Response for cube of 2: is %d", process(1000, cube));
  newline return 0;
}