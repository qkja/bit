/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-30 18:54:59
 * LastEditTime : 2022-11-30 20:04:13
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "log.hpp"

#define SOCKET_ERR 1
#define BIND_ERR   2
#define LISTEN_ERR 3
#define BUFFER_SIZE 1024