#include "BlockqQueue.hpp"
#include <time.h>
#include <unistd.h>
#include <string>

#include "Task.hpp"
std::string str = "+-*/%";
using namespace std;
void *consumer(void *args)
{
  BlockqQueue<Task> *p = (BlockqQueue<Task> *)args;

  while (true)
  {
    //sleep(1);

    Task t = p->pop();
    int one = 0;
    int two = 0;
    char op = 0;
    t.get(&one, &two, &op);
    int result = t();
    cout << "我 [ " << pthread_self() << " ] 消费了一个任务 "
         << one << " " << op << " " << two << "=" << result << endl;
    // cout << "我消费了一个数据 " << ret << endl;
    //  cout << "我消费了一个数据 " << ret << endl;
    //   sleep(1);
  }
}

void *producer(void *args)
{
  BlockqQueue<Task> *p = (BlockqQueue<Task> *)args;

  while (true)
  {

    int one = rand() % 10;
    int two = rand() % 10;
    char op = str[rand() % str.size()];
    Task t(one, two, op);
    p->push(t);
    cout << "我 [ " << pthread_self() << " ] 生产了一个任务 "
         << one << " " << op << " " << two << "=?" << endl;

    // int ret = rand() % 10;
    // p->push(ret);
    // cout << "我生产了一个数据 " << ret << endl;
    sleep(1);
  }
}
int main()
{
  srand((unsigned long)time(nullptr));
  BlockqQueue<Task> bq;
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