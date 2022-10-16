#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
//class Solution {
//public:
//    bool containsDuplicate(vector<int>& nums) {
//      if(nums.empty())
//        return false;
//      // 这里使用 map 
//      map<int,int> m;
//      for(int& val : nums)
//      {
//        m[val]++;
//      }
//      // 遍历 map 
//      for(auto val : m)
//      {
//        if(val.second > 1)
//          return true;
//      }
//      return false;
//    }
//};
class Solution {
public:
    // 这里我们使用简单的dp
    int maxSubArray(vector<int>& nums) {
      if(nums.empty())
        return -1;
      vector<int> result;
      result.resize(nums.size());
      result[0] = nums[0];
      int maxSum = result[0];
      for(size_t i = 1; i < nums.size(); ++i)
      {
        result[i] = max(result[i-1]+nums[i], nums[i]);
        if(result[i] > maxSum)
        {
          maxSum = result[i];
        }
      }
      return maxSum;
    }
};
