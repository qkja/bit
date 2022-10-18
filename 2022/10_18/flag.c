#include <stdio.h>
#define PRINT_A 0x01
#define PRINT_B 0x02
#define PRINT_C 0x04
#define PRINT_D 0x08

void f(int flag)
{
  if(flag & PRINT_A) printf("hello A\n");
  printf("hello A\n");
  printf("hello A\n");
  printf("hello A\n");
}
int main()
{
  f(PRINT_A);
  return 0;
}
