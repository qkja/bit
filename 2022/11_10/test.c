/**
* User: Qkj
* Description: 
* Date: 2022-11-10
* Time: 10:48
*/
#include <stdio.h>

int main()
{
  int a = 0;
  while(scanf("%d", &a) != EOF)
  {
    if(a == 0)
      break;
    printf("%d\n",a);
  }
  return 0;
}
