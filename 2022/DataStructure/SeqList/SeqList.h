#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#endif 

/*
 * 这里只简单 的 写一下
 * 至于里面的细节我们用注释表示
*/

// 好修改数据的 类型
typedef int SLDateType;

typedef struct SeqList 
{
  SLDateType * array;
  size_t size;
  size_t capacity;
} SeqList;



// 对数据的管理:增删查改 
// 问题  初始化为何使用 指针传参 简单的值拷贝
// 尤其是里面的指针  这也是简单的值拷贝
void SeqListInit(SeqList* ps);

// 这里可以用结构体传参吗
void SeqListDestroy(SeqList* ps);

// 指针消耗小
void SeqListPrint(SeqList* ps);

void SeqListPushBack(SeqList* ps, SLDateType x);

void SeqListPushFront(SeqList* ps, SLDateType x);

void SeqListPopFront(SeqList* ps);

void SeqListPopBack(SeqList* ps);
 
// 顺序表查找
int SeqListFind(SeqList* ps, SLDateType x);
// 顺序表在pos位置插入x
void SeqListInsert(SeqList* ps, size_t pos, SLDateType x);
// 顺序表删除pos位置的值
void SeqListErase(SeqList* ps, size_t pos);

// 这里是一些辅助函数,一般不爆露接口
// 检测容量
// 不够直接扩容 够什么都不做
void SeqListCheckCapacity(SeqList* ps);

