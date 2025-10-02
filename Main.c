#include "BasicTypes.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

num sumOfArray(const num* a,const size_t size)
{
  num sum = 0;
  for (int i = 0;i<size; i++) {
    sum += a[i];
  }
  return sum;
}
int main() {
  size_t size =  10;
  num array[size];
  loopI(size)
  {
    array[i] = i*100;
    printf("Value : %d",i);
  }
  num sum = sumOfArray(array,size);
  printf("Sum of the array is %0.5f",sum);
  return 0;
}