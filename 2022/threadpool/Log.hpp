#include <iostream>
#include <ctime>

std::ostream &Log()
{
  std::cout << "For Debug | "
            << " timestamp " << (uint32_t)time(nullptr)
            << "| Thread [" << pthread_self() << "] | ";
  return std::cout;
}