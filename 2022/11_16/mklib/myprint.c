/**
* User: Qkj
* Description: 
* Date: 2022-11-16
* Time: 19:06
*/
#include "myprint.h"
void Print(const char* msg)
{
  assert(msg);
  printf("%s : %lld\n", msg, (long long)time(NULL));
}
