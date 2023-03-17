/**
* User: Qkj
* Description: 
* Date: 2023-03-17
* Time: 17:02
*/
#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;
void *callback1(void *args)
{
  while (true)
  {
    cout << "我是新线程   " << (char *)args << "... " << endl;
    sleep(1);
  }
}

void *callback2(void *args)
{
  while (true)
  {
    cout << "我是新线程   " << (char *)args << "... " << endl;
    sleep(1);
  }
}

int main()
{
  pthread_t tid1;
  pthread_t tid2;
  pthread_create(&tid1, nullptr, callback1, (void *)"thread1"); // 创建线程
  pthread_create(&tid2, nullptr, callback2, (void *)"thread2"); // 创建线程

  while (true)
  {
    cout << "我是主线程..." << endl;
    sleep(1);
  }

  pthread_join(tid1, nullptr); // 等待线程
  pthread_join(tid2, nullptr); // 等待线程

  return 0;
}
