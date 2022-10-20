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

//void SeqListInit(SeqList ps)                                        
//{                                                                                                             // 这里有两个模式,
//  // 一个是初始化的时候开辟点空间                                                    
//  // 一个不开,这里我们选择不开                                        
//  ps.array = NULL;                                                                           
//  ps.capacity = 0;                                                                                   
//  ps.size = 0;                                                      
//} 


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
  SeqListInsert(ps, ps->size, x);
  //assert(ps);
  // 检测扩容
  
  //SeqListCheckCapacity(ps);
  // 到这一步 空间够了
  //ps->array[ps->size++] = x;
}

void SeqListPushFront(SeqList* ps, SLDateType x)
{
  SeqListInsert(ps, 0, x);
  //assert(ps);
  // 扩容
  
  //size_t pos = ps->size-1;
  //while((int)pos >= 0)
  //{
  //  ps->array[pos+1] = ps->array[pos];
  //  --pos;
  //}
  //ps->array[0] = x;
  //ps->size++;
  //size_t pos = ps->size;
  //while(pos > 0)
  //{
  //  ps->array[pos] = ps->array[pos-1];
  //  --pos;
  //}
  //ps->array[pos] = x;
  //ps->size++;
}

void SeqListPopFront(SeqList* ps)
{
  SeqListErase(ps, 0);
  //assert(ps); 
  //if(ps->size == 0)
  //  return;
  //for(size_t i = 1;i < ps->size; i++)
  //{
  //  ps->array[i-1] = ps->array[i];
  //}
  //ps->size--;
}

void SeqListPopBack(SeqList* ps)
{
  SeqListErase(ps,ps->size-1);
  // assert(ps);
  // if(ps->size == 0)
  //   return;
  // ps->size--;
}
 
// 顺序表查找
int SeqListFind(SeqList* ps, SLDateType x)
{
  assert(ps);
  for(size_t i = 0; i < ps->size; i++)
  {
    if(ps->array[i] == x)
      return x;
  }
  return -1;
}

// 顺序表在pos位置插入x
void SeqListInsert(SeqList* ps, size_t pos, SLDateType x)
{
  assert(ps);
  //判断pos的合法性
  assert(pos <= ps->size); // 等于箱单于尾插
  // 检测 扩容
  SeqListCheckCapacity(ps);
  size_t end = ps->size;
  while(end > pos)
  {
    ps->array[end] = ps->array[end-1];
    end--;
  }
  ps->array[pos] = x;
  ps->size++;
}

// 顺序表删除pos位置的值
void SeqListErase(SeqList* ps, size_t pos)
{
  assert(ps);
  assert(pos < ps->size); // 这里不等 是因为数组下标越界
  if(ps->size == 0)
    return;
  for(size_t i = pos+1; i < ps->size; i++)
  {
    ps->array[i-1] = ps->array[i];
  }
  ps->size--;
}
