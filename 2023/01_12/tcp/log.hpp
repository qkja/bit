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
int logFd = -1;

class Log
{
public:
  Log() : _logFd(-1)
  {
  }
  ~Log()
  {
  }
  void enable()
  {
    umask(0);
    _logFd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666) : -1;
    assert(_logFd >= 0);
    dup2(_logFd, 1);
    dup2(_logFd, 2);
  }

private:
  int _logFd;
};

void logMessage(int level, const char *format, ...)
{
  assert(level >= DEBUG);
  assert(level <= FATAL);

  char logInfo[1024];
  va_list ap;
  va_start(ap, format);

  vsnprintf(logInfo, sizeof(logInfo) - 1, format, ap);
  va_end(ap);

  if (logFd != -1)
  {
    dup2(logFd, 1);
    dup2(logFd, 2);
  }
  FILE *out = (level == FATAL) ? stderr : stdout;
  char *name = getenv("USER");

  fprintf(out, "%s | %u | %s | %s\n",
          log_level[level],
          (unsigned long)(time(nullptr)),
          name == nullptr ? "unknow" : name,
          logInfo);
  fflush(out);
  fsync(out->_fileno);
}