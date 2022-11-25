/**
 * Author       : Qkj
 * Description  : 线程控制
 * Date         : 2022-11-24 22:50:06
 * LastEditTime : 2022-11-25 14:00:40
 */
// linux 是存在线程的,只不过我们不谈
// 里面都是什么东西  是寄存器
#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;
int a = 0;
int tickets = 10000; // 抢票
void *getTickets(void *args)
{
  const char *name = (char *)args;
  while (true)
  {
    // a++;
    if (tickets > 0) // 这里面有问题
    {
      usleep(1000); // 微妙

      // 抢票
      cout << name << "  抢到了票, 票号是 " << tickets << endl;
      tickets--;
      //等下给他加锁
      // a++;
    }
    else
    {
      cout << name << "  没抢到了票 " << endl;
      break;
    }
  }
  return nullptr;
}

int main()
{
  pthread_t tid1 = 0;
  pthread_t tid2 = 0;
  pthread_t tid3 = 0;
  pthread_t tid4 = 0;
  pthread_create(&tid1, nullptr, getTickets, (void *)"thread1");
  pthread_create(&tid2, nullptr, getTickets, (void *)"thread2");
  pthread_create(&tid3, nullptr, getTickets, (void *)"thread3");
  pthread_create(&tid4, nullptr, getTickets, (void *)"thread4");

  pthread_join(tid1, nullptr);
  pthread_join(tid2, nullptr);
  pthread_join(tid3, nullptr);
  pthread_join(tid4, nullptr);
  cout << "抢票完成" << endl;
  // cout << a<<endl;
  return 0;
}

// void* callback(void* argc)
// {
// }

// int main()
// {
//   pthread_t tid=0;
//   // 这个就是一个地址
//   pthread_create(&tid, nullptr, callback, (void*)"thread");

//   // 上面说了  线程有自己的  东西
//   // 那么pcb
//   // 这个是   join出来的   他就像是malloc出来的空间
//   // 还是没有谈   pthread_t
//   // 我们要不要加载动态库到内存里面呢
//   return 0;
// }

// int main()
// {
//   // 创建
//   // 使用
//   // 等待
//   // tid 非常大 这个究竟是什么  -- 暂时放着    格式打印 16进制

//   // 什么叫做获取线程id,他和那个参数有关
//   return 0;
// }

// 线程分离