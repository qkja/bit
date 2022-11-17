/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 16:33:30
 * LastEditTime : 2022-11-17 21:03:50
 */


#include "Comm.hpp"
#include "Log.hpp"

#include <cstdio>
#include <unistd.h>

using namespace std;
// 充当使用共享内存的角色
int main()
{
    int fd = Open(FIFO_FILE, WRITER);
    // 创建相同的key值
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
    char *str = (char*)shmat(shmid, nullptr, 0);

    while(true)
    {
        printf("Please Enter# ");
        fflush(stdout);
        ssize_t s = read(0, str, MEM_SIZE);
        if(s > 0)
        {
            str[s] = '\0';
        }
        Signal(fd);
    }
    shmdt(str);

    return 0;
}









// #include "Comm.hpp"
// // 充当 使用共享内存的角色
// #include "Log.hpp"
// using namespace std;
// int main()
// {
//   // printf("111\n");
//   // fflush(stdout);
//   //CreateFifo();

//   int fd = Open(FIFO_FILE, WRITER);
//   // printf("222\n");
//   // fflush(stdout);
//   assert(fd >= 0);
//   key_t key = CreateKey();
//   int shmid = shmget(key, MEM_SIZE, IPC_CREAT);

//   // printf("333\n");
//   // fflush(stdout);
//   if(shmid < 0)
//   {
//     Log() << strerror(errno) << endl;
//     exit(2);
//   }
  

//   // 挂接
//   char* str = (char*)shmat(shmid, nullptr, 0);
//   if(str == nullptr)
//   {}  // 判断一下
//   //sleep(10);
//   // 用它
//   //int cnt = 0;


//   while(true)
//   {
//     printf("请输入: ");
//     fflush(stdout);
//     size_t s = read(0, str, MEM_SIZE);
//     if(s > 0)
//     {
//       // abc\n
//       str[s-1] = '\0';
//     }
//     Signal(fd);
//   }


//   // while(true)
//   // {
//   //   printf("请输入: ");
//   //   fflush(stdout);
//   //   size_t s = read(0, str, MEM_SIZE);
//   //   if(s > 0)
//   //   {
//   //     // abc\n
//   //     str[s-1] = '\0';
//   //   }
//   // }
//   // while(cnt < 26)
//   // {
//   //   str[cnt] = 'A' + cnt;
//   //   ++cnt;
//   //   str[cnt] = '\0';
//   //   sleep(1);

//   // }
//   //sleep(1);

//   shmdt(str);  // 参数就是放回置
//   // 这类不做删除   我们只是 使用
//   return 0;
// }