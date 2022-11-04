/**
* User: Qkj
* Description: 学习标记位的思想
* Date: 2022-11-04
* Time: 20:56
*/

#include <stdio.h>

#define PRINT_A 0x1   // 0000 0001
#define PRINT_B 0x2   // 0000 0010
#define PRINT_C 0x4   // 0000 0100
#define PRINT_D 0x8   // 0000 1000

#define PRINT_DEL 0x0   // 0000 0000

void Show(int flags)
{
  if(flags & PRINT_A)
    printf("hello A\n");

  if(flags & PRINT_B)
    printf("hello B\n");

  if(flags & PRINT_C)
    printf("hello C\n");

  if(flags & PRINT_D)
    printf("hello D\n");

  if(flags == PRINT_DEL)
    printf("hello Default\n");
}

int main()
{
  Show(PRINT_DEL);
  printf("\n");

  Show(PRINT_A);
  printf("\n");
  
  Show(PRINT_A | PRINT_B);
  printf("\n");

  Show(PRINT_A | PRINT_B | PRINT_C);
  printf("\n");

  Show(PRINT_A | PRINT_B | PRINT_C | PRINT_D);
  printf("\n");
  return 0;
}
