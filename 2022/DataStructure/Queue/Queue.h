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
