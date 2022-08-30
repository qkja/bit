#include <stdio.h>
#define M 100
int main()
{
  // 打印一个宏
  printf("宏 %d\n",M);

#ifdef A
  printf("hello A\n");
#else 
  printf("对不起，你没有定义 A\n");
#endif
  return 0;
}
