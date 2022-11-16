/**
* User: Qkj
* Description: 制作库
* Date: 2022-11-16
* Time: 18:58
*/
#include "mymath.h"

int addToVal(int from, int to)
{
  assert(from<=to);
  int result = 0;
  int i = 0;
  for(i = from; i <= to; i++)
  {
    result += i;
  }
  return result;
}
