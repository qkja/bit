/**
 * User: Qkj
 * Description:
 * Date: 2023-03-18
 * Time: 10:56
 */
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

using namespace std;

// 设置理念,由于 屏幕是临界资源,
// 我们呢应该是一个是一个锁.想一想,是不是可以可以用一个条件变量完成
// A->打印, --> 唤醒

// 条件变量
pthread_cond_t con = PTHREAD_COND_INITIALIZER; // 条件变量的初始化
struct Test
{
  pthread_mutex_t *pMutex;
  string str;
};
void *Print(void *arg)
{
  struct Test *p = (struct Test *)arg;
  while (true)
  {
    pthread_cond_wait(&con, p->pMutex);
    cout << p->str << std::endl;
  }
}

int main()
{
  // 拿到一一把锁
  pthread_mutex_t mut;
  // 初始化锁
  pthread_mutex_init(&mut, nullptr);
  pthread_t a;
  pthread_t b;
  struct Test aPrint;
  aPrint.pMutex = &mut;
  aPrint.str = "我是线程A;";
  struct Test bPrint;
  bPrint.pMutex = &mut;
  bPrint.str = "我是线程B;";

  // 创建线程
  pthread_create(&a, nullptr, Print, (void *)&aPrint);
  pthread_create(&a, nullptr, Print, (void *)&bPrint);

  // 唤醒条件变量
  while (true)
  {
    pthread_cond_signal(&con);
    sleep(1);
  }
  

  pthread_join(a, nullptr);
  pthread_join(b, nullptr);
  return 0;
}

// pthread_mutex_t mutex;

// int tickets = 1000;

// void *getTickets(void *args)
// {
//   const char *name = static_cast<const char *>(args);

//   while (true)
//   {
//     pthread_mutex_lock(&mutex);
//     if (tickets > 0)
//     {
//       usleep(10000);
//       cout << name << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;
//       sleep(1);
//       pthread_mutex_unlock(&mutex);
//     }
//     else
//     {
//       // 票抢到几张,就算没有了呢？0
//       cout << name << "] 已经放弃抢票了,因为没有了..." << endl;
//       pthread_mutex_unlock(&mutex);

//       break;
//     }
//   }

//   return nullptr;
// }

// int main()
// {
//   // 初始化锁
//   pthread_mutex_init(&mutex, nullptr);

//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_t tid4;
//   pthread_create(&tid1, nullptr, getTickets, (void *)"thread 1");
//   pthread_create(&tid2, nullptr, getTickets, (void *)"thread 2");
//   pthread_create(&tid3, nullptr, getTickets, (void *)"thread 3");
//   pthread_create(&tid4, nullptr, getTickets, (void *)"thread 4");

//   int n = pthread_join(tid1, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid2, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid3, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid4, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   pthread_mutex_destroy(&mutex);
//   return 0;
// }

// void* callback(void* arg)
//{
//   const char* name = static_cast<char*>(arg);
//   while(1)
//   {
//     cout << "name " << name << " " << pthread_self() <<endl;
//     sleep(1);
//   }
// }
// int main()
//{
//   pthread_t pid;
//   pthread_create(&pid, nullptr, callback, (void*)"thread");
//
//   pthread_join(pid, nullptr);
//   return 0;
// }
