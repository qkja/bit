/**
 * User: Qkj
 * Description: 线程池
 * Date: 2022-12-27
 * Time: 19:51
 */
#include "ThreadPool.hpp"
#include <memory>
#include <time.h>
#include <string>
//#include "Log.hpp"
#include "Task.hpp"

using namespace std;

int main()
{
  prctl(PR_SET_NAME, "master");

  const string str = "+-*/%";

  // unique_ptr<ThreadPool<int>> tp(new ThreadPool<int>());
  //unique_ptr<ThreadPool<Task>> tp(new ThreadPool<Task>());
  unique_ptr<ThreadPool<Task>> tp(ThreadPool<Task>::getInstance());
  tp->start();
  srand((unsigned long)time(nullptr) ^ getpid() ^ pthread_self());

  sleep(1);
  while (1)
  {
    int one = rand() % 50;
    int two = rand() % 10;
    char op = str[rand() % str.size()];
    Task t(one, two, op);
    Log() << "主线程派发任务 " << one << op << two << "=?" << endl;
    tp->push(t);
    sleep(1);
  }

  // cout << "hello bit "<< endl;
  return 0;
}
