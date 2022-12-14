#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

void handler(int signo)
{
  cout << "我是一个进程 pid " << getpid() << ",刚刚获取了一个信号: " << signo << endl;
}
void showPending(const sigset_t &pendings)
{
  // 如何显式
  for (size_t i = 1; i <= 31; i++)
  {
    if (sigismember(&pendings, i) == 1)
    {
      cout << "1";
    }
    else
    {
      cout << "0";
    }
  }
  cout << endl;
}

// int main()
// {
//   cout << "pid : " << getpid() << std::endl;
//   sigset_t bsig, obsig;

//   sigemptyset(&bsig);  // 清空当前信号集
//   sigemptyset(&obsig); // 清空当前信号集

//   for (int i = 1; i <= 31; i++)
//   {
//     sigaddset(&bsig, i);
//     signal(i, handler);
//   }

//   sigprocmask(SIG_SETMASK, &bsig, &obsig);
//   sigset_t pendings;
//   int cnt = 0;
//   while (true)
//   {
//     sigemptyset(&pendings); // 清空当前信号集
//     if (sigpending(&pendings) == 0)
//     {
//       showPending(pendings);
//     }
//     sleep(1);
//     cnt++;
//     if (cnt == 15)
//     {
//       sigset_t s;
//       sigemptyset(&s);
//       sigaddset(&s, 2);
//       sigprocmask(SIG_UNBLOCK, &s, nullptr);
//     }
//   }

//   return 0;
// }