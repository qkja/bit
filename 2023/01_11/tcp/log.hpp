#pragma once
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEBUG 0
#define NOTICE 1
#define WARINING 2
#define FATAL 3

#define LOGFILE "server.log"
const char *log_level[] = {"DEBUG", "NOTICE", "WARINING", "FATAL"};

void logMessage(int level, const char *format, ...)
{
  assert(level >= DEBUG);
  assert(level <= FATAL);

  char logInfo[1024];
  va_list ap;
  va_start(ap, format);

  vsnprintf(logInfo, sizeof(logInfo) - 1, format, ap);
  va_end(ap);
  umask(0);
  int fd = open(LOGFILE, 0666, O_WRONLY | O_CREAT | O_APPEND);
  assert(fd >= 0);

  FILE *out = (level == FATAL) ? stderr : stdout;
  char *name = getenv("USER");
  dup2(fd, 1);
  dup2(fd, 2);
  fprintf(out, "%s | %u | %s | %s\n",
          log_level[level],
          (unsigned long)(time(nullptr)),
          name == nullptr ? "unknow" : name,
          logInfo);
  fflush(out);
  fsync(fd);
  close(fd);
}