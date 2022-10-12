// 时间复杂度
// 比较原则
//
#include <stdio.h>
#include <assert.h>
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
void swap(int* pa,int* pb)
{
  int ret = *pa;
  *pa = *pb;
  *pb = ret;
}
void bubbleSort(int* arr, int n)
{
  assert(arr);
  // 这里 n 是个数
  // 如果 n 是 1 ,不需要比较,所以这里是 n-1
  for(int i = 0; i < n-1; i++)
  {
    // 我们这里 用 后面的和前面的比较
    for(int j = 1; j < n-i/*注意,这里注释是不对的,但是这里需要关注一下条件*/;j++)
    {
      if(arr[j-1] > arr[j])
      {
        swap(&arr[j-1], &arr[j]);
      }
    }
  }
}
// 优化

// 二分查找
int main()
{
  int arr[] = {1,2,3,4,5,6};
  int sz = sizeof(arr)/sizeof(arr[0]);
  bubbleSort(arr, sz);
  for(int i = 0; i < sz; i++)
  {
    printf("%d ", arr[i]);
  }
  return 0;
}
