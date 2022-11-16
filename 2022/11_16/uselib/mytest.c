/**
* User: Qkj
* Description: 
* Date: 2022-11-16
* Time: 20:58
*/
// 下面的方法太挫了 
//#include "./lib-static/include/mymath.h"
//#include "./lib-static/include/myprint.h"

// 我们就这们用
#include "mymath.h"
#include "myprint.h"

int main()
{
  int start = 0;
  int end = 100;
  int result = addToVal(start, end);
  printf("result : %d\n", result);

  Print("hello word");
  return  0;
}
