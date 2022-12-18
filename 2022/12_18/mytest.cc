#include <unistd.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <signal.h>
#include <string.h>
#include <assert.h>
using namespace std;

// void handler(int signo)
// {
//   assert(signo == 17);
//   while (true)
//   {
//     pid_t id = waitpid(-1, nullptr, WNOHANG); // -1 等待任意进程
//     if (id > 0)
//     {
//       cout << "父进程等待成功 child id " << id << endl;
//       // break;
//     }
//     else
//     {
//       break;
//     }
//   }
// }

int main()
{
  signal(SIGCHLD, SIG_IGN);

  pid_t id = fork();
  if (id == 0)
  {
    int cnt = 10;
    while (cnt)
    {
      cout << "我是子进程 pid " << getpid()
           << " cnt " << cnt << endl;
      sleep(1);
      cnt--;
    }
    cout << "我是子进程 进入僵尸" << endl;
    return 1;
  }

  while (true)
  {
    cout << "我是父进程 pid " << getpid() << endl;
    sleep(1);
  }

  return 0;
}

// void handler(int signo)
// {
//   assert(signo == 17);
//   cout << "子进程确实退出了 sig  "
//        << signo << "  我是父进程 " << getpid() << endl;

//   pid_t id = waitpid(-1, nullptr, 0) >= 0; // -1 等待任意进程
//   if (id > 0)
//   {
//     cout << "父进程等待成功 child id " << id << endl;
//   }
// }

// void handler(int signo)
// {
//   assert(signo == 17);
//   while (true)
//   {
//     pid_t id = waitpid(-1, nullptr, WNOHANG); // -1 等待任意进程
//     if (id > 0)
//     {
//       cout << "父进程等待成功 child id " << id << endl;
//      // break;
//     }
//     else
//     {
//       break;
//     }
//   }
// }

// int main()
// {
//   for (size_t i = 0; i < 10; i++)
//   {

//     pid_t id = fork();
//     if (id == 0)
//     {
//       int cnt = 10;
//       while (cnt)
//       {
//         cout << "我是子进程 pid " << getpid()
//              << " cnt " << cnt << endl;
//         sleep(1);
//         cnt--;
//       }
//       cout << "我是子进程 进入僵尸" << endl;
//       return 1;
//     }
//   }

//   signal(17, handler);

//   while (true)
//   {
//     cout << "我是父进程 pid " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   pid_t id = fork();
//   if (id == 0)
//   {
//     int cnt = 10;
//     while (cnt)
//     {
//       cout << "我是子进程 pid " << getpid()
//            << " cnt " << cnt << endl;
//       sleep(1);
//       cnt--;
//     }
//     cout << "我是子进程 进入僵尸" << endl;
//     return 1;
//   }
//   signal(17, handler);

//   while (true)
//   {
//     cout << "我是父进程 pid " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   pid_t id = fork();
//   if (id == 0)
//   {
//     int cnt = 10;
//     while (cnt)
//     {
//       cout << "我是子进程 pid " << getpid()
//            << " cnt " << cnt << endl;
//       sleep(1);
//       cnt--;
//     }
//     cout << "我是子进程 进入僵尸" << endl;
//     return 1;
//   }

//   if (waitpid(id, nullptr, 0) >= 0)
//   {
//     cout << "父进程等待成功" << endl;
//   }

//   return 0;
// }

// void handler(int signo)
// {
//   assert(signo == 17);
//   while (true)
//   {
//     pid_t id = waitpid(-1, nullptr, WNOHANG) >= 0; // -1 等待任意进程
//     if (id > 0)
//     {
//       cout << "父进程等待成功 child id " << id << endl;
//     }
//     else
//     {
//       break;
//     }
//   }
// }

// int main()
// {
//   for (size_t i = 0; i < 10; i++)
//   {

//     pid_t id = fork();
//     if (id == 0)
//     {
//       int cnt = 10;
//       while (cnt)
//       {
//         cout << "我是子进程 pid " << getpid()
//              << " cnt " << cnt << endl;
//         sleep(1);
//         cnt--;
//       }
//       cout << "我是子进程 进入僵尸" << endl;
//       return 1;
//     }
//   }

//   signal(17, handler);

//   while (true)
//   {
//     cout << "我是父进程 pid " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   pid_t id = fork();
//   if (id == 0)
//   {
//     int cnt = 10;
//     while (cnt)
//     {
//       cout << "我是子进程 pid " << getpid()
//            << " cnt " << cnt << endl;
//       sleep(1);
//       cnt--;
//     }
//     cout << "我是子进程 进入僵尸" << endl;
//     return 1;
//   }
//   // signal(17, handler);

//   if (waitpid(id, nullptr, 0) >= 0)
//   {
//     cout << "父进程等待成功" << endl;
//   }

//   // while (true)
//   // {
//   //   cout << "我是父进程 pid " << getpid() << endl;
//   //   sleep(1);
//   // }

//   return 0;
// }

// int main()
// {
//   pid_t id = fork();
//   if (id == 0)
//   {

//     while (true)
//     {
//       /* code */
//       cout << "我是子进程 pid " << getpid() << endl;
//       sleep(1);
//     }
//     cout << "我是子进程 我要推出了" << endl;
//     return 1;
//   }
//   signal(17, handler);
//   while (true)
//   {
//     cout << "我是父进程 pid " << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// #include <unistd.h>
// #include <stdio.h>
// #include <signal.h>
// #include <string.h>

// volatile int flags = 0;

// void handler(int signo)
// {
//   flags = 1;
//   printf("更改flags: 0->1\n");
// }

// int main()
// {
//   // 可以同时修饰一个变量吗？？
//   // 含义冲突吗，该变量代表什么含义？

//   signal(2, handler);

//   while (!flags);
//   printf("进程是正常退出的!\n");

//   return 0;
// }

// void hander(int signo)
// {
//   std::cout << "我捕获了一个信号 : " << signo << std::endl;

// }

// void handler(int signo)
// {
//   cout << "获取到一个信号,信号的编号是: " << signo << endl;
//   sigset_t pending;
//   // 增加handler信号的时间,永远都会正在处理2号信号！
//   while (true)
//   {
//     cout << "." << endl;
//     sigpending(&pending);
//     for (int i = 1; i <= 31; i++)
//     {
//       if (sigismember(&pending, i))
//         cout << '1';
//       else
//         cout << '0';
//     }
//     cout << endl;
//     sleep(1);
//   }
// }

// int main()
// {
//   struct sigaction ac;
//   struct sigaction oldac;
//   memset(&ac, 0, sizeof(struct sigaction));
//   memset(&oldac, 0, sizeof(struct sigaction));

//   ac.sa_handler = handler;   // 自定义信号动作
//   sigemptyset(&ac.sa_mask);  // 置空
//   sigaddset(&ac.sa_mask, 3); // 添加 3号信号被阻塞
//   sigaction(2, &ac, &oldac); // 捕捉2号信号

//   while (1)
//   {
//     sleep(1);
//   }

//   return 0;
// }