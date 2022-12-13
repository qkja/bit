#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

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

void handler(int signo)
{
  cout << "我是一个进程 pid " << getpid() << ",刚刚获取了一个信号: " << signo << endl;
  // exit(1);
}

int main()
{
  cout << "pid : " << getpid() << std::endl;
  sigset_t bsig, obsig;

  sigemptyset(&bsig);  // 清空当前信号集
  sigemptyset(&obsig); // 清空当前信号集

  for (int i = 1; i <= 31; i++)
  {
    sigaddset(&bsig, i);
    signal(i, handler);
  }

  sigprocmask(SIG_SETMASK, &bsig, &obsig);
  sigset_t pendings;
  int cnt = 0;
  while (true)
  {
    sigemptyset(&pendings); // 清空当前信号集
    if (sigpending(&pendings) == 0)
    {
      showPending(pendings);
    }
    sleep(1);
    cnt++;
    if (cnt == 15)
    {
      sigprocmask(SIG_SETMASK, &obsig, nullptr);
      //break;
    }
  }

  return 0;
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
//       //break;
//     }
//   }

//   return 0;
// }

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
//     if(cnt == 10)
//     {
//       sigprocmask(SIG_SETMASK,  &obsig, nullptr);
//       break;
//     }
//   }

//   return 0;
// }

// void showPending(const sigset_t &pendings)
// {
//   // 如何显式
//   for (size_t i = 1; i <= 31; i++)
//   {
//     if (sigismember(&pendings, i) == 1)
//     {
//       cout << "1";
//     }
//     else
//     {
//       cout << "0";
//     }
//   }
//   cout << endl;
// }

// int main()
// {
//   // 开始的时候没有任何信号bingbi

// // 看不到信号   - 2号信号   捕捉一下

//   sigset_t pendings;
// // 在捕捉哪里看 whie
//   while (true)
//   {
//     sigemptyset(&pendings); // 清空
//     if (sigpending(&pendings) == 0)
//     {
//       showPending(pendings);
//     }
//     sleep(1);
//     /* code */
//   }

//   return 0;
// }

// int main()
// {
//   sigset_t newId = 0x01;
//   sigset_t newId = 0;
//   sigprocmask();
//    return 0;
// }
// int main()
// {

//   int *p = nullptr;
//   *p = 20; // 野指针
//   exit(1);

//   return 0;
// }

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

// void handler(int signo)
// {
//   cout << "我是一个进程 pid " << getpid() << ",刚刚获取了一个信号: " << signo << endl;
//   exit(1);
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
//   cout << "我是一个进程,刚刚获取了一个信号: " << signo << endl;
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
//   while (1)
//   {
//     cout << "hello bit" << endl;
//     sleep(1);
//   }
//   return 0;
// }

// int main()
// {
//   while (1)
//   {
//   }
//   return 0;
// }

// int main()
// {
//   while (1)
//   {
//     cout << "hello bit" << endl;
//     sleep(1);
//   }
//   return 0;
// }

// int main()
// {

//   return 0;
// }