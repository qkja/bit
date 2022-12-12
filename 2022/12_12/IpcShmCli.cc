#include "Comm.hpp"
//#include "Log.hpp"

#include <cstdio>
#include <unistd.h>

using namespace std;
// 充当使用共享内存的角色
int main()
{
  int fd = Open(FIFO_FILE, WRITER);
  // 创建相同的key值
  sleep(5);
  key_t key = CreateKey();
  Log() << "key: " << key << "\n";

  // 获取共享内存
  int shmid = shmget(key, MEM_SIZE, IPC_CREAT);
  if (shmid < 0)
  {
    Log() << "shmget: " << strerror(errno) << "\n";
    return 2;
  }

  // 挂接
  char *str = (char *)shmat(shmid, nullptr, 0);

  // 用它
  // sleep(5);
  // 竟然没有使用任何的系统调用接口！
  // str
  while (true)
  {
    printf("Please Enter# ");
    fflush(stdout);
  //scanf("%s", str);
    ssize_t s = read(0, str, MEM_SIZE);

    //printf("Please Enter#2 \n");


    if (s > 0)
    {
      str[s] = '\0';
    }
    Signal(fd);
  }
  // int cnt = 0;
  // while(cnt <= 26)
  // {
  //     str[cnt] = 'A' + cnt;
  //     ++cnt;
  //     str[cnt] = '\0';
  //     sleep(5);
  // }

  // 去关联
  shmdt(str);

  return 0;
}

// int main()
// {
//   int fd = Open(FIFO_FILE, WRITER);
//   key_t key = CreateKey();
//   Log() << "key: " << key << std::endl;
//   Log() << "shmget begin" << std::endl;

//   int shmid = shmget(key, MEM_SIZE, IPC_CREAT);
//   Log() << "shmat begin" << std::endl;
//   char *str = (char *)shmat(shmid, nullptr, 0);
//   while (true)
//   {
//     printf("请输入# ");
//     fflush(stdout);
//     ssize_t s = read(0, str, MEM_SIZE);
//     if (s > 0)
//     {
//       str[s] = '\0';
//     }
//     Signal(fd);
//   }

//   Log() << "shmdt begin" << std::endl;
//   shmdt(str);
//   // sleep(5);
//   close(fd);
//   return 0;
// }

// int main()
// {
//   int fd = Open(FIFO_FILE, WRITER);
//   key_t key = CreateKey();
//   Log() << "key: " << key << std::endl;
//   Log() << "shmget begin" << std::endl;

//   // 仅仅是获取
//   int shmid = shmget(key, MEM_SIZE, IPC_CREAT);
//   // 挂接
//   Log() << "shmat begin" << std::endl;
//   char *str = (char *)shmat(shmid, nullptr, 0);
//   while (true)
//   {
//     printf("请输入# ");
//     fflush(stdout);
//     ssize_t s = read(0, str, MEM_SIZE);
//     if (s > 0)
//     {
//       str[s] = '\0';
//     }
//     Signal(fd);
//   }
//   // while (true)
//   // {
//   //   printf("请输入# ");
//   //   fflush(stdout);
//   //   ssize_t s = read(0, str, MEM_SIZE);
//   //   if (s == 0)
//   //   {
//   //     break;
//   //   }
//   // }

//   // int cnt = 0;
//   // while (cnt < 26)
//   // {
//   //   str[cnt] = 'A' + cnt;
//   //   cnt++;
//   //   str[cnt] = '\0';
//   //   sleep(5);
//   // }

//   // sleep(5);

//   Log() << "shmdt begin" << std::endl;
//   shmdt(str);
//   // sleep(5);
//   close(fd);
//   return 0;
// }

// int main()
// {
//   key_t key = CreateKey();
//   std::cout << "key: " << key << std::endl;
//   return 0;
// }
