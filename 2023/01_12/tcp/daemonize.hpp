#pragma once

#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void daemonize()
{
  signal(SIGPIPE, SIG_IGN);
  if (fork() > 0)
    exit(0);
  setsid();
  int fd = 0;
  if (fd = open("/dev/null", O_RDWR) != -1)
  {
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > STDERR_FILENO)
      close(fd);
  }
}
