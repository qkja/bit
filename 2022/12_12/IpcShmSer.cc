// #include "Comm.hpp"

// int flags = IPC_CREAT | IPC_EXCL;
#include "Comm.hpp"
// #include "Log.hpp"

#include <unistd.h>

using namespace std;

// 我想创建全新的共享内存
const int flags = IPC_CREAT | IPC_EXCL;

// 充当使用共享内存的角色
int main()
{
  // cout << "==================" << endl;
  CreateFifo();
  // cout << "==================" << endl;

  // return 2;
  int fd = Open(FIFO_FILE, READER);
  // cout << "==================" << endl;
  // return 2;
  assert(fd >= 0);

  key_t key = CreateKey();
  Log() << "key: " << key << "\n";

  Log() << "create share memory begin\n";
  int shmid = shmget(key, MEM_SIZE, flags | 0666);
  if (shmid < 0)
  {
    Log() << "shmget: " << strerror(errno) << "\n";
    return 2;
  }
  Log() << "create shm success, shmid: " << shmid << "\n";
  // sleep(5);

  // 1. 将共享内存和自己的进程产生关联attach
  char *str = (char *)shmat(shmid, nullptr, 0);
  Log() << "attach shm : " << shmid << " success\n";

  // sleep(5);
  // 用它
  while (true)
  {
    // 让读端进行等待
    if (Wait(fd) <= 0)
      break;
    printf("%s\n", str);
    sleep(1);
  }

  // 2. 去关联
  shmdt(str);
  Log() << "detach shm : " << shmid << " success\n";
  // sleep(5);

  // 删它
  shmctl(shmid, IPC_RMID, nullptr);

  Log() << "delete shm : " << shmid << " success\n";

  Close(fd, FIFO_FILE);
  // sleep(5);
  return 0;
}

// int main()
// {
//   umask(0);
//   CreateFifo(); // 创建命名管道
//   int fd = Open(FIFO_FILE, READER);

//   key_t key = CreateKey();
//   Log() << "key: " << key << std::endl;
//   int shmid = shmget(key, MEM_SIZE, flags | 0666);
//   if (shmid < 0)
//   {
//     Log() << "shmget fali  " << strerror(errno) << std::endl;
//     return 1;
//   }

//   Log() << "shmget success  shmid " << shmid << std::endl;
//   Log() << "shmat begin " << std::endl;
//   char *str = (char *)shmat(shmid, nullptr, 0);

//   while (true)
//   {
//     int s = Wait(fd); // 没有内容在这里阻塞
//     if (s <= 0)
//       break;
//     printf("%s\n", str);
//   }

//   Log() << "shmdt begin " << std::endl;
//   shmdt(str);

//   Log() << "shmctl begin " << std::endl;
//   shmctl(shmid, IPC_RMID, nullptr);
//   Log() << "shmctl success  shmid " << shmid << std::endl;

//   Close(fd, FIFO_FILE);
//   return 0;
// }

// int main()
// {
//   umask(0);
//   CreateFifo(); // 创建命名管道
//   int fd = Open(FIFO_FILE, READER);

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

//   while (true)
//   {
//     int s = Wait(fd); // 没有内容在这里阻塞
//     if (s <= 0)
//       break;
//     printf(".%s\n", str);
//   }

//   // while (true)
//   // {
//   //   printf(".%s\n", str);
//   //   sleep(1);
//   // }

//   // sleep(5);

//   // 去关联
//   Log() << "shmdt begin " << std::endl;
//   shmdt(str);
//   // sleep(5);
//   Log() << "shmctl begin " << std::endl;
//   shmctl(shmid, IPC_RMID, nullptr);
//   Log() << "shmctl success  shmid " << shmid << std::endl;
//   // sleep(5);
//   Close(fd,FIFO_FILE);
//   return 0;
// }

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
