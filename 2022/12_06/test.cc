/**
 * User: Qkj
 * Description:
 * Date: 2022-12-06
 * Time: 19:01
 */
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>

using namespace std;
void my_perror(const char *p)
{
  printf("%s: %s\n", p, strerror(errno));
}
int main()
{
  int fd = open("log.txt", O_RDONLY); // 必然失败,没有这个函数

  if (fd < 0)
  {
    // 失败后 errno会被设置
    my_perror("open");
    perror("open");
  }
  return 0;
}
// int main()
// {

//  perror("hello perror 2");
//   return 0;
// }

// int main()
// {

//   // stdout
//   printf("hello printf 1\n"); // 1
//   fprintf(stdout, "hello fprintf 1\n");
//   fputs("hello fputs 1\n", stdout);

//   // stderr

//   fprintf(stderr, "hello fprintf 2\n");
//   fputs("hello fputs 2\n", stderr);
//   perror("hello perror 2");

//   // cout
//   cout << "hello cout 1" << endl;

//   // cerr
//   cerr << "hello cerr 2" << endl;
//   return 0;
// }

// int main()
// {

//   perror("hello perror 2");
//   return 0;
// }
