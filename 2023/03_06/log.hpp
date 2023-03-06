#pragma once
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cassert>
#include <ctime>

#define DEBUG 0
#define NOTICE 1
#define WARINING 2
#define FATAL 3

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

  FILE *out = (level == FATAL) ? stderr : stdout;
  char *name = getenv("USER");

  fprintf(out, "%s | %u | %s | %s\n",
          log_level[level],
          (unsigned long)(time(nullptr)),
          name == nullptr ? "unknow" : name,
          logInfo);
}