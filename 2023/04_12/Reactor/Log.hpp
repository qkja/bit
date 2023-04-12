#pragma once

#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <cassert>
#include <cstring>
#include <cerrno>
#include <cstdlib>

#define DEBUG 0
#define NOTICE 1
#define WARNING 2

#define FATAL 3

const char *log_level[] = {"DEBUG", "NOTICE", "WARNING", "FATAL"};

// logMessage(DEBUG, "%d", 10);
void logMessage(int level, const char *format, ...)
{
  assert(level >= DEBUG);
  assert(level <= FATAL);

  char *name = getenv("USER");

  char logInfo[1024];
  va_list ap; // ap -> char*
  va_start(ap, format);

  vsnprintf(logInfo, sizeof(logInfo) - 1, format, ap);

  va_end(ap); // ap = NULL

  FILE *out = (level == FATAL) ? stderr : stdout;

  fprintf(out, "%s | %u | %s | %s\n",
          log_level[level],
          (unsigned int)time(nullptr),
          name == nullptr ? "unknow" : name,
          logInfo);
}