/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 16:43:52
 * LastEditTime : 2022-11-17 17:40:57
 */
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define IPC_NAME "/home/bit/104/2022/11_17"
#define PROJ_ID 0x14
#define MEM_SIZE 4096
key_t CreateKey()
{
  key_t key = ftok(IPC_NAME, PROJ_ID);
  if(key < 0)
  {
    std::cerr<< "ftok : " << strerror(errno) << std::endl;
    exit(1);
  }
  return key;
}