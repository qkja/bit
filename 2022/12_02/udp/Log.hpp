#ifndef __LOG_HPP__
#define __LOG_HPP__
#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <cstdlib>
#include <time.h>
#endif

#define DEBUG  0
#define NOTICE 1
#define WARING 2
#define FATAL  3
const char* log_level[] = {"DEBUG",
"NOTICE",
"WARING",
"FATAL"};
// 注意这个去可变参数列表那个去瞅瞅
void logMessage(int level, const char* format, ...)
{
  assert(level >= DEBUG);
  assert(level <= FATAL);
  char* name = getenv("USER");
  char logInfo[1024];
  va_list ap;
  va_start(ap, format);
  vsnprintf(logInfo, sizeof(logInfo)-1,
      format, ap);
  va_end(ap);

  FILE* out = (level == FATAL)?stderr:stdout;
  fprintf(out, "%s | %u | %s | %s\n", 
      log_level[level],
      (unsigned int)time(nullptr),
      name == nullptr?"unknow":name,
      logInfo);
}
