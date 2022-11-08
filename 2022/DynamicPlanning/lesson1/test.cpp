#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

extern int first(vector<int>& v, int begin, int end);
extern int second(vector<int>& v, int begin, int end);
// 打牌
// 后手函数 

// 根据规则返回获胜者的分数
// 先手和后手是一个人 不是打法
// 注意这是一个后手函数,只不过是为了先手服务的
// 作为一个后手,我们只能得到先手拿过之后才可以,也就是先手会
// 想尽一切办法阻止我们拿大牌
// 我们只能得到 较小值
int second(vector<int>& v, int begin, int end)
{
  if(begin == end)
    return 0;
  // 这里有一个问题 为何又有变成先手了
  int ret1 = v[begin] + first(v, begin+1, end);
  int ret2 = v[end] + first(v, begin, end+1);
  return min(ret1,ret2);
}

int first(vector<int>& v, int begin, int end)
{
  // 对于先手来说 只剩一张牌
  // 直接拿走
  if(begin == end)
    return v[begin];

  // 这里 我们拿到左侧或者右侧 后面就是作为后手了
  int ret1 = v[begin] + second(v, begin+1, end);
  int ret2 = v[end] + second(v, begin, end+1);
  // 我们希望得到 左侧或者右侧的最大值
  return max(ret1,ret2);
}


int way1(vector<int>& scores)
{
  if(scores.empty())
    return -1;
  return -1;
}

