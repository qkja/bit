/** 
 * Author       : Qkj
 * Description  : 创造共享内存
 * Date         : 2022-11-03 15:45:13
 * LastEditTime : 2022-11-03 20:08:34
 */

#include "Comm.hpp"
#include "Log.hpp"
using namespace std;
const int flags = IPC_CREAT | IPC_EXCL;

int main()
{
    key_t key = CreateKey();
    //Log() << key << endl;
    //cout << key << endl;

    // 创建共享内存
    // int shmget(key_t key, size_t size, int shmflg);
    int shmid = shmget(key, MEM_SIZE, flags);

    // 返回值
    //On success, a valid shared memory identifier is returned.  On errir, -1 is returned, and errno  is  set
    //to indicate the error.
    if(shmid < 0)
    {
        Log() << "shmid" <<strerror(errno) << "\n";
        exit(2);
    }

    Log() << "create shm success, shmid : " << shmid << endl;
    return 0;
}