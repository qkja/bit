#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    //void SumIsK(vector<vector<int>>& result, const vector<int>& nums,int k, int sum) {
    //  if()
    //}
    //// 这里我们用回溯算法试一下 不要急
    //vector<vector<int>> threeSum(vector<int>& nums) {
    //  vector<vector<int>> vv;
    //  if(nums.empty())
    //    return vv;
    //  SumIsK(vv, nums, 3, 0);
    //  return vv;
    //}
  // 先来测试 for 循环  这里 超出时间限制
  // 这个函数 看看 v 里面 的前两个元素 是不是在 helper中
  // 在 就返回 true
  // 不在 加入 放回 false 
  //bool IsExist(vector<int>& helper, const vector<int>& v)
  //{

  //  int first = v[0];
  //  int second = v[1];
  //  if(helper.empty())
  //  {
  //    helper.push_back(first);
  //    helper.push_back(second);
  //    return false;
  //  }
  //  for(size_t i = 0; i < helper.size(); i += 2)
  //  {
  //    if(helper[i] == first)
  //    {
  //      if(helper[i+1] == second)
  //        return true;
  //    }
  //  }

  //  helper.push_back(first);
  //  helper.push_back(second);
  //  return false;
  //}
  //vector<vector<int>> threeSum(vector<int>& nums) {
  //  vector<vector<int>> vv;
  //  if(nums.empty())
  //    return vv;
  //  vector<int> v;
  //  vector<int> helper;
  //  for(size_t i = 0; i < nums.size(); i++)
  //  {
  //    for(size_t j = 0; j < nums.size(); j++)
  //    {
  //      for(size_t k = 0; k < nums.size(); k++)
  //      {
  //        if(i != j && i != k && j != k)
  //        {
  //          if(nums[i] + nums[j] + nums[k] == 0)
  //          {
  //            //这里需要一个 辅助 的  vector  
  //            
  //            // 这里 可以入数组了
  //            v.push_back(nums[i]);
  //            v.push_back(nums[j]);
  //            v.push_back(nums[k]);
  //            sort(v.begin(), v.end()); // 升序
  //            if(!IsExist(helper,v))
  //            {
  //              vv.push_back(v);
  //            }
  //            v.clear();
  //          }
  //        }
  //      }
  //    }
  //  }
  //  return vv;

  //}
};//
