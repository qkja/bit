#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "log.hpp"
using namespace std;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int cnt = 100;
void *callback1(void *args)
{

  while (1)
  {
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex); // 脑子抽了
    cout << "count " << cnt-- << std::endl;
    pthread_mutex_unlock(&mutex);

    sleep(1);
  }
}

int main()
{
  pthread_t t1;
  pthread_create(&t1, nullptr, callback1, (void *)"thread1");
  pthread_join(t1, nullptr);
  return 0;
}
// int tickets = 1000;
// Mutex mutex;

// bool getTickets()
// {
//   bool ret = false;
//   Lock_GUARD l(&mutex); // 完成加锁  函数退出后自动析构解锁

//   if (tickets > 0)
//   {
//     usleep(100000);
//     cout << "thread  " << pthread_self() << " 抢到了票, 票的编号: " << tickets << endl;
//     tickets--;
//     ret = true;
//   }
//   return ret;
// }

// void *startRoutine(void *args)
// {
//   char *name = (char *)args;
//   while (true)
//   {
//     if (!getTickets())
//     {
//       break;
//     }
//     cout << name << "获得票成功" << endl;
//     sleep(1);
//   }
// }

// int main()
// {

//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_t tid4;

//   pthread_create(&tid1, nullptr, startRoutine, (void *)"thread1");
//   pthread_create(&tid2, nullptr, startRoutine, (void *)"thread2");
//   pthread_create(&tid3, nullptr, startRoutine, (void *)"thread3");
//   pthread_create(&tid4, nullptr, startRoutine, (void *)"thread4");

//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   pthread_join(tid3, nullptr);
//   pthread_join(tid4, nullptr);

//   return 0;
// }

// pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
// void *callback1(void *args)
// {
//   pthread_mutex_lock(&mutexA);
//   sleep(1);

//   pthread_mutex_lock(&mutexB);
//   while (1)
//   {
//     cout << "我是线程1" << std::endl;
//     sleep(1);
//   }

//   pthread_mutex_unlock(&mutexA);
//   pthread_mutex_unlock(&mutexB);
// }
// void *callback2(void *args)
// {
//   pthread_mutex_lock(&mutexB);
//   sleep(1);

//   pthread_mutex_lock(&mutexA);
//   while (1)
//   {
//     cout << "我是线程2" << std::endl;
//     sleep(1);
//   }

//   pthread_mutex_unlock(&mutexA);
//   pthread_mutex_unlock(&mutexB);
// }
// int main()
// {
//   pthread_t t1, t2;
//   pthread_create(&t1, nullptr, callback1, (void *)"thread1");
//   pthread_create(&t1, nullptr, callback2, (void *)"thread1");

//   pthread_join(t1, nullptr);
//   pthread_join(t2, nullptr);
//   return 0;
// }
// int tickets = 1000;
// Mutex mutex;

// bool getTickets()
// {
//   bool ret = false;
//   Lock_GUARD l(&mutex); // 完成加锁  函数退出后自动析构解锁

//   if (tickets > 0)
//   {
//     usleep(100000);
//     cout << "thread  " << pthread_self() << " 抢到了票, 票的编号: " << tickets << endl;
//     tickets--;
//     ret = true;
//   }
//   return ret;
// }

// void *startRoutine(void *args)
// {
//   char *name = (char *)args;
//   while (true)
//   {
//     if (!getTickets())
//     {
//       break;
//     }
//     cout << name << "获得票成功" << endl;
//     sleep(1);
//   }
// }

// int main()
// {

//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_t tid4;

//   pthread_create(&tid1, nullptr, startRoutine, (void *)"thread1");
//   pthread_create(&tid2, nullptr, startRoutine, (void *)"thread2");
//   pthread_create(&tid3, nullptr, startRoutine, (void *)"thread3");
//   pthread_create(&tid4, nullptr, startRoutine, (void *)"thread4");

//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   pthread_join(tid3, nullptr);
//   pthread_join(tid4, nullptr);

//   return 0;
// }

// struct mythread
// {
//   char name[100];
//   pthread_mutex_t *mutexp;
// };

// void *getTickets(void *args)
// {
//   struct mythread *p = (struct mythread *)args;
//   while (true)
//   {
//     pthread_mutex_lock(p->mutexp);
//     if (tickets > 0)
//     {
//       usleep(100000);
//       cout << p->name << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;

//       pthread_mutex_unlock(p->mutexp);
//     }
//     else
//     {
//       // 票抢到几张，就算没有了呢？0
//       cout << p->name << " 已经放弃抢票了，因为没有了..." << endl;
//       pthread_mutex_unlock(p->mutexp);

//       break;
//     }
//   }

//   return nullptr;
// }

// int main()
// {
//   pthread_mutex_t mutex;
//   pthread_mutex_init(&mutex, nullptr);

//   struct mythread *m = new mythread;
//   m->mutexp = &mutex;
//   strcpy(m->name, "测试");

//   pthread_t tid1;

//   pthread_create(&tid1, nullptr, getTickets, (void *)m);

//   int n = pthread_join(tid1, nullptr);
//   pthread_mutex_destroy(m->mutexp);
//   delete m;

//   return 0;
// }

// void *getTickets(void *args)
// {
//   const char *name = static_cast<const char *>(args);
//   pthread_mutex_lock(&mutex);

//   while (true)
//   {
//     if (tickets > 0)
//     {
//       usleep(10000);
//       cout << name << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;
//       pthread_mutex_unlock(&mutex);
//     }
//     else
//     {
//       // 票抢到几张，就算没有了呢？0
//       cout << name << "] 已经放弃抢票了，因为没有了..." << endl;
//       //pthread_mutex_unlock(&mutex);

//       break;
//     }
//   }

//   return nullptr;
// }

// void *getTickets(void *args)
// {
//   pthread_mutex_t *mutex_p = (pthread_mutex_t *)args;
//   while (true)
//   {
//     pthread_mutex_lock(mutex_p);
//     if (tickets > 0)
//     {
//       usleep(100000);
//       cout << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;

//       pthread_mutex_unlock(mutex_p);
//     }
//     else
//     {
//       // 票抢到几张，就算没有了呢？0
//       cout << " 已经放弃抢票了，因为没有了..." << endl;
//       pthread_mutex_unlock(mutex_p);

//       break;
//     }
//   }

//   return nullptr;
// }

// int main()
// {
//   static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//   pthread_t tid1;

//   pthread_create(&tid1, nullptr, getTickets, (void *)&mutex);

//   int n = pthread_join(tid1, nullptr);
//   cout << n << ":" << strerror(n) << endl;

//   return 0;
// }

// int main()
// {
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

// void *getTickets(void *args)
// {
//   const char *name = static_cast<const char *>(args);

//   while (true)
//   {

//     if (tickets > 0)
//     {
//       usleep(1000);
//       cout << name << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;

//       // other code
//       usleep(123); // 模拟其他业务逻辑的执行
//     }
//     else
//     {
//       // 票抢到几张，就算没有了呢？0
//       cout << name << "] 已经放弃抢票了，因为没有了..." << endl;
//       break;
//     }
//   }

//   return nullptr;
// }

// 如何理解exit？
// void *callback(void *args)
// {
//  // pthread_detach(pthread_self());
//   //cout << "线程分离" << endl;
//   int cnt = 50;
//   while (cnt)
//   {
//     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }

// }
// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_create(&tid1, nullptr, callback, (void *)"thread 1");
//   pthread_create(&tid2, nullptr, callback, (void *)"thread 2");
//   pthread_create(&tid3, nullptr, callback, (void *)"thread 3");

//   //sleep(1);
//   //  倾向于：让主线程，分离其他线程

//   pthread_detach(tid1);
//   pthread_detach(tid2);
//   pthread_detach(tid3);

//   int n = pthread_join(tid1, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid2, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid3, nullptr);
//   cout << n << ":" << strerror(n) << endl;

//   return 0;
// }

// void *startRoutine(void *args)
// {
//   pthread_t *ptid = (pthread_t *)args;
//   PTHREAD_CANCELED;
//   int cnt = 0;

//   while (true)
//   {
//     if (cnt == 5)
//     {
//       cout << "new thread been canceled" << endl;

//       pthread_cancel(*ptid);
//       break;
//     }
//     cnt++;
//     cout << "thread 正在运行..." << endl;
//     sleep(1);
//   }
// }
// int main()
// {

//   pthread_t t = pthread_self();
//   pthread_t tid;
//   int n = pthread_create(&tid, nullptr, startRoutine, (void *)&t);

//   (void)n;

//   sleep(30); // 代表main thread对应的工作

//   return 0;
// }

// void *startRoutine(void *args)
// {
//   while (true)
//   {
//     cout << "thread 正在运行..." << endl;
//     sleep(1);
//   }
// }
// int main()
// {

//   pthread_t tid;
//   int n = pthread_create(&tid, nullptr, startRoutine, (void *)"thread1");

//   (void)n;

//   sleep(3); // 代表main thread对应的工作
//   pthread_cancel(tid);
//   cout << "new thread been canceled" << endl;

//   void *ret = nullptr;     // void* -> 64 -> 8byte -> 空间
//   pthread_join(tid, &ret); // void **retval是一个输出型参数
//   cout << "main thread join success, ret: " << (long long)ret << endl;
//   sleep(1);
//   return 0;
// }

// int tickets = 10000; // 临界资源，可能会因为共同访问，可能会造成数据不一致问题。
// pthread_mutex_t mutex;

// void *getTickets(void *args)
// {
//   const char *name = static_cast<const char *>(args);

//   while (true)
//   {
//     // 临界区,只要对临界区加锁，而且加锁的粒度约细越好
//     // 加锁的本质是让线程执行临界区代码串行化
//     // 加锁是一套规范，通过临界区对临界资源进行访问的时候，要加就都要加
//     // 锁保护的是临界区, 任何线程执行临界区代码访问临界资源，都必须先申请锁，前提是都必须先看到锁！
//     // 这把锁，本身不就也是临界资源吗？锁的设计者早就想到了
//     // pthread_mutex_lock: 竞争和申请锁的过程，就是原子的！
//     // 难度在加锁的临界区里面，就没有线程切换了吗？？？？
//     pthread_mutex_lock(&mutex);
//     if (tickets > 0)
//     {
//       usleep(100000);
//       cout << name << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;
//       pthread_mutex_unlock(&mutex);

//       // other code
//       //usleep(123); // 模拟其他业务逻辑的执行
//     }
//     else
//     {
//       // 票抢到几张，就算没有了呢？0
//       cout << name << "] 已经放弃抢票了，因为没有了..." << endl;
//       pthread_mutex_unlock(&mutex);
//       break;
//     }
//   }

//   return nullptr;
// }

// // 如何理解exit？
// int main()
// {
//   pthread_mutex_init(&mutex, nullptr);
//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_t tid4;
//   pthread_create(&tid1, nullptr, getTickets, (void *)"thread 1");
//   pthread_create(&tid2, nullptr, getTickets, (void *)"thread 2");
//   pthread_create(&tid3, nullptr, getTickets, (void *)"thread 3");
//   pthread_create(&tid4, nullptr, getTickets, (void *)"thread 4");

//   // sleep(1);
//   // 倾向于：让主线程，分离其他线程

//   // pthread_detach(tid1);
//   // pthread_detach(tid2);
//   // pthread_detach(tid3);

//   // 1. 立即分离,延后分离 -- 线程活着 -- 意味着，我们不在关心这个线程的死活。4. 线程退出的第四种方式，延后退出
//   // 2. 新线程分离，但是主线程先退出(进程退出) --- 一般我们分离线程，对应的main thread一般不要退出(常驻内存的进程)
//   // sleep(1);

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

// int tickets = 1000;

// void *getTickets(void *args)
// {
//   const char *name = static_cast<const char *>(args);

//   while (true)
//   {

//     if (tickets > 0)
//     {
//       usleep(1000);
//       cout << name << " 抢到了票, 票的编号: " << tickets << endl;
//       tickets--;
//     }
//     else
//     {
//       // 票抢到几张，就算没有了呢？0
//       cout << name << "] 已经放弃抢票了，因为没有了..." << endl;
//       break;
//     }
//   }

//   return nullptr;
// }

// int main()
// {
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

//   return 0;
// }

// void *startRoutine(void *args)
// {

//   int cnt = 5;
//   while (cnt)
//   {
//     cout << "我是新线程   cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }
// }
// int main()
// {
//   // cout << sizeof(void*) << endl;
//   // pthread_t unsigned long int -> 地址！
//   pthread_t tid;
//   // pthread_attr_t
//   int n = pthread_create(&tid, nullptr, startRoutine, (void *)"thread1");
//   // 3. 线程退出的方式，给线程发送取消请求， 如果线程是被取消的，退出结果是：-1
//   // 3.1 main thread cancel new thread , 反过来呢？能不能，什么现象？ --- 不推荐的做法
//   pthread_cancel(tid);
//   // PTHREAD_CANCELED;
//   (void)n;

//   // sleep(3); //代表main thread对应的工作

//   cout << "new thread been canceled   " << n << endl;

//   // sleep(10);
//   //  线程退出的时候，一般必须要进行join，如果不进行join，就会
//   //  造成类似于进程那样的内存泄露问题

//   //sleep(10);

//   // printTid(tid);
//   //  cout << "new thread id : " << tid << endl; //线程ID -- 为什么这么大？
//   // while (true)
//   // {
//   //   cout << "main thread" << endl;

//   //   // cout << "main thread 正在运行..." << endl;
//   //   sleep(1);
//   // }

//    // void* -> 64 -> 8byte -> 空间
//   //int ret  = pthread_join(tid,nullptr); // void **retval是一个输出型参数
//   //cout << "main thread join success, *ret: " << ret << endl;

//   //sleep(10);
// }
// void *startRoutine(void *args)
// {
//   // pthread_detach(pthread_self());
//   // cout << "线程分离....." << endl;

//   int cnt = 5;
//   while (cnt)
//   {
//     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }
// }
// int main()
// {

//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;

//   pthread_create(&tid1, nullptr, startRoutine, (void *)"thread 1");
//   pthread_create(&tid2, nullptr, startRoutine, (void *)"thread 2");
//   pthread_create(&tid3, nullptr, startRoutine, (void *)"thread 3");

//   sleep(1);
//   // 倾向于：让主线程，分离其他线程

//   pthread_detach(tid1);
//   pthread_detach(tid2);
//   pthread_detach(tid3);

//   // 1. 立即分离,延后分离 -- 线程活着 -- 意味着，我们不在关心这个线程的死活。4. 线程退出的第四种方式，延后退出
//   // 2. 新线程分离，但是主线程先退出(进程退出) --- 一般我们分离线程，对应的main thread一般不要退出(常驻内存的进程)
//   // sleep(1);

//   int n = pthread_join(tid1, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid2, nullptr);
//   cout << n << ":" << strerror(n) << endl;
//   n = pthread_join(tid3, nullptr);
//   cout << n << ":" << strerror(n) << endl;

//   return 0;
// }

// void *callback(void *args)
// {
//   int cnt = 5;
//   while (cnt)
//   {
//     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }
// }

// int main()
// {
//   pthread_t tid1;

//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");

//   pthread_detach(tid1);

//   pthread_join(tid1, nullptr);
//   cout << "线程等待结束 " << endl;
//   //sleep(10);
// while (1)
// {
//     cout << "我是新线程 " << endl;
//     sleep(1);
// }

//   return 0;
// }

// struct thread_info
// {
//   pthread_t tid;
//   void* stack; // 线程栈
// };

// __thread int g_val = 10;

// void *callback(void *args)
// {
//   char *name = static_cast<char *>(args);

//   while (1)
//   {
//     cout << "我是新线程 " << name << " 我看到一个全局变量 g_val: "
//          << g_val << "  地址是 " << &g_val << endl;
//     sleep(1);
//   }
// }

// int main()
// {

//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;

//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");
//   pthread_create(&tid2, nullptr, callback, (void *)"thread2");
//   pthread_create(&tid3, nullptr, callback, (void *)"thread3");

//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   pthread_join(tid3, nullptr);

//   return 0;
// }

// void *callback(void *args)
// {
//   while (1)
//   {
//   }
//   pthread_exit((void *)10);
// }

// int main()
// {

//   pthread_t tid;

//   pthread_create(&tid, nullptr, callback, (void *)"thread1");
//   while (1)
//   {
//     cout << "我是主线程... ";
//     printf("新线程id %p\n", tid);
//     sleep(1);
//   }

//   return 0;
// }

// void *callback(void *args)
// {
//   int cnt = 5;
//   while (cnt)
//   {
//     if (cnt == 2)
//     {
//       cout << "注意我要除零了" << endl;
//       int a = 10;
//       a /= 0;
//     }
//     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }
//   pthread_exit((void *)10);
// }

// void handler(int signo)
// {
//   cout << "我是一个进程 pid " << getpid() << ",刚刚获取了一个信号: " << signo << endl;
//   exit(1); // 这里捕捉完直接退出
// }

// // void *callback(void *args)
// // {
// //   int cnt = 5;
// //   while (cnt)
// //   {
// //     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
// //     sleep(1);
// //     cnt--;
// //   }
// //   return (void *)10;
// // }

// int main()
// {
//   signal(8, handler);
//   pthread_t tid1;

//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");
//   void *ret = nullptr;
//   pthread_join(tid1, &ret);
//   cout << "线程等待结束 ret  " << (long long)ret << endl;
//   while (1)
//   {
//     cout << "我是主线程... " << endl;
//     sleep(1);
//   }

//   return 0;
// }

// void *callback(void *args)
// {
//   int cnt = 5;
//   while (cnt)
//   {
//     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }
//   pthread_exit((void *)10);
// }

// int main()
// {
//   pthread_t tid1;

//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");
//   void *ret = nullptr;
//   pthread_join(tid1, &ret);
//   cout << "线程等待结束 ret  " << (long long)ret << endl;
//   sleep(5);

//   return 0;
// }

// void *callback(void *args)
// {
//     while (true)
//     {
//       cout << "我是新线程   线程id" << (char *)args << "... " << endl;
//       sleep(1);
//     }
// }

// void *callback(void *args)
// {
//   while (true)
//   {
//     cout << "我是新线程,线程id  " << pthread_self() << "... " << endl;
//     sleep(1);
//   }
// }

// void *callback(void *args)
// {
//   int cnt = 5;
//   while (cnt)
//   {
//     cout << "我是新线程   线程id" << (char *)args << " cnt  " << cnt << endl;
//     sleep(1);
//     cnt--;
//   }
//   return (void*)10;
// }

// int main()
// {
//   pthread_t tid1;

//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");
//   void* ret = nullptr;
//   pthread_join(tid1, &ret);
//   cout << "线程等待结束 ret  " << (long long)ret << endl;
//   sleep(5);

//   return 0;
// }

// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");
//   pthread_create(&tid2, nullptr, callback, (void *)"thread1");
//   pthread_create(&tid3, nullptr, callback, (void *)"thread1");

//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   pthread_join(tid3, nullptr);

//   cout << "线程等待结束 " << endl;
//   sleep(5);

//   return 0;
// }

// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;
//   pthread_t tid3;
//   pthread_create(&tid1, nullptr, callback, (void *)"thread1");
//   pthread_create(&tid2, nullptr, callback, (void *)"thread1");
//   pthread_create(&tid3, nullptr, callback, (void *)"thread1");
//   while (1)
//   {
//     cout << "我是主线程... 新线程id是 " << tid << endl;
//     sleep(1);
//   }

//   return 0;
// }

// int main()
// {
//   const char* str = "hello";
//   *str = 'H';
//   return 0;
// }

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

// void *rout(void *args)
// {
//   while (true)
//   {
//     cout << "我是新线程..." << endl;
//     sleep(1);
//   }
// }

// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;
//   pthrea`d_create(&tid1, nullptr, callback1, (void *)"thread1"); // 创建线程
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

// int main()
// {
//   pthread_t tid;
//   pthread_create(&tid, nullptr, rout, (void *)"thread"); // 创建线程
//   //pthread_join(tid, nullptr);                            // 等待线程

//   while (true)
//   {
//     cout << "我是主线程..." << endl;
//     sleep(1);
//   }

//   return 0;
// }