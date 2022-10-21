#include "Queue.h"

void QueueInit(Queue* pq)
{
  assert(pq);
  pq->head = NULL;
  pq->tail = NULL;
}

void QueueDestory(Queue* pq)
{
  assert(pq);
  if(pq->head == NULL)
    return;

  QueueNode* cur = pq->head;
  QueueNode* curNext = pq->head->next;
  while(curNext)
  {
    free(cur);
    cur = curNext;
    curNext = curNext->next;
  }
  free(cur);
  pq->head = NULL;
  pq->tail = NULL;

  //while(cur)
  //{
  //  free(cur);
  //  if(curNext == NULL)
  //    return;
  //  cur = curNext;
  //  curNext = curNext->next;
  //}
  //pq->head = NULL;
  //pq->tail = NULL;
}

QueueNode* BuyQueueNode(QDataType x)
{
  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
  assert(node);
  node->data = x;
  node->next = NULL;
  return node;
}

void QueuePush(Queue* pq, QDataType x)
{
  assert(pq);
  QueueNode* node = BuyQueueNode(x);

  // 第一次插入
  if(pq->head == NULL)
    pq->head = node;
  else
    pq->tail->next = node;

  pq->tail = node;
}

void QueuePop(Queue* pq)
{
  assert(pq);
  assert(pq->head);
  QueueNode* next = pq->head->next;
  free(pq->head);
  pq->head = next;
}

bool QueueEmpty(Queue* pq)
{
  assert(pq);
  return pq->head == NULL;
}

size_t QueueSize(Queue* pq)
{
  assert(pq);
  QueueNode* cur = pq->head;
  size_t count = 0;
  while(cur)
  {
    cur = cur->next;
    count++;
  }
  return count;
}

QDataType QueueFront(Queue* pq)
{
  assert(pq);
  assert(pq->head);

  return pq->head->data;
}

QDataType QueueBack(Queue* pq)
{
  assert(pq);
  assert(pq->head);
  return pq->tail->data;
}
