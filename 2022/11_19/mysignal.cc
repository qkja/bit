/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-19 14:10:29
 * LastEditTime : 2022-11-19 14:22:50
 */
#include <iostream>
using namespace std;

int main()
{
  const int a = 10;
  cout << a << endl;
  int* p = (int*)&a;
  *p = 100;
  cout << a << endl;
  cout << *p << endl;
  return 0;
}

/*
子进程发送   17 好信号 退出时(暂停,继续运行时  暂停和  s态是一样吗)
*/

// 如何赞成 暂停进程
// 继续  18



// #include <signal.h>
// #include <stdio.h>
// #include <unistd.h>
// // 认识  volatile  关键字
// int falgs  = 0;
// void hander(int a)
// {
//   printf("得到\n", a);
//   falgs = 1;
// }
// int main()
// {
//   int a = 10;
//   signal(2, hander);
//   printf("------------\n");
//   a = 0;
//   while (!falgs)
//   {
//     a++;
//     sleep(1);
//   }
//   printf("%d", a);
//   return 0;
// }

// 这里是  volatile  和  const一样
// int main()
// {
//   // volatile 
//   while (!falgs);
//   return 0;
// }

// 我们需要看一下 捕捉函数的流程
// 认识另外的信号捕捉
// int main()
// {

//   // struct sigaction
//   // {
//   //   void (*sa_handler)(int);
//   //   void (*sa_sigaction)(int, siginfo_t *, void *); // 实时信号
//   //   sigset_t sa_mask;                               // 这个是什么
//   //   int sa_flags;
//   //   void (*sa_restorer)(void);
//   // };
//   return 0;
// }