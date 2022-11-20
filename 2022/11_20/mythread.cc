/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-20 08:48:20
 * LastEditTime : 2022-11-20 14:55:59
 */
#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;

void *startRoutine(void *args)
{
  int cnt = 10;
  while (true)
  {
    cout << "我是一个新线程 cnt " << cnt << endl;
    sleep(1);
    if (cnt == 0)
    {
      int* p = nullptr;
      *p = 20;
    }
    cnt--;
  }
}


int main()
{

  cout << sizeof(void*) <<endl;
  return 0;
}

// int main()
// {

//   pthread_t tid = 0;
//   pthread_create(&tid, nullptr, startRoutine, (void *)"thread1");

//   pthread_join(tid, nullptr);

//   cout << "线程推出了" << endl;
//   sleep(10);
//   while (true)
//   {
//     cout << "主线程正在运行..." << endl;
//     sleep(1);
//   }

//   return 0;
// }

// 创建函数
// void *startRoutine(void *args)
// {
//   int cnt = 10;
//   while (true)
//   {
//     cout << pthread_self() << endl;
//     cout << "我是一个新线程,id " << cnt << endl;
//     sleep(1);
//     if (cnt == 0)
//     {
//       break;
//     }
//     cnt--;
//   }
// }

// int main()
// {

//   pthread_t tid = 0;
//   pthread_create(&tid, nullptr, startRoutine, (void *)"thread1");

//   pthread_join(tid, nullptr);

//   cout << "线程推出了" << endl;
//   sleep(10);
//   while (true)
//   {
//     cout << "主线程正在运行..." << endl;
//     sleep(1);
//   }

//   return 0;
// }

// // 创建函数
// void *startRoutine(void *args)
// {
//   while (true)
//   {
//     cout << "我是一个新线程,id " << endl;
//     sleep(1);
//   }
// }

// static void PrintTid(const pthread_t tid)
// {
//   printf("thread id : 0x%x\n", tid);
// }

// int main()
// {
//   // 1 创建一个线程
//   // int pthread_create(pthread_t * thread, const pthread_attr_t *attr,
//   //                    void *(*start_routine)(void *), void *arg);

//   // On  success, pthread_create() returns 0; on error, it returns an error number, and the contents of *thread are
//   //      undefined.

//   pthread_t tid = 0;
//   pthread_create(&tid, nullptr, startRoutine, (void *)"thread1");

//   // 如何打印线程id 就是所谓整数
//   PrintTid(tid);
//   cout << "id " << tid << endl; // 怎么这么大 现在只需要知道是新城id
//   cout << "id " << (unsigned int)*(unsigned int*)tid << endl;
//   while (true)
//   {
//     cout << "主线程正在运行..." << endl;
//     sleep(1);
//   }

//   return 0;
// }

// #include <string>
// #include <iostream>
// #include <sys/types.h>
// #include <unistd.h>
// #include <pthread.h>
// using namespace std;

// int main()
// {
//   // 1 创建一个线程
//   // int pthread_create(pthread_t * thread, const pthread_attr_t *attr,
//   //                    void *(*start_routine)(void *), void *arg);

//   return 0;
// }

// 先来认识一下线程的简单使用

// void* callback1(void* p)
// {

// }

// void* callback2(void* p)
// {

// }
// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;

//   pthread_create(&tid1, nullptr, callback1, (void*)"thread 1");
//   pthread_create(&tid1, nullptr, callback2, (void*)"thread 1");

//   while (true)
//   {
//     cout << "我是主线程 " << getpid() << endl;
//     sleep(1);
//   }
//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   return 0;
// }

// int main()
// {
//   int* p =nullptr;
//   for(int i=0;i<10;i++){};
//   return 0;
// }

// #include <string>
// #include <pthread.h>

// // 先来认识一下线程的简单使用
// void callback1()
// {

// }
// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;

//   pthread_create(&tid1, nullptr, callbask1, (void*)"thread 1")
//   pthread_create(&tid1, nullptr, callbask2, (void*)"thread 1")

//   while (true)
//   {
//     cout << "我是主线程 " << getpid(); << endl;
//     sleep(1);
//   }
//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   return 0;
// }
