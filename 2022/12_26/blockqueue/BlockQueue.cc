#include "BlockqQueue.hpp"
#include <time.h>
#include <unistd.h>
using namespace std;
void *consumer(void *args)
{
  BlockqQueue<int> *p = (BlockqQueue<int> *)args;

  while (true)
  {
    int ret = p->pop();
    cout << "我消费了一个数据 " << ret << endl;
    //sleep(1);
  }
}

void *producer(void *args)
{
  BlockqQueue<int> *p = (BlockqQueue<int> *)args;
  while (true)
  {
   

    int ret = rand() % 10;
    p->push(ret);
    cout << "我生产了一个数据 " << ret << endl;
    sleep(1);
  }
}
int main()
{
  srand((unsigned long)time(nullptr));

  BlockqQueue<int> bq;
  pthread_t c, q;
  pthread_create(&c, nullptr, consumer, &bq);
  pthread_create(&q, nullptr, producer, &bq);

  pthread_join(c, nullptr);
  pthread_join(q, nullptr);
  return 0;
}

// const int &f()
// {
//   int ret = 1;
//   return ret;
// }
// int main()
// {
//   cout << f() << endl;
//   int ret = f();
//   cout << f() << endl;

//   cout << ret << endl;
//   cout << "hello bit" << endl;
//   return 0;
// }