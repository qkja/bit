#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

// 定义一个条件变量
pthread_cond_t cond;
// 定义一个互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 定义一个全局退出变量
volatile bool quit = false;
void *waitCommand(void *args)
{
  while (!quit)
  {
    // 让所有的线程等待被唤醒 注意锁的使用还没开始
    // 所有的线程都会在这里等着,给我排队.等着一个一个被叫醒
    pthread_cond_wait(&cond, &mutex);
    cout << "thread id  " << pthread_self() << "  running" << endl;
  }

  cout << "thread id  " << pthread_self() << "  end" << endl;
}

int main()
{
  pthread_cond_init(&cond, nullptr);

  pthread_t t1, t2, t3;
  pthread_create(&t1, nullptr, waitCommand, nullptr);
  pthread_create(&t2, nullptr, waitCommand, nullptr);
  pthread_create(&t3, nullptr, waitCommand, nullptr);

  while (true)
  {
    //  控制
    char n = 0;

    cout << "请输入你的commmand: ";
    cin >> n; // cin cout 交叉使用缓冲区会被强制刷新
    if (n == 'n')
    {
      // cout << "aaaaaaaaaaaa" << endl;
      // 唤醒一个线程
      pthread_cond_signal(&cond);
    }
    else
    {
      quit = true;
      break;
    }
    sleep(1);
  }

  // 退出的时候 吧所有的线程取消
  // 2.先唤醒才取消 有问题
  pthread_cond_broadcast(&cond);
  pthread_cancel(t1);
  pthread_cancel(t2);
  pthread_cancel(t3);

  // 1. 先取消在唤醒 有问题
  //pthread_cond_broadcast(&cond);

  pthread_join(t1, nullptr);
  pthread_join(t2, nullptr);
  pthread_join(t3, nullptr);

  pthread_cond_destroy(&cond);
  return 0;
}

// int cnt = 100;
// void *callback1(void *args)
// {

//   while (1)
//   {
//     pthread_mutex_lock(&mutex);
//     pthread_mutex_lock(&mutex);// 脑子抽了
//     cout << "count " << cnt-- << std::endl;
//     pthread_mutex_unlock(&mutex);

//     sleep(1);
//   }

// }

// int main()
// {
//   pthread_t t1;
//   pthread_create(&t1, nullptr, callback1, (void *)"thread1");
//   pthread_join(t1, nullptr);
//   return 0;
// }