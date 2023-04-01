/**
 * User: Qkj
 * Description:
 * Date: 2023-04-01
 * Time: 22:55
 */

#include "util.hpp"
#include <string>
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace Util;

// int main()
// {
//   SetNonBlock(0);
//   char buffer[1024];
//   while (true)
//   {
//     buffer[0] = 0;
//     int n = scanf("%s", buffer);
//     if (-1 == n)
//     {
//       cout << "errno " << errno << "desc " << strerror(errno) << endl;
//     }
//     cout << "刚刚获取的字符# " << buffer << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   SetNonBlock(0);
//   while (true)
//   {
//     string s;
//     cin >> s;
//     cout << "刚刚获取的字符# " << s << endl;
//     sleep(1);
//   }

//   return 0;
// }