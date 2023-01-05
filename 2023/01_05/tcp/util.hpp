#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.hpp"

#define SOCKET_ERR 1
#define BIND_ERR 2
#define LISTEN_ERR 3