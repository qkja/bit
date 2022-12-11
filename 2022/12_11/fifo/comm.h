/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-12-11 14:11:14
 * LastEditTime : 2022-12-11 14:11:14
 */

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#define IPC_PATH "./fifo"