#include <iostream>
using namespace std;
//机器人 行走
// 停溜在 cur 
// 还有 rest 步
// 目标 aim
// 有哪些位置 1 - N
// 返回值 方法数
int process(int cur, int rest, int aim, int N)
{
  if(rest == 0)
  {
    return cur == aim ? 1 : 0;
  }

  // 这还有步数要走
  if(cur == 1)
  {
    // 一定要去2
    return process(2, rest-1, aim, N);
  }
  if(cur == N)
  {
    // 和上面一样
    return process(N-1, rest-1, aim, N);
  }

  // 这里 就
  return process(cur+1, rest-1, aim, N)
    + process(cur-1, rest-1, aim, N);
  
}
int way1(int N, int start, int aim, int K)
{
  return process(start, K, aim, N);
}
int main()
{
  cout << way1(4, 2, 4, 4) << endl;
  cout << process(2, 4, 4, 4) << endl;
  return 0;
}

