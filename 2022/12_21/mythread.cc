#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

void *callback(void *args)
{
  while (1)
  {
  }
  pthread_exit((void *)10);
}


int main()
{
  
  pthread_t tid;

  pthread_create(&tid, nullptr, callback, (void *)"thread1");
  while (1)
  {
    cout << "我是主线程... ";
    printf("新线程id %p\n", tid);
    sleep(1);
  }

  return 0;
}

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