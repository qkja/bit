/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-18 16:30:37
 * LastEditTime : 2022-11-18 17:10:13
 */
#include <sys/types.h>
#include <wait.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
using namespace std;

void handler(int signo)
{
  cout << "我是一个进程 pid " << getpid() << ",刚刚获取了一个信号: " << signo << endl;
}

int main()
{
  pid_t id = fork();
  if (id == 0)
  {
    int a = 0;
    a/=0;
    exit(1);
  }
  int status = 0;
  pid_t ret = waitpid(id, &status, 0);
  if (ret > 0)
  {
    cout << "推出码     " << ((status >> 8) & 0xFF) << endl;
    cout << "core dump  " << ((status >> 7) & 0x1) << endl;
    cout << "退出信号   " << ((status)&0x7F) << endl;
  }
  return 0;
}


// int main()
// {
//   pid_t id = fork();
//   if (id == 0)
//   {
//     int *p = nullptr;
//     *p = 20; // 野指针
//     exit(1);
//   }
//   int status = 0;
//   pid_t ret = waitpid(id, &status, 0);
//   if (ret > 0)
//   {
//     cout << "推出码     " << ((status >> 8) & 0xFF) << endl;
//     cout << "core dump  " << ((status >> 7) & 0x1) << endl;
//     cout << "退出信号   " << ((status)&0x7F) << endl;
//   }
//   return 0;
// }

// int main()
// {
//   try
//   {
//     while (1)
//     {
//       int a = 10;
//       int b = 0;
//       if (b == 0)
//       {
//         throw "除零错误";
//       }
//       a /= b;
//     }
//   }
//   catch (const char *&e)
//   {
//     std::cerr << e << '\n';
//   }
//   printf("---------------\n");
//   return 0;
// }

// int main()
// {

//   for (int i = 0; i < 31; i++)
//     signal(i + 1, handler);
//   int a = 10;
//   a /= 0;
//   return 0;
// }

// void handler(int signo)
// {
//   cout << "我是一个进程 pid " << getpid() <<",刚刚获取了一个信号: " << signo << endl;
//   exit(1);
// }

// int main()
// {

//  for(int i = 0; i < 31;i++)
//    signal(i+1, handler);

// int* p = nullptr;
// *p = 10;
//  return 0;
// }

// int main()
// {

//  for(int i = 0; i < 31;i++)
//    signal(i+1, handler);

//  int arr[15];
//  arr[19] = 0;
//  return 0;
// }

// int main()
// {

//  for(int i = 0; i < 31;i++)
//    signal(i+1, handler);

//  int a = 10;
//  a /= 0;
//  return 0;
// }

// int main()
// {
//   int a = 10;
//   a /= 0;

//   return 0;
// }

// int main()
// {
//   while (1)
//   {
//     sleep(1);
//     cout << "pid : " << getpid() << endl;
//   }

//   return 0;
// }

// int main()
// {
//   try
//   {
//     int a = 0;
//     if(a == 0)
//       throw "异常";
//   }
//   catch(const char* e)
//   {
//     cout << e << endl;
//   }
//   return 0;
// }

// void handler(int a)
//{
//   cout <<a <<endl;
// }
// int main()
//{
//
//   for(int i = 0; i < 31;i++)
//     signal(i+1, handler);
//
//   int a = 10;
//   a /= 0;
//
//   //  之前我们称 程序奔溃   楚玲错误
//   //  进程奔溃的本质 是进程收到 异常信号
//   //  OS 怎么知道除磷   状态寄存器 的标志位会发什么改变
//
//   // 进程崩溃了 一定会导致进程种植吗  我们做的是默认行为
//   //int a = 10;
//   //a /= 0;
//
//   return 0;
// }
//

// void handler(int signo)
// {
//   cout << "我是一个进程,刚刚获取了一个信号: " << signo << endl;
// }

// int main()
// {
//   for (size_t i = 1; i <= 31; i++)
//   {
//      signal(i, handler);
//   }

//   sleep(3);
//   cout << "进程已经设置完了捕捉" << endl;
//   sleep(3);
//   while (true)
//   {
//     cout << "我是一个正在运行的进程 pid : " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   signal(SIGINT, handler);
//   signal(SIGQUIT, handler);
//   sleep(3);
//   cout << "进程已经设置完了捕捉" << endl;
//   sleep(3);
//   while (true)
//   {
//     cout << "我是一个正在运行的进程 pid : " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   signal(SIGINT, handler);
//   sleep(3);
//   cout << "进程已经设置完了捕捉" << endl;
//   sleep(3);
//   while (true)
//   {
//     cout << "我是一个正在运行的进程 pid : " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   while (1)
//   {
//     cout << "hello bit" << endl;
//   }
//   uint32_t
//   return 0;
// }

// int main()
// {
//   while (1)
//   {
//     sleep(1);
//   }
//   return 0;
// }
