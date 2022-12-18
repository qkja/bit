#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <string.h>
using namespace std;

// void hander(int signo)
// {
//   std::cout << "我捕获了一个信号 : " << signo << std::endl;

// }

void handler(int signo)
{
  cout << "获取到一个信号,信号的编号是: " << signo << endl;
  sigset_t pending;
  // 增加handler信号的时间,永远都会正在处理2号信号！
  while (true)
  {
    cout << "." << endl;
    sigpending(&pending);
    for (int i = 1; i <= 31; i++)
    {
      if (sigismember(&pending, i))
        cout << '1';
      else
        cout << '0';
    }
    cout << endl;
    sleep(1);
  }
}

int main()
{
  struct sigaction ac;
  struct sigaction oldac;
  memset(&ac, 0, sizeof(struct sigaction));
  memset(&oldac, 0, sizeof(struct sigaction));

  ac.sa_handler = handler;   // 自定义信号动作
  sigemptyset(&ac.sa_mask);  // 置空
  sigaddset(&ac.sa_mask, 3); // 添加 3号信号被阻塞
  sigaction(2, &ac, &oldac); // 捕捉2号信号

  while (1)
  {
    sleep(1);
  }

  return 0;
}