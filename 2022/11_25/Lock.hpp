/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-25 18:41:06
 * LastEditTime : 2022-11-25 18:44:29
 */
#include <pthread.h>
class Mutex
{

public:
  Mutex()
  {
    pthread_mutex_init(&_lock, nullptr);
  }
  ~Mutex()
  {
    pthread_mutex_destroy(&_lock);
  }


  void lock()
  {
    pthread_mutex_lock(&_lock);
  }

  void unlock()
  {
    pthread_mutex_unlock(&_lock);
  }

private:
  pthread_mutex_t _lock;
};
