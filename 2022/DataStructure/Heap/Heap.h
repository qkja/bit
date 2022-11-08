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
	HPDataTytpe* elem;   // 指针
	size_t szie;         // 数组的有限元素的个数
	size_t capacity;     // 数组的空间大小
}Heap;




