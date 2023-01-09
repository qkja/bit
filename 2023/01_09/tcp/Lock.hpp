#pragma once
#include <pthread.h>
#include <iostream>

class Mutex
{
public:
  Mutex(/* args */)
  {
    pthread_mutex_init(&_mutex, nullptr);
  }
  ~Mutex()
  {
    pthread_mutex_destroy(&_mutex);
  }

  void lock()
  {
    pthread_mutex_lock(&_mutex);
  }
  void unlock()
  {
    pthread_mutex_unlock(&_mutex);
  }

private:
  pthread_mutex_t _mutex;
};

class Lock_GUARD
{
private:
  Mutex *_pMutex;

public:
  Lock_GUARD(Mutex *p)
      : _pMutex(p)
  {
    std::cout << "加锁成功" << std::endl;
    _pMutex->lock();
  }

  ~Lock_GUARD()
  {
    std::cout << "解锁成功" << std::endl;
    _pMutex->unlock();
  }
};