/** 
 * Author       : Qkj
 * Description  : 
 * Date         : 2022-11-17 16:34:52
 * LastEditTime : 2022-11-17 18:49:53
 */

#include "Comm.hpp"
#include "Log.hpp"
using namespace std;
// 充当 创建共享内存的角色
const int flags  = IPC_CREAT | IPC_EXCL | 0666;
int main()
{
  key_t key = CreateKey();
  //cout << key << endl;
  Log() << key << endl;

  int shmid = shmget(key, MEM_SIZE, flags);
  if(shmid < 0)
  {
    Log() << strerror(errno) << endl;
    exit(2);
  }
  Log() << "create shmid success " << shmid << endl;
  sleep(5);

  // 挂接
  // void *shmat(int shmid, const void *shmaddr, int shmflg);
  // shmaddr -> nullptr
  // shmflg 读写  默认  0
  // 返回值  成功了就是返回值的地址  佛则就是nall  和mallo的用法一样
 

  shmat(shmid, nullptr, 0);
  sleep(5);

  Log() << "shmat shmid success " << shmid << endl;



  // 去关联
  // int shmdt(const void *shmaddr);





  // 删除
  //int shmctl(int shmid, int cmd, struct shmid_ds *buf);
  shmctl(shmid, IPC_RMID,nullptr);
  sleep(5);
  Log() << "delete shmid success " << shmid << endl;
  return 0;

}