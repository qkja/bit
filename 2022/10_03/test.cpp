#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <deque>
using namespace std;
// 什么是 不错的 工作
// 三个 指标 薪资 岗位 同事(公司)
// 薪资 超过 1w 底线 超过 30w
// 目标岗位 现在还很模糊 


class Solution {

public:

  // 连续子向量的和   就是 素组里面的连续元素
  int FindGreatestSumOfSubArray(vector<int> array) {
    if(array.empty())
      return 0;
    int sum = 0;

  }



  // tok 问题   找最下 建大堆
  //vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
  //  vector<int> v;
  //  if(input.size() == 0 || k <= 0)
  //    return v;
  //  if(k > (int)input.size())
  //    return input;

  //  // 这里 建大堆 默认的 less  就是 大堆
  //  
  //  std::priority_queue<int> maxPri;
  //  for(int i = 0; i < k; i++)
  //  {
  //    maxPri.push(input[i]);
  //  }
  //  // 这里开始 挑选
  //  for(size_t i = k; i < input.size(); i++)
  //  {
  //    // 得到 堆顶的元素
  //    int ret = maxPri.top();
  //    // 判断 是否入堆
  //    if(input[i] < ret)
  //    {
  //      maxPri.pop();
  //      maxPri.push(input[i]);
  //    }
  //  }

  //  while(!maxPri.empty())
  //  {
  //    v.push_back(maxPri.top());
  //     maxPri.pop();
  //  }
  //  return v;
  //}

  void  PermutationHelper(string& str, int start, vector<string>& result)
  {

  }
  vector<string> Permutation(string str) {

    vector<string> result;
    if(str.size() > 0)
    {

      // 这里需要 排列组合
      PermutationHelper(str, 0, result);
      // 按照 字典序 排序
      sort(result.begin(), result.end());
    }
    return result;
  }
};
