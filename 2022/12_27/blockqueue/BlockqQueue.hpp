#pragma once

#include <iostream>
#include <pthread.h>
#include <queue>
#include <stdlib.h>

using std::queue;

const uint32_t gDefaultCap = 5;
// 设计一个阻塞队列
template <class T>
class BlockqQueue
{

public:
  BlockqQueue(uint32_t cap = gDefaultCap)
      : _cap(cap)
  {
    pthread_mutex_init(&_mutex, nullptr);
    pthread_cond_init(&_conCond, nullptr);
    pthread_cond_init(&_proCond, nullptr);
  }
  ~BlockqQueue()
  {
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_conCond);
    pthread_cond_destroy(&_proCond);
  }

public:
  // 生产接口
  void push(const T &in)
  {
    // 加锁
    // 判断  是不是适合生产 是否满了
    //       满了(不生产,顺便解 锁,)-- 产生饥饿问题   这里要  阻塞时锁都被扔掉了)  唤醒消费者
    //       不满(生产) -- 程序员视角的条件

    // 生产
    // 解锁

    lockQueue();
    while (isFull()) // 小bug
    {
      // 阻塞等待,等待被唤醒
      proBlockWait();
    }

    // 条件满足可以生产
    pushCore(in);
    unlockQueue();
    // 唤醒消费者
    wakeCon();
  }
  // 消费接口
  // void pop(T *out)
  T pop()
  {
    // 加锁
    // 消费 -> 阻塞队列是否为空
    //      空   -- 等待(休眠)
    //      不空 -- 消费 接着唤醒生产者
    // 解锁

    lockQueue();
    while (isEmpty())
    {
      conBlockWait();
    }

    T ret = popCore();
    unlockQueue();
    // 唤醒生产者
    wakePro();
    return ret;
  }

private:
  void wakePro()
  {
    pthread_cond_signal(&_proCond);
  }
  void wakeCon()
  {
    pthread_cond_signal(&_conCond);
  }
  T popCore()
  {
    T ret = _bq.front();
    _bq.pop();
    return ret;
  }

  void pushCore(const T &in)
  {
    _bq.push(in);
  }
  void conBlockWait()
  {
    pthread_cond_wait(&_conCond, &_mutex);
  }

  void proBlockWait()
  {
    pthread_cond_wait(&_proCond, &_mutex);
  }

  bool isEmpty()
  {
    return _bq.empty();
  }
  bool isFull()
  {
    return _bq.size() == _cap;
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
  uint32_t _cap; // 阻塞队列的容量

  queue<T> _bq;            // 阻塞队列
  pthread_mutex_t _mutex;  // 一把锁
  pthread_cond_t _conCond; // 消费者等待的条件变量
  pthread_cond_t _proCond; // 生产者等待的条件变量
};