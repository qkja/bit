/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 16:43:52
 * LastEditTime : 2022-11-17 21:34:59
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include "Log.hpp"

#define PATH_NAME "/home/bit/104/2022/11_17"
#define PROJ_ID 0x14
#define MEM_SIZE 4096

#define FIFO_FILE ".fifo"

key_t CreateKey()
{
    key_t key = ftok(PATH_NAME, PROJ_ID);
    if(key < 0)
    {
        std::cerr <<"ftok: "<< strerror(errno) << std::endl;
        exit(1);
    }
    return key;
}

void CreateFifo()
{
    umask(0);
    if(mkfifo(FIFO_FILE, 0666) < 0)
    {
        std::cerr << strerror(errno) << "\n";
        exit(2);
    }
}

#define READER O_RDONLY
#define WRITER O_WRONLY

int Open(const std::string &filename, int flags)
{
    return open(filename.c_str(), flags);
}

int Wait(int fd)
{
    uint32_t values = 0;
    ssize_t s = read(fd, &values, sizeof(values));
    return s;
}

int Signal(int fd)
{
    uint32_t cmd = 1;
    write(fd, &cmd, sizeof(cmd));
}

int Close(int fd, const std::string filename)
{
    close(fd);
    unlink(filename.c_str());
}









// #include <iostream>

// #include <string>
// #include <cstring>
// #include <unistd.h>
// #include <cstdio>
// #include <sys/types.h>
// #include <errno.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <assert.h>
// //#include "Log.hpp"

// #define IPC_NAME "/home/bit/104/2022/11_17"
// #define PROJ_ID 0x14
// #define MEM_SIZE 4096
// #define FIFO_FILE ".fifo"

// #define READER O_RDONLY
// #define WRITER O_WRONLY

// key_t CreateKey()
// {
//   key_t key = ftok(IPC_NAME, PROJ_ID);
//   if(key < 0)
//   {
//     std::cerr<< "ftok : " << strerror(errno) << std::endl;
//     exit(1);
//   }
//   return key;
// }


// // 创建管道
// void CreateFifo()
// {
//   if(mkfifo(FIFO_FILE, 0666) < 0)
//   {
//     std::cerr<< "mkfifo fail" << std::endl;
//     exit(2);
//   }
// }

// int Open(const std::string& filename, int falgs)
// {
//   //printf("qqq\n");
//   return open(filename.c_str(), falgs);
//   //printf("qqq\n");

//   //return fd;
// }


// int Wait(int fd)
// {
//   uint32_t values = 0;
//   ssize_t s = read(fd, &values, sizeof(values));
//   if(s <= 0)
//     return 0;
//   //assert(s == sizeof(values));
//   return s;
// }

// void Signal(int fd)
// {
//    uint32_t cmd = 0;
//    write(fd, &cmd, sizeof(cmd));
// }

// void Close(int fd, const std::string& name)
// {
//   close(fd);
//   unlink(name.c_str());

// }





// int OpenForRead(std::string& filename)
// {
//   int fd = open(filename.c_str(), O_RDONLY);
//   return fd;
// }

// int OpenForWrite(std::string& filename)
// {
//   int fd = open(filename.c_str(), O_WRONLY);
//   return fd;
// }