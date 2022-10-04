#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:

  struct TreeNode {
 	int val;
 	struct TreeNode *left;
 	struct TreeNode *right;
 	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  };

  int KthNode(TreeNode* proot, int k) {
    if(proot == nullptr || k <= 0)
      return -1;
    vector<int> v;
    stack<TreeNode*> s;
    TreeNode* cur = proot;
    while(cur != nullptr || !s.empty())
    {
      if(cur)
      {
        s.push(cur);
        cur = cur->left;
      }
      else 
      {

        cur = s.top();
        v.push_back(cur->val);
        s.pop();
        cur = cur->right;
      }
      
    }
    if(k > (int)v.size())
      return -1;
    return v[k-1];
  }

  //struct TreeNode {
  //  int val;
  //  struct TreeNode *left;
  //  struct TreeNode *right;
  //  TreeNode(int x) :
  //          val(x), left(NULL), right(NULL) {
  //  }
  //};
  //vector<vector<int> > Print(TreeNode* pRoot) {
  //    vector<vector<int>> vv;
  //    if (pRoot == nullptr) {
  //        return vv;
  //    }
  //    queue<TreeNode*> q;
  //    q.push(pRoot);
  //    int size = 1;
  //    vector<int> v;
  //    int flag = 0;
  //    while (size--) {
  //        TreeNode* ret = q.front();
  //        q.pop();
  //        if (ret->left)
  //            q.push(ret->left);
  //        if (ret->right)
  //            q.push(ret->right);

  //        v.push_back(ret->val);

  //        if (size == 0)
  //        {
  //            if (flag == 0) 
  //            {
  //                flag = 1;
  //            }
  //            else 
  //            {
  //                // 逆置一下
  //                reverse(v.begin(), v.end());
  //                flag = 0;
  //            }
  //            vv.push_back(v);
  //            v.clear();
  //            size = q.size();
  //        }

  //    }// endofwhile
  //    return vv;
  //}


  //void reverser(string& str, int begin, int end)
  //{
  //  while(begin < end)
  //  {
  //    std::swap(str[begin],str[end]);
  //    begin++;
  //    end--;
  //  }
  //}

  //// 这里我们默认空格不连续
  //string ReverseSentence(string str) {
  //  if(str.empty())
  //    return "";

  //  // 局部逆置 这里 需要 得到 空格' ';
  //  size_t begin = 0;
  //  size_t end = 0;
  //  while(end != string::npos)
  //  {
  //    // 找字串
  //    end = str.find(' ', begin);
  //    if(end == string::npos)
  //    {
  //      reverser(str, begin, str.size() - 1);
  //      break;
  //    }
  //    reverser(str, begin, end-1);
  //    begin = end + 1;
  //  }
  //  reverser(str, 0, str.size()-1);
  //  return str;
  //}

  // 字符串左移
  // 这个用一个比较 垃圾的写法
  //void LeftRotateStringHelper(string& str) {
  //  char ch = str[0];
  //  str.erase(0,1);
  //  str += ch;
  //}
  //string LeftRotateString(string str, int n) {
  // 
  // if(str.empty())
  //   return "";
  // n = n % str.size();// 这一点很重要
  // for(int i=0;i < n; i++)
  // {
  //   LeftRotateStringHelper(str);
  // }
  // return str;
  //}
  // 滑动窗口的 问题
  //vector<vector<int> > FindContinuousSequence(int sum) {
  //  vector<vector<int>> vv;
  //  int low = 1;
  //  int high = 2;
  //  while(low < high)
  //  {
  //    //  求和  (a0 + an)*n/2
  //    int result = (low + high)*(high-low+1) / 2;
  //    if(sum == result)
  //    {
  //      vector<int> v;
  //      for(int i=low;i<=high;i++)
  //      {
  //        v.push_back(i);
  //      }
  //      vv.push_back(v);
  //      low++;
  //    }
  //    else if(sum > result)
  //    {
  //      high++;
  //    }
  //    else
  //    {
  //      low++;
  //    }
  //  }//endofwhile
  //  return vv;
  //}


  //struct myCompare
  //{
  //  bool operator()(int x, int y)
  //  {
  //    string sx = to_string(x);
  //    string sy = to_string(y);

  //    string A = sx;
  //    A += sy;

  //    string B = sy;
  //    B += sx;

  //    return A < B;
  //  }
  //};

  //void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
  //  if(data.empty())
  //    return;

  //  // 这需要 异或 一下  到底是 两个 x y的异或 结果一定不为0 可以以这个作为判据
  //  // 把这个  结果看作 二进制  一定有bit为1 这个位就是 x和y不同的位,
  //  // 我们准备两个数组,两两数据相同的一定在同一个数组,x y 在两个数组
  //  // 我们分别对这两个 数组异或 得到 xy
  //  int x = 0;
  //  *num1 = 0;
  //  *num2 = 0;

  //  for(auto& val : data)
  //    x ^= val;

  //  // 这里寻找 最后一个 位为1 
  //  int flag = 1;
  //  for(int i = 0; i < (int)sizeof(int)*8; i++)
  //  {
  //    
  //    if(x & (1<<i))
  //    {
  //      flag = 1 << i;
  //      break;
  //    }
  //  }

  //  for(size_t i = 0; i < data.size(); i++)
  //  {
  //    if(data[i] & flag)
  //      *num1 = (*num1) ^ data[i];
  //    else 
  //      *num2 = (*num2) ^ data[i];
  //  // 这里开始遍历
  //  }
  //}

  //string PrintMinNumber(vector<int> numbers) {
  //  if(numbers.empty())
  //    return "";

  //  sort(numbers.begin(), numbers.end(), myCompare());

  //  string str;
  //  for(auto& val : numbers)
  //    str += to_string(val);
  //  return str;
  //}


  // 连续子向量的和   就是 素组里面的连续元素
  // 定义:   f(i) : 表示 亿i下标结尾 的连续和
  // 转移:   f(i) = max(f(i-1)+arr[i], arr[i]);
  // 初始化: f(0) = arr[0]
  
  // 确立容器 一个一位数组
  
  // 方法二 优化一下 我们总是拿到 f(i-1)我们关系这个是不是负数
  //int FindGreatestSumOfSubArray(vector<int> array) {
  //  if(array.size() == 0)
  //    return 0;

  //  int total = array[0];
  //  int maxSum = total;
  //  for(size_t i = 1; i < array.size(); i++)
  //  {
  //    if(total >= 0)
  //      total += array[i];
  //    else 
  //      total = array[i];
  //    if(maxSum < total)
  //      maxSum = total;
  //  }
  //  return maxSum;
  //}

  // 方法一 简单的dp 3 + 1 1就是使用 一位数组还是二维数组
  //int FindGreatestSumOfSubArray(vector<int> array) {
  //  if(array.empty())
  //    return 0;

  //  int* dp = new int[array.size()]; // 这里初始化为0了
  //  dp[0] = array[0];
  //  int maxSum = dp[0];

  //  for(size_t i = 1; i < array.size(); i++)
  //  {
  //    dp[i] = max(dp[i-1]+array[i], array[i]);
  //    if(maxSum < dp[i])
  //      maxSum = dp[i];
  //  }

  //  delete[] dp;
  //  return maxSum;
  //}
};

//bool IsPalindrome(string &s, int *start, int *end)
//{
//
//  int left = 0;
//  int right = s.size() - 1;
//  bool result = true;
//  while(left < right)
//  {
//    if(s[left] != s[right])
//    {
//      result = false;
//      break;
//    }
//    else 
//    {
//      left++;
//      right--;
//    }
//  }
//
//  // 这里已经找到了
//  // 这是 碰到了 不能成为回文字符串的 两个节点  题目说了,去掉一个肯定可以的到 回文
//  if(start != nullptr)
//     *start = left;
//  if(end != nullptr)
//     *end = right;
//  return result;
//}
//
//int main() 
//{
//    int n = 0;
//    cin >> n;
//    while (n--) 
//    {
//      string s;
//      cin >> s;
//      int* start = new int(0); // 这里需要 
//      int* end = new int(0);
//      if(IsPalindrome(s, start, end))
//      {
//        cout << -1 << endl;
//      }
//      else 
//      {
//        // 这里需要输出下标
//        // 使用这个方法 比我想的要节省太多的空间
//        // 删除一个节点
//        // a b b 或者  b b a
//        s.erase(s.begin() + *start);
//
//        if(IsPalindrome(s, nullptr, nullptr))
//          cout << *start << endl;
//        else 
//          cout << *end << endl;
//        
//      }
//      delete start;
//      delete end;
//    }
//    return 0;
//}
