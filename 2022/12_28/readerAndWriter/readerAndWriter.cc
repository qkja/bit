#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int board = 0;
pthread_rwlock_t rw;
void *reader(void *args)
{
  const char *name = (char *)args;

  while (1)
  {
    pthread_rwlock_rdlock(&rw);
    cout << "reader read: " << board << endl;
    sleep(3);
    pthread_rwlock_unlock(&rw);
    sleep(2);
  }
}

void *writer(void *args)
{
  sleep(1);

  const char *name = (char *)args;
  while (1)
  {
    pthread_rwlock_wrlock(&rw);
    board++;
    pthread_rwlock_unlock(&rw);
    sleep(1);
  }
}

int main()
{
  pthread_rwlock_init(&rw, nullptr);
  pthread_t w;
  pthread_t r1;
  pthread_t r2;
  pthread_t r3;
  pthread_t r4;
  pthread_create(&r1, nullptr, reader, (void *)"reader");
  pthread_create(&r2, nullptr, reader, (void *)"reader");
  pthread_create(&r3, nullptr, reader, (void *)"reader");
  pthread_create(&r4, nullptr, reader, (void *)"reader");
  pthread_create(&w, nullptr, writer, (void *)"reader");
  pthread_join(w, nullptr);
  pthread_join(r1, nullptr);
  pthread_join(r2, nullptr);
  pthread_join(r3, nullptr);
  pthread_join(r4, nullptr);
  pthread_rwlock_destroy(&rw);

  return 0;
}