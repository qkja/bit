/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-18 20:05:31
 * LastEditTime : 2022-11-18 20:22:56
 */
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string>

using namespace std;

int cnt = 0;
void handler(int signo)
{
  cout << "我是一个进程,刚刚获取了一个信号: " << signo << endl;
  cout << "cnt : " << cnt << endl;;
  exit(1);
}

int main()
{
  alarm(1); // 一秒之后 产生一个信号  会发送  一个SIGALRM
  signal(SIGALRM, handler); // 这里只是 设置

  while (1)
  {
    cnt++;
  }

  return 0;
}

// int main()
// {
//   alarm(1); // 一秒之后 产生一个信号  会发送  一个SIGALRM

//   int cnt = 0;
//   while (1)
//   {
//     cout << "hello : cnt " << cnt << endl;
//     cnt++;
//   }

//   return 0;
// }

// int main()
// {
//   signal(SIGABRT, handler); // 这里只是 设置

//   while (1)
//   {
//     sleep(1);
//     abort();
//   }

//   return 0;
// }
// int main()
// {
//   signal(2, handler); // 这里只是 设置

//   while (1)
//   {
//     raise(2);
//     sleep(1);
//   }

//   return 0;
// }

// void Usage(const string& proc)
// {
//   cout << "Usage:\n\t" << proc << " signo pid" << endl;
// }

// int main(int argc,char* argv[])
// {
//   if(argc != 3)
//   {
//     Usage(argv[0]);
//     exit(1);
//   }
//   // kill -9 1110
//   if(kill((pid_t)atoi(argv[2]), (pid_t)atoi(argv[1])) == -1)
//   {
//     cerr << "kill: " << strerror(errno) << endl;
//   }

//   return 0;
// }
