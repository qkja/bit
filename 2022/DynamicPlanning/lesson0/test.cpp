#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;



















//f(i,j) 表示从这个点到最后一行的最小路径和
// i,j  -> i+1,j or i+1 ,j+1可以到达这个点
// f(i,j) = min(f(i+1,j), f(i+1,j+1)) + v[i][j];
// 这个就是简单的转移方程
// 初识值  最后一行的点等于权重本身
// 求得值  f(0,0)
//class Solution {
//public:
//    int minimumTotal(vector<vector<int> > &triangle) {
//        if(triangle.empty())
//          return -1;
//        int length = triangle.size();
//        vector<vector<int>> result(length, vector<int>(length));
//
//        // 设置初识值
//        for(int i = 0; i < length; i++)
//        {
//          result[length-1][i] = triangle[length-1][i];
//        }
//        for(int i = length-2; i >= 0; i--)
//        {
//          for(int j = 0; j <= i; j++)
//          {
//             // 这里理解错了  每玩下一行都会多一个元素  这里不需要判断
//            //if(i == j)
//              //result[i][j] = result[i+1][j] + triangle[i][j];
//            //else 
//              result[i][j] = min(result[i+1][j], result[i+1][j+1]) + triangle[i][j];
//          }
//        }
//        return result[0][0];
//    }
//};


// f(i,j) 表示从第一行到这个点的路径和
//class Solution {
//public:
//    int minimumTotal(vector<vector<int> > &triangle) {
//  
//      // 这里等会判断无效参数
//      
//      vector<vector<int>> result;
//      result.resize(triangle.size());
//      vector<int> v;
//      v.resize(triangle.size());  // 多开辟一些无效空间 
//      for(size_t i = 0; i < result.size(); i++)
//      {
//        result[i] = v;
//      }
//
//      result[0][0] = triangle[0][0];
//      // 这类写状态方程
//      for(size_t i = 1 ; i < triangle.size(); i++)
//      {
//        for(size_t j = 0; j < triangle[i].size(); j++)
//        {
//          // 判断特殊情况
//          if(j == 0)
//          {
//            result[i][0] = result[i-1][0] + triangle[i][0];
//          }
//          else if(i == j)
//          {
//            result[i][j] = result[i-1][j-1] + triangle[i][j];
//          }
//          else 
//          {
//            result[i][j] = min(result[i-1][j], result[i-1][j-1]) + triangle[i][j];    
//          }
//        }
//      }
//      // 这得到最后一行的最小指
//      int minSum = result[result.size()-1][0];
//      for(size_t i = 1; i < result[result.size()-1].size(); i++)
//      {
//        if(minSum > result[result.size()-1][i])
//          minSum = result[result.size()-1][i];
//      }
//      return minSum;
//    }
//};







//class Solution {
//public:
//    bool IsExist(const string& str, unordered_set<string>& dict)
//    {
//      return dict.find(str) != dict.end();
//    }
//    //解释一下 从[start,pos]位置,我们切掉的字符串是否可以在 dict中找到
//    bool process1(string& s, int start, int end, unordered_set<string>& dict)
//    {
//      // 这里是 递归跳出接口
//      if(end ==(int)s.size())
//      {
//        string str = s.substr(start, end-start+1);
//        return IsExist(str,dict);
//      }
//
//      string str = s.substr(start, end-start+1);
//      // 这里开始查找
//      bool b1 = false;
//      bool b2 = false;
//      if(IsExist(str,dict))
//      {
//        // 找到了
//        b1 = process1(s,end+1,end+1,dict)
//          || process1(s,start, end+1,dict);
//      }
//      else 
//      {
//        b2 = process1(s,start,end+1,dict);
//      }
//      return b1&&b2;
//    }
//
//    bool wordBreak(string s, unordered_set<string> &dict) {
//        // 我们先来写一个尝试
//        return process1(s,0,0,dict);
//    }
//};
//
//




//机器人 行走
// 停溜在 cur 
// 还有 rest 步
// 目标 aim
// 有哪些位置 1 - N
// 返回值 方法数
//int process1(int cur, int rest, int aim, int N)
//{
//  if(rest == 0)
//  {
//    return cur == aim ? 1 : 0;
//  }
//
//  // 这还有步数要走
//  if(cur == 1)
//  {
//    // 一定要去2
//    return process1(2, rest-1, aim, N);
//  }
//  if(cur == N)
//  {
//    // 和上面一样
//    return process1(N-1, rest-1, aim, N);
//  }
//
//  // 这里 就
//  return process1(cur+1, rest-1, aim, N)
//    + process1(cur-1, rest-1, aim, N);
//  
//}
//
//int way1(int N, int start, int aim, int K)
//{
//  return process1(start, K, aim, N);
//}
//
//// 优化 尝试1
//// 这个递归 只和 cur 和 rest 有关
//// 出现重复解 的 递归可以优化
//// 从定向下的动态规划
//int process2(int pos, int rest, int aim, int N, vector<vector<int>>& dp)
//{
//  // 有表 找表
//  if(dp[pos][rest] != -1)
//  {
//    return dp[pos][rest];
//  }
//  
//  // 到这里 之前没算过
//  int result = 0;
//  if(rest == 0)
//  {
//    result = pos == aim ? 1 : 0;
//  }
//  else if(pos == 1)
//  {
//    result = process2(2, rest-1, aim, N, dp);
//  }
//  else if(pos == N)
//  {
//    result = process2(N-1, rest-1, aim, N, dp);
//  }
//  else 
//  {
//    result = process2(pos-1, rest-1, aim, N,dp)
//      +process2(pos+1, rest-1, aim, N, dp);
//  }
//
//  dp[pos][rest] = result;
//  return result;
//}
//
//int way2(int N, int start, int aim, int K)
//{
//  // pos 范围 1 - N
//  // rest 范围 0 - K
//
//  // 这里是我第一次用,先暂时解释一下
//  // 我们得到一二维数组,有 N+1行,
//  // 每一行是一个一位数组,里面包含K+1个元素,我们初始化为-1
//  vector<vector<int>> dp(N+1, vector<int>(K+1,-1));
//
//  return process2(start, K, aim, N, dp);
//  // -1 表示 这个位置没有算过
//  
//}
//
//int main()
//{
//  cout << way2(4,2,4,4)<<endl;
//  return 0;
//}
//int main()
//{
//  cout << way1(4, 2, 4, 4) << endl;
//  cout << process(2, 4, 4, 4) << endl;
//  return 0;
//}
// 再次优化  表的大小
// 当rest=0时,只有 aim = cur 的时候才为1
// 我们只需要 dp[cur][rest] 这个数据就可以了
// 普遍位置是如何依赖的
// 继续看暴力递归
// cur = 1 依赖左下角的值
// cur = N 依赖 左上角的
// 普遍位置  依赖左上角 和 左下角
// 我们展示如何填这张表
//int way3(int N, int start, int aim, int K)
//{
//  // 这里添加一下 无效参数的 判断
//  if(N < 2 || start < 1 || start > N|| aim < 1 || aim > N || K < 0)
//    return -1;
//  // pos 范围 1 - N
//  // rest 范围 0 - K
//  vector<vector<int>> dp(N+1, vector<int>(K+1,0));  
//  // 0 来个初识值
//
//  // 只有当 cur = aim && rest = 0的时候
//  // 表格为 1 否则 rest = 0 && cur != aim 都是 0
//  // 因为这个方法到不了 目标
//  dp[aim][0] = 1;
//
//  // 这里 我们 先算 列
//  for(int i = 1;i < K+1; i++)
//  {
//    // 这里 从上王下
//    // cur == 1这里依赖 左下角
//    dp[1][i] = dp[2][i-1];
//    for(int j = 2; j < N; j++)
//    {
//      // 这里依赖 左上角 和左下角
//      dp[j][i] = dp[j-1][i-1] + dp[j+1][i-1];
//    }
//    // cur == N 这里依赖左上角
//    dp[N][i] = dp[N-1][i-1];
//  }
//  // 我们要的结果
//  return dp[start][K];
//
//}
//
//int main()
//{
//  cout << way3(4,2,4,4)<<endl;
//  cout << way3(5,2,4,6)<<endl;
//  return 0;
//}

