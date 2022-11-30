/**
 * Author       : Qkj
 * Description  :
 * Date         : 2022-11-27 10:39:49
 * LastEditTime : 2022-11-27 10:43:14
 */
#include <cstdlib>
#include <cassert>

void Usage(const char* name)
{
  assert(name);

}
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  // 1. 设置命令行设置服务器IP

  // 2 创建客户端
  int sockfd = 0;
  // 要不要绑定,为何不需要 需要绑定,不需要用户z自己
  // 这里不需要是我们不需要自己手动绑定,OS会帮我们这门做
  // 如果你非要自己干,可以 但是我们严重不推荐
  // 所有的客户端和服务器进行通信的时候,
  // 问题 -- 我们如何让OS自己绑定.为什么呢?客户端很短

  // 为何server要bind.server提供的服务必须被所有人知道
  // server还不能随便改变




  //setto() 会自动
  return 0;
}