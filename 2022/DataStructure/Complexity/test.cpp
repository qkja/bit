// 时间复杂度
// 比较原则

#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;
// 最坏的情况
//const char* myStrchr(const char* str,int character)
//{
//  assert(str);
//  while(*str)
//  {
//    if(*str == character)
//    {
//      return str;
//    }
//    else 
//    {
//      ++str;
//    }
//  }
//  return NULL;
//}

// 冒泡排序
//void swap(int* pa,int* pb)
//{
//  int ret = *pa;
//  *pa = *pb;
//  *pb = ret;
//}
//void bubbleSort(int* arr, int n)
//{
//  assert(arr);
//  // 这里 n 是个数
//  // 如果 n 是 1 ,不需要比较,所以这里是 n-1
//  for(int i = 0; i < n-1; i++)
//  {
//    // 我们这里 用 后面的和前面的比较
//    for(int j = 1; j < n-i/*注意,这里注释是不对的,但是这里需要关注一下条件*/;j++)
//    {
//      if(arr[j-1] > arr[j])
//      {
//        swap(&arr[j-1], &arr[j]);
//      }
//    }
//  }
//}
// 优化
//void bubbleSort(int* arr, int n)
//{
//  assert(arr);
//  // 这里 n 是个数
//  // 如果 n 是 1 ,不需要比较,所以这里是 n-1
//  for(int i = 0; i < n-1; i++)
//  {
//    int flag = 0;
//    // 我们这里 用 后面的和前面的比较
//    for(int j = 1; j < n-i/*注意,这里注释是不对的,但是这里需要关注一下条件*/;j++)
//    {
//      if(arr[j-1] > arr[j])
//      {
//        flag = 1;
//        swap(&arr[j-1], &arr[j]);
//      }
//    }
//    if(flag == 0)
//      break;
//  }
//}

// 二分查找
// 我们这里写[left, right) 左闭右开的写法
//int BinarySearch(int* array, int n, int key)
//{
//  assert(array);
//  int left = 0;
//  int right = n;
//  while(left < right)
//  {
//    int mid = (left + right) / 2; // 这是最好防溢出
//    if(array[mid] == key)
//    {
//      return mid;
//    }
//    else if(array[mid] < key)
//    {
//      left = mid + 1;
//    }
//    else 
//    {
//      right = mid;
//    }
//  }
//  return -1;
//}
// 等下还要优化一下 另外一个算法 // 这个放在一个具体的场景吧,等着后面再来 ,到时候写一个博客
//int main()
//{
//  int arr[] = {1,2,3,4,5,6};
//  int sz = sizeof(arr)/sizeof(arr[0]);
//  bubbleSort(arr, sz);
//  for(int i = 0; i < sz; i++)
//  {
//    printf("%d ", arr[i]);
//  }
//  return 0;
//}
//
//#include <vector>
//#include <iostream>
//using namespace std;
//class Solution {
//public:
//    //int missingNumber(vector<int>& nums) {
//    //  if(nums.empty())
//    //    return -1;
//    //  int sum = 0;
//    //  for(int val : nums)
//    //    sum += val;
//    //  return((0+nums.size())* (nums.size()+1))/2 - sum;
//    //}
//   // 这里使用 异或
//   //int missingNumber(vector<int>& nums) 
//   //{
//   //  if(nums.empty())
//   //    return -1;
//   //  int flag = 0;
//   //  for(size_t i = 0;i<nums.size();i++)
//   //  {
//   //    flag^=nums[i];
//   //    flag^=i;
//   //  }
//   //  flag ^= (int)nums.size();
//   //  return flag;
//   //}
//
//    //int missingNumber(vector<int>& nums) {
//    //    if(nums.empty())
//    //        return -1;
//    //    vector<int> v;
//    //    v.resize(nums.size() + 1, -1);
//    //    for(size_t i = 0;i<nums.size();i++)
//    //    {
//    //        v[nums[i]]=1;
//    //    }
//    //    for(size_t i=0;i<v.size();i++)
//    //    {
//    //        if(v[i] == -1)
//    //        return i;
//    //    }
//    //    return -1;
//    //}
//};
//int main()
//{
//  cout <<"hello"<<endl;
//  return 0;
//}




///////////////////////////////////////////
// 空间复杂度
// 这里 只谈一点 时间时间积累的 空间是可以重复的
// 等下把斐波那契数列的空间复杂度度博客添加一下
// 下面的轮转数组我们用三种写法

class Solution {
public:
  void reverse(vector<int>& v, int begin, int end)
  {
    while(begin < end)
    {
      int ret = v[begin];
      v[begin] = v[end];
      v[end] = ret;
      begin++;
      end--;
    }
  }
  // 三次逆置
  void rotate(vector<int>& nums, int k) {
    if(nums.empty())
      return;

    k %= nums.size();
    reverse(nums, 0, nums.size() - k - 1);
    reverse(nums, nums.size() - k, nums.size() - 1);
    reverse(nums, 0, nums.size() - 1);
  }

  // 解法二 开辟一个数组 注意 这里 需要 k%size()
  // 防止数组溢出
  // 当k == size的时候,先当与没有移动
  //void rotate(vector<int>& nums, int k) {
  //  if(nums.empty())
  //    return;
  //  vector<int> v;
  //  k %= nums.size();
  //  v.reserve(nums.size());
  //  //把 后 k 个放在前面
  //  //注意下标
  //  for(size_t i = nums.size() - k; i < nums.size(); i++)
  //  {
  //    v.push_back(nums[i]);
  //  }
  //  //把前size-k个放在数组后面
  //  for(int i = 0; i < nums.size() - k; i++)
  //  {
  //    v.push_back(nums[i]);
  //  }
  //  // 数组倒回去
  //  for(size_t i = 0; i < nums.size(); i++)
  //  {
  //    nums[i] = v[i];
  //  }
  //}
    // 解法一 暴力解法 这个应该会超出时间限制
    //void rotateHelper(vector<int>& nums) {
    //  // 保存最后一个元素
    //  int ret = nums[nums.size()-1];
    //  int end = nums.size() - 1;
    //  while(end > 0)
    //  {
    //    nums[end] = nuns[end-1];
    //    end--;
    //  }

    //  nums[end] = ret;
    //}

    //void rotate(vector<int>& nums, int k) {
    //  if(nums.empty())
    //    return;
    //  for(int i = 0; i < k; i++)
    //  {
    //    // 右旋
    //    rotateHelper(nums);
    //  }
    //}
};



