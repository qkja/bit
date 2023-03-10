#include <iostream>
#include "util.hpp"
using namespace std;
using namespace Util;
int main()
{
  char buffer[1024];
  SetNonBlock(0); // 把标准输入设置成非阻塞
  while (true)
  {
    buffer[0] = '\0';
    scanf("%s", buffer);
    cout << "刚刚获取的 " << buffer << std::endl; 
    sleep(1);
  }

  return 0;
}

// int main()
// {
//   string s;
//   char buffer[1024];
//   SetNonBlock(0); // 把标准输入设置成非阻塞
//   while (true)
//   {
//     buffer[0] = '\0';
//     scanf("%s", buffer);
//     cout << "刚刚获取的 " << buffer;
//     sleep(1);
//   }

//   return 0;
// }