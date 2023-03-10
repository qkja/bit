#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

namespace Util
{
  bool SetNonBlock(int sock)
  {
    int flag = fcntl(sock, F_GETFD);
    if (flag == -1)
      return false;
    int n = fcntl(sock, F_SETFL | O_NONBLOCK);

    if (n == -1)
      return false;
    return true;
  }
}

#endif
