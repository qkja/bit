#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include "Log.hpp"

#endif
using std::queue;

const int gThreadNum = 5;
template <class T>
class ThreadPool
{
public:
  ThreadPool(int num = gThreadNum)
      : _threadNum(num), _isStart(false)
  {
    pthread_mutex_init(&_mutex, nullptr);
    pthread_cond_init(&_cond, nullptr);
  }
  ~ThreadPool()
  {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
  }

public:
  static void *threadRoutine(void *args) // 主要是 this指针
  {
    pthread_detach(pthread_self());

    ThreadPool *tp = (ThreadPool *)args;
    while (true)
    {
      // sleep(1);
      // std::cout << "thread [" << pthread_self() << "] running..." << std::endl;
      tp->lockQueue();
      while (!tp->haveTask())
      {
        // 进来是没有任务
        tp->waitForTask();
      }
      // 有任务了
      T t = tp->pop();
      tp->unlockQueue();

      int one = 0;
      int two = 0;
      char op = 0;
      t.get(&one, &two, &op);
      int result = t.run(); // 规定所有的任务必须有一个run方法
      Log() << "新线程处理任务 " << one << op << two << "=" << result << std::endl;
    }
  }

public:
  void start()
  {
    assert(!_isStart);

    for (size_t i = 0; i < _threadNum; i++)
    {
      pthread_t temp;
      pthread_create(&temp, nullptr, threadRoutine, this);
    }
    _isStart = true;
  }
  // 放任务
  void push(const T &in)
  {
    lockQueue();
    _taskQueue.push(in);
    choiceThreadForHandler();
    // 这里为何不会死锁
    unlockQueue();
  }

private:
  void choiceThreadForHandler()
  {
    pthread_cond_signal(&_cond);
  }
  void waitForTask()
  {
    pthread_cond_wait(&_cond, &_mutex);
  }
  bool haveTask()
  {
    return !_taskQueue.empty();
  }
  T pop()
  {
    T ret = _taskQueue.front();
    _taskQueue.pop();
    return ret;
  }
  void lockQueue()
  {
    pthread_mutex_lock(&_mutex);
  }
  void unlockQueue()
  {
    pthread_mutex_unlock(&_mutex);
  }

private:
  bool _isStart;
  int _threadNum;
  queue<T> _taskQueue;
  pthread_mutex_t _mutex;
  pthread_cond_t _cond;
};