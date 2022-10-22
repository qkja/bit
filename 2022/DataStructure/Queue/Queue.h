#ifndef __QUEUE_H__
#define __QUEUE_H__ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#endif 

typedef int QDataType;

typedef struct QueueNode
{
	QDataType data;
	struct QueueNode* next;
}QNode;

typedef struct Queue
{
	QNode* head;
	QNode* tail;
}Queue;

void QueueInit(Queue* pq);
void QueueDestory(Queue* pq);
void QueuePush(Queue* pq, QDataType x);
void QueuePop(Queue* pq);
bool QueueEmpty(Queue* pq);
size_t QueueSize(Queue* pq);
QDataType QueueFront(Queue* pq);
QDataType QueueBack(Queue* pq);


/*
 * 
 * 设计循环队列  生产者消费者模型  图书馆 
 * 空间固定 k
 * 有效数据的元素个数
 * 看自己的设计 k-1 或者 k
 * k 是由缺陷的  相等 可能为空 也可能满了
 * 所以我们设计k-1个
 */

// 如何实现环状
// 这里我们用一个 数组 注意链表可以
// 这里超出数组长度 就回到下标 0

// 存在一个对头和一个堆为
// 相等为空
//
typedef int MQDataType;
typedef struct 
{

  MQDataType* array;
  size_t front;
  size_t tail;  // 指向最后一个数据的下一个位置
  size_t cap;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k);

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value);
bool myCircularQueueDeQueue(MyCircularQueue* obj);

int myCircularQueueFront(MyCircularQueue* obj);

int myCircularQueueRear(MyCircularQueue* obj);

bool myCircularQueueIsEmpty(MyCircularQueue* obj);

bool myCircularQueueIsFull(MyCircularQueue* obj);

void myCircularQueueFree(MyCircularQueue* obj);
