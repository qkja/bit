#include "Comm.hpp"

int main()
{
  key_t key = CreateKey();
  Log() << "key: " << key << std::endl;
  Log() << "shmget begin" << std::endl;

  // 仅仅是获取
  int shmid = shmget(key, MEM_SIZE, IPC_CREAT);
  // 挂接
  Log() << "shmat begin" << std::endl;
  char *str = (char *)shmat(shmid, nullptr, 0);
  sleep(5);

  Log() << "shmdt begin" << std::endl;
  shmdt(str);
  sleep(5);

  return 0;
}

// int main()
// {
//   key_t key = CreateKey();
//   std::cout << "key: " << key << std::endl;
//   return 0;
// }
