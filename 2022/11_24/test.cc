/**
 * User: Qkj
 * Description: 线程概念
 * Date: 2022-11-24
 * Time: 19:08
 */
#include <iostream>
#include <unistd.h>
#include <string>
#include <pthread.h> // Linux 必须自带这个库

using namespace std;

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                    void *(*start_routine)(void *), void *arg);

// 我们先来见一下

//也要等待
// void *callback1(void *args)
// {
//   string str = (char *)args;
//   while (true)
//   {
//     cout << str << "  " << getpid() << endl;
//     sleep(1);
//   }
// }

// void *callback2(void *args)
// {
//   string str = (char *)args;
//   while (true)
//   {
//     cout << str << "  " << getpid() << endl;
//     sleep(1);
//   }
// }

// int main()
// {
//   pthread_t tid1;
//   pthread_t tid2;

//   pthread_create(&tid1, nullptr, callback1, (void *)"thread1"); // 这里回调 callback1
//   pthread_create(&tid2, nullptr, callback2, (void *)"thread2");

//   while (true)
//   {
//     cout << "我是主线程   " << getpid() << endl;
//     sleep(1);
//   }

//   // 等待
//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   return 0;
// }
