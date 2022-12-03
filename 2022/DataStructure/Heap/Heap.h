#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#endif

typedef int HPDataTytpe;

typedef struct Heap
{
	HPDataTytpe *elem; // 指针
	size_t szie;			 // 数组的有限元素的个数
	size_t capacity;	 // 数组的空间大小
} Heap;

//初始化  堆
void HeapInit(Heap *php);

//销毁 堆
void HeapDestroy(Heap *php);

//数据入堆
void HeapPush(Heap *php, HPDataTytpe val);

//数据出堆
void HeapPop(Heap* php);
HPDataTytpe HeapTop(Heap* php);

//判断堆是不是 空
bool HeapEmpty(Heap* php);

//向上调整
void adjustUp(HPDataTytpe *elem, int size);

//向下调整
void adjustDown(HPDataTytpe* elem, int size,size_t root);\

// 堆排序
void HeapSort(int* arr,int len);