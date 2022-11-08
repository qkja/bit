/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-03 15:51:18
 * LastEditTime : 2022-11-03 16:27:38
 */

#pragma once
#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATH_NAME "/home/bit/104/2022/11_02"
#define PROJ_ID 0x14
#define MEM_SIZE 4096

key_t CreateKey()
{
    //key_t ftok(const char *pathname, int proj_id);
    key_t key = ftok(PATH_NAME, PROJ_ID);
    //On  success, the generated key_t value is returned.  On failure -1 is returned, with errno indicating
    //the error as for the stat(2) system call.
    if(key == -1)
    {
        std::cerr << "ftok : " <<strerror(errno) << std::endl;
        exit(1);
    }
    return key;
}