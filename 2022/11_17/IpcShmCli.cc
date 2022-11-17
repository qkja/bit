/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 16:33:30
 * LastEditTime : 2022-11-17 19:07:31
 */
#include "Comm.hpp"
// 充当 使用共享内存的角色
#include "Log.hpp"
using namespace std;
int main()
{
  key_t key = CreateKey();

  int shmid = shmget(key, MEM_SIZE, IPC_CREAT);
  if(shmid < 0)
  {
    Log() << strerror(errno) << endl;
    exit(2);
  }

  // 挂接
  char* str = (char*)shmat(shmid, nullptr, 0);
  if(str == nullptr)
  {}  // 判断一下

  // 用它


  sleep(1);

  shmdt(str);  // 参数就是放回置
  // 这类不做删除   我们只是 使用
  return 0;
}
