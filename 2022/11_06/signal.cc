/**
 * User: Qkj
 * Description: 信号量
 * Date: 2022-11-06
 * Time: 09:38
 */

#include <iostream>
#include <unistd.h>

using namespace std;











// int main()
// {
//   try
//   {

//     while (1)
//     {
//       int a = 10;
//       int i = 0;
//       if (0 == i)
//         throw "除磷错误";
//       a /= i;
//     }
//   }
//   catch (const std::exception &e)
//   {
//     std::cerr << e.what() << '\n';
//   }

//   return 0;
// }

// int main()
// {
//   while(1)
//   {
//     cout << "hello signal" << endl;
//     sleep(1);
//   }

//   return 0;
// }

// 后台进程   要变成 前台进程   不影响我们打印
// 后台进程 在自己运行结束后 会自己销毁吗  猜测-- 会的
//
// 进程 是如何记住信号的
// 在哪记住的             -- 位图