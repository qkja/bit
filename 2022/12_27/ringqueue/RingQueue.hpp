#pragma once
#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>
using std::vector;
const int gCap = 5;

template <class T>
class RingQueue
{
public:
  RingQueue(int cap = gCap)
      : _ringQueue(cap)
  {
    // 生产者使用  _ringQueue.size()
    sem_init(&_roomSem, 0, _ringQueue.size());
    // 消费者使用  0
    sem_init(&_dataSem, 0, 0);
    _pIndex = 0;
    _cIndex = 0;

    pthread_mutex_init(&_pmutex, nullptr); // this指针跑哪了
    pthread_mutex_init(&_cmutex, nullptr);
  }

  ~RingQueue()
  {
    sem_destroy(&_roomSem);
    sem_destroy(&_dataSem);

    pthread_mutex_destroy(&_pmutex);
    pthread_mutex_destroy(&_cmutex);
  }

public:
  // 生产者调用
  void push(const T &in)
  {
    // 申请信号量
    sem_wait(&_roomSem); // P 操作
    // 生产

    // 要在这里加锁   --最好

    pthread_mutex_lock(&_pmutex);
    _ringQueue[_pIndex] = in;
    _pIndex++;
    _pIndex %= _ringQueue.size();
    pthread_mutex_unlock(&_pmutex);

    // 数据那里变化
    sem_post(&_dataSem); // V操作
  }
  // 消费者来拿
  T pop()
  {
    sem_wait(&_dataSem);
    pthread_mutex_lock(&_cmutex);

    T ret = _ringQueue[_cIndex];
    _cIndex++;
    _cIndex %= _ringQueue.size();
    pthread_mutex_unlock(&_cmutex);

    sem_post(&_roomSem);
    return ret;
  }

private:
  vector<T> _ringQueue;    // 环形队列
  sem_t _roomSem;          // 空间计数器
  sem_t _dataSem;          // 数据计数器
  uint32_t _pIndex;        // 生产者位置
  uint32_t _cIndex;        // 消费者位置
  pthread_mutex_t _pmutex; // 生产者的锁
  pthread_mutex_t _cmutex; // 消费者的锁
};