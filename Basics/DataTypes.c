#include "../Common/BasicTypes.h"
#include <stdio.h>


int main() {

  int a = 0;
  float b = 0;
  char c = 'c';
  double d = 0;
  char *s[100];

  scanf("%c",*s);
  printf("Size of int : %d\n", sizeof(int));
  printf("Size of float : %d\n",sizeof(float));
  printf("Size of char : %d\n",sizeof(char));
  printf("Size of double : %d\n",sizeof(double));
  printf("Size of String : %d\n",sizeof(s));

  return 0;
}