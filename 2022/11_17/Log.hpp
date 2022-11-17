/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 17:10:55
 * LastEditTime : 2022-11-17 17:13:58
 */
#include <iostream>
#include <time.h>
std::ostream& Log()
{
  std::cout << "ForDebug|  " << "timestamp: " << (uint64_t)time(nullptr) << " ";
  return std::cout;
}