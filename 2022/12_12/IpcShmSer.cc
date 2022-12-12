#include "Comm.hpp"

int flags = IPC_CREAT | IPC_EXCL;
int main()
{
  umask(0);
  key_t key = CreateKey();
  Log() << "key: " << key << std::endl;
  int shmid = shmget(key, MEM_SIZE, flags | 0666);
  if (shmid < 0)
  {
    Log() << "shmget fali  " << strerror(errno) << std::endl;
    return 1;
  }

  Log() << "shmget success  shmid " << shmid << std::endl;

  // 这里使用共享内存
  // 挂接
  Log() << "shmat begin " << std::endl;
  char *str = (char *)shmat(shmid, nullptr, 0);
  
  
  sleep(5);

  // 去关联
  Log() << "shmdt begin " << std::endl;
  shmdt(str);
  sleep(5);
  Log() << "shmctl begin " << std::endl;
  shmctl(shmid, IPC_RMID, nullptr);
  Log() << "shmctl success  shmid " << shmid << std::endl;
  sleep(5);
  return 0;
}

// int flags = IPC_CREAT | IPC_EXCL;

// int main()
// {
//   umask(0);
//   key_t key = CreateKey();
//   Log() << "key: " << key << std::endl;
//   int shmid = shmget(key, 4097, flags|0666);
//   if (shmid < 0)
//   {
//     Log() << "shmget fali  " << strerror(errno) << std::endl;
//     return 1;
//   }

//   Log() << "shmget success  shmid " << shmid << std::endl;

//   return 0;
// }

// int main()
// {
//   umask(8);
//   key_t key = CreateKey();
//   Log() << "key: " << key << std::endl;
//   int shmid = shmget(key, MEM_SIZE, flags | 0666);
//   if (shmid < 0)
//   {
//     Log() << "shmget fali  " << strerror(errno) << std::endl;
//     return 1;
//   }

//   Log() << "shmget success  shmid " << shmid << std::endl;

//   // 这里使用共享内存
//   // 挂接
//   Log() << "shmat begin " << std::endl;
//   char *str = (char *)shmat(shmid, nullptr, 0);
//   sleep(5);
//   Log() << "shmctl begin " << std::endl;

//   shmctl(shmid, IPC_RMID, nullptr);
//   Log() << "shmctl success  shmid " << shmid << std::endl;
//   sleep(5);

//   return 0;
// }

// int main()
// {
//   key_t key = CreateKey();
//   std::cout << "key: " << key << std::endl;
//   return 0;
// }
