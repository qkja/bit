#include <stdio.h>

int add(int a)
{
  int sum = 0;
  int i = 0;
  for(i=0;i<a;i++)
  {
    sum += i;
  }

  return sum;
}

int main()
{
  int x = 10;
  int total = add(x);

  printf("%d\n",total);
  return 0;
}
