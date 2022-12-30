#include "RingQueue.hpp"
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// int fdPro = 0;
// int fdCon = 0;
void *productor(void *args)
{
  RingQueue<int> *p = (RingQueue<int> *)args;
  while (true)
  { 
    // 不如直接打印到文件中
    // pthread_mutex_lock(&mutex);
    // dup2(fdPro, 1);
    // pthread_mutex_unlock(&mutex);

    int data = rand() % 10;
    p->push(data);
    cout << "pthread[ " << pthread_self() << " ] 生产了一个数据 " << data << endl;
    //sleep(3);
  }
}

void *consumer(void *args)
{

  RingQueue<int> *p = (RingQueue<int> *)args;
  while (true)
  {
    // 重定向这里有问腿
    // pthread_mutex_lock(&mutex);

    // dup2(fdCon, 1);
    // pthread_mutex_unlock(&mutex);
    sleep(10);

    int data = p->pop();
    cout << "pthread[ " << pthread_self() << " ] 消费了一个数据 " << data << endl;
  }
}

int main()
{

  // fdPro = open("Prodect.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

  // fdCon = open("Con.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

  srand((unsigned long)time(nullptr) ^ getpid());
  RingQueue<int> rq;
  pthread_t c1;
  pthread_t c2;
  pthread_t c3;
  pthread_t c4;

  pthread_t p1;
  pthread_t p2;
  pthread_t p3;
  pthread_t p4;

  pthread_create(&p1, nullptr, productor, &rq);
  pthread_create(&p2, nullptr, productor, &rq);
  pthread_create(&p3, nullptr, productor, &rq);
  pthread_create(&p4, nullptr, productor, &rq);

  pthread_create(&c1, nullptr, consumer, &rq);
  pthread_create(&c2, nullptr, consumer, &rq);
  pthread_create(&c3, nullptr, consumer, &rq);
  pthread_create(&c4, nullptr, consumer, &rq);

  pthread_join(p1, nullptr);
  pthread_join(p2, nullptr);
  pthread_join(p3, nullptr);
  pthread_join(p4, nullptr);

  pthread_join(c1, nullptr);
  pthread_join(c2, nullptr);
  pthread_join(c3, nullptr);
  pthread_join(c4, nullptr);

  // cout << "hello bit" << endl;
  return 0;
}