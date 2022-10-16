#include "SeqList.h"

void SeqListCheckCapacity(SeqList* ps)
{
  assert(ps);
  if(ps->capacity == ps->size)
  {
    // z注意这个判断很重要
    size_t newSize = ps->capacity == 0 ? 4 : 2 * ps->capacity;
    // 开辟空间 使用 realloc
    // 这个函数 会开辟拷贝
    int* ret = (int*)realloc(ps->array, sizeof(SLDateType)*newSize);
    // 我测试了一下
    // 如果我们开辟失败,
    // C++ 原来的空间也会被销毁
    // C语言则不会
    // 但是 函数说明可不是这样的
    // 这里我们按最差的来  
    // 后面会我专门去测试一下,差点表
    assert(ret);
    ps->array = ret;
    ps->capacity = newSize;
  }
}

// 对数据的管理:增删查改 
void SeqListInit(SeqList* ps)
{
  // 首先检测 是否为空
  assert(ps);
  
  //这里有两个模式,一个是初始化的时候开辟点空间
  //一个不开,这里我们选择不开
  ps->array = NULL;
  ps->capacity = 0;
  ps->size = 0;
}

void SeqListDestroy(SeqList* ps)
{
  assert(ps);
  ps->capacity = 0;
  ps->size = 0;
  // 释放 NULL 也不会报错
  // 不过最好判断一下
  if(ps->array)
    free(ps->array);
  ps->array = NULL;
}
 
void SeqListPrint(SeqList* ps)
{
  assert(ps);
  for(size_t i = 0; i < ps->size; i++)
  {
    printf("%d ", *(ps->array + i));
  }
  printf("\n");
}

void SeqListPushBack(SeqList* ps, SLDateType x)
{
  assert(ps);
  // 检测扩容
  
  SeqListCheckCapacity(ps);
  // 到这一步 空间够了
  ps->array[ps->size++] = x;
}

void SeqListPushFront(SeqList* ps, SLDateType x);
void SeqListPopFront(SeqList* ps);
void SeqListPopBack(SeqList* ps);
 
// 顺序表查找
int SeqListFind(SeqList* ps, SLDateType x);
// 顺序表在pos位置插入x
void SeqListInsert(SeqList* ps, size_t pos, SLDateType x);
// 顺序表删除pos位置的值
void SeqListErase(SeqList* ps, size_t pos);
