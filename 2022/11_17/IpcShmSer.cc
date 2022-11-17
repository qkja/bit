/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 16:34:52
 * LastEditTime : 2022-11-17 21:17:08
 */


#include "Comm.hpp"
#include "Log.hpp"

#include <unistd.h>

using namespace std;

// 我想创建全新的共享内存
const int flags = IPC_CREAT | IPC_EXCL;

// 充当使用共享内存的角色
int main()
{

    CreateFifo();
    int fd = Open(FIFO_FILE, READER);
    assert(fd >= 0);


    key_t key = CreateKey();
    Log() << "key: " << key << "\n";

    Log() << "create share memory begin\n";
    int shmid = shmget(key, MEM_SIZE, flags | 0666);
    cout << shmid<< endl;
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
    while(true)
    {
        // 让读端进行等待
        if(Wait(fd) <= 0) break; 
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
// #include "Comm.hpp"
// #include "Log.hpp"
// using namespace std;
// // 充当 创建共享内存的角色
// const int flags  = IPC_CREAT | IPC_EXCL | 0666;
// int main()
// {
//     CreateFifo();
//     int fd = Open(FIFO_FILE, READER);
//     assert(fd >= 0);

//   //int fd = Open(FIFO_FILE, READER);
//   //assert(fd >= 0);
//   printf("hello2\n");
//   key_t key = CreateKey();
//   //cout << key << endl;
//   //Log() << key << endl;
//   printf("hello3\n");
//   int shmid = shmget(key, MEM_SIZE, flags | 0666);
//   //int shmid = shmget(key, MEM_SIZE, flags);

//   printf("hello4\n");
  
//   if(shmid < 0)
//   {
//     Log() << strerror(errno) << endl;
//     exit(2);
//   }
//   printf("hello5\n");

//   //Log() << "create shmid success " << shmid << endl;
//   //sleep(5);

//   // 挂接
//   // void *shmat(int shmid, const void *shmaddr, int shmflg);
//   // shmaddr -> nullptr
//   // shmflg 读写  默认  0
//   // 返回值  成功了就是返回值的地址  佛则就是nall  和mallo的用法一样
 

//   char* str = (char*)shmat(shmid, nullptr, 0);
//   if(str == nullptr)
//   {}  // 判断一下

//   //Log() << "shmat shmid success " << shmid << endl;
//   //sleep(5);
//   while (true)
//   {
//     if(Wait(fd) <= 0)
//     {
//       break;
//     }
//     printf("%s\n", str);
//     sleep(1);
//   }
  



//   // 使用
//   // while (true)
//   // {
//   //   printf("%s\n", str);
//   //   sleep(1);
//   // }

//   // 去关联
//   // int shmdt(const void *shmaddr);
//   shmdt(str);  // 参数就是放回置
//   str = nullptr;




//   // 删除
//   //int shmctl(int shmid, int cmd, struct shmid_ds *buf);
//   shmctl(shmid, IPC_RMID,nullptr);
//   //sleep(5);
//   //Log() << "delete shmid success " << shmid << endl;
//   Close(fd, FIFO_FILE);
//   return 0;
// }