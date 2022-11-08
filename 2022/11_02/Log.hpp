/** 
 * Author       : Qkj
 * Description  : 辅助打印
 * Date         : 2022-11-03 16:07:18
 * LastEditTime : 2022-11-03 16:14:07
 */
#include <iostream>
#include <ctime>

std::ostream& Log()
{
    std::cout << "For Debug |  " << "timestamp :  " << (uint64_t)time(nullptr) << "  ";
    return std::cout;
}