/** 
 * Author       : Qkj
 * Description  : 使用共享内存的角色
 * Date         : 2022-11-03 15:45:00
 * LastEditTime : 2022-11-03 16:05:41
 */

#include "Comm.hpp"
using namespace std;
int main()
{
    key_t key = CreateKey();
    cout << key << endl;
    return 0;
}
