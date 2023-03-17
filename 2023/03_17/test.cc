/**
 * User: Qkj
 * Description:
 * Date: 2023-03-17
 * Time: 17:02
 */
#include <signal.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
using namespace std;
void sigcb(int sig)
{
  cout << "捕捉一个信号 " << sig << endl;
}

int main()
{
  signal(2, sigcb);
  signal(40, sigcb);
  sigset_t bsig;
  sigset_t obsig;
  sigemptyset(&bsig);
  sigemptyset(&obsig);

  // 添加 2号和40号
  sigaddset(&bsig, 2);
  sigaddset(&bsig, 40);

  // 替换当前内核的信号集
  sigprocmask(SIG_SETMASK, &bsig, &obsig);
  while (1)
  {
    cout << "我是 main" << getpid() << endl;
    sleep(1);
  }

  return 0;
}

// int main()
// {
//   struct sigaction ac;
//   struct sigaction oldac;

//   memset(&ac, 0, sizeof(ac));
//   memset(&oldac, 0, sizeof oldac);
//   ac.sa_handler = sigcb;
//   sigemptyset(&ac.sa_mask);

//   sigaction(SIGINT, &ac, &oldac); // 设置动作
//   while (1)
//   {
//     cout << "我是 main" << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }

// void sigcb(int sig)
// {
//   cout << "捕捉一个信号 " << sig << endl;
// }
// int main()
// {
//   for (size_t i = 1; i <= 31; i++)
//   {
//     signal(i, sigcb);
//   }
//   while (1)
//   {
//     cout << "我是 main" << getpid() << endl;
//     sleep(1);
//   }

//   return 0;
// }
// #include <pthread.h>
// #include <iostream>
// #include <unistd.h>

// using namespace std;
// void *callback1(void *args)
// {
//   while (true)
//   {
//     cout << "我是新线程   " << (char *)args << "... " << endl;
//     sleep(1);
//   }
// }

// void *callback2(void *args)
// {
//   while (true)
//   {
//     cout << "我是新线程   " << (char *)args << "... " << endl;
//     sleep(1);
//   }
// }

// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_create(&tid1, nullptr, callback1, (void *)"thread1"); // 创建线程
//   pthread_create(&tid2, nullptr, callback2, (void *)"thread2"); // 创建线程

//   while (true)
//   {
//     cout << "我是主线程..." << endl;
//     sleep(1);
//   }

//   pthread_join(tid1, nullptr); // 等待线程
//   pthread_join(tid2, nullptr); // 等待线程

//   return 0;
// }
