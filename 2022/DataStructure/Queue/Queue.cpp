#include "Queue.h"

MyCircularQueue* myCircularQueueCreate(int k) {
  // 这里要求是 是 k 的有效元素 我们 开辟 k+1
  MyCircularQueue* m = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
  assert(m);
  MQDataType*ret = (MQDataType*)malloc(sizeof(MQDataType) * (k+1)) ;
  assert(ret);
  m->array = ret;
  m->front = 0;
  m->tail = 0;
  m->cap = k+1;
  return m;
}

// 入队列
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
  assert(obj);
  // 判满
  if(myCircularQueueIsFull(obj))
    return false;
  



  obj->array[obj->tail] = value;
  if(obj->tail == obj->cap-1)
    obj->tail = 0;
  else 
    obj->tail++;
  return true;

  //obj->array[obj->tail] = value;
  //// 这里修改 tail 
  //int ret = (obj->tail+1) % (obj->cap);
  //obj->tail = ret;
  //return true;
}

// 出队列
bool myCircularQueueDeQueue(MyCircularQueue* obj) {

  assert(obj);
  // 判空
  if(myCircularQueueIsEmpty(obj))
    return false;
  if(obj->front == obj->cap-1)
    obj->front = 0;
  else 
    obj->front++;
  // 这里修改 front 
  //int ret = (obj->front+1)%(obj->cap);
  //obj->front = ret;
  return true;
}

// 头部
int myCircularQueueFront(MyCircularQueue* obj) {

  assert(obj);
  // 判空
  if(myCircularQueueIsEmpty(obj))
    return -1;
  return obj->array[obj->front];
}

// 尾部
int myCircularQueueRear(MyCircularQueue* obj) {

  assert(obj);
  // 判空
  if(myCircularQueueIsEmpty(obj))
    return -1;

  // 如果 tail 是 0 单拿出来
  if(obj->tail == 0)
  {
    return obj->array[obj->cap - 1];
  }
  return obj->array[obj->tail - 1];
}

// 空
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
  assert(obj);
  return obj->front == obj->tail;
}

// 满
bool myCircularQueueIsFull(MyCircularQueue* obj) {
  assert(obj);
  size_t ret = (obj->tail+1)%obj->cap;
  return ret == obj->front;
}

// 释放空间
void myCircularQueueFree(MyCircularQueue* obj) {
  assert(obj);
  free(obj->array);
  obj->array = NULL;
  obj->front = 0;
  obj->tail = 0;
  free(obj);
  // 这里修改obj 改变的是行参
}






















void QueueInit(Queue* pq)
{
  assert(pq);
  pq->head = NULL;
  pq->tail = NULL;
}

void QueueDestory(Queue* pq)
{
  assert(pq);
  //if(pq->head == NULL
  //    && pq->tail == NULL)
  //  return;

  QueueNode* cur = pq->head;
  while(cur)
  {
    QueueNode* next = cur->next;
    free(cur);
    cur = next;
  }
  pq->head = NULL;
  pq->tail = NULL;
  //QueueNode* cur = pq->head;
  //QueueNode* curNext = pq->head->next;
  //while(curNext)
  //{
  //  free(cur);
  //  cur = curNext;
  //  curNext = curNext->next;
  //}
  //free(cur);
  //pq->head = NULL;
  //pq->tail = NULL;

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

// 没有必要写 只有自己用
//QueueNode* BuyQueueNode(QDataType x)
//{
//  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
//  assert(node);
//  node->data = x;
//  node->next = NULL;
//  return node;
//}

void QueuePush(Queue* pq, QDataType x)
{
  assert(pq);
  //QueueNode* node = BuyQueueNode(x);
  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
  assert(node);
  node->data = x;
  node->next = NULL;
  // 第一次插入
  if(pq->head == NULL 
      && pq->tail == NULL)
    pq->head = node;
  else
    pq->tail->next = node;

  pq->tail = node;
}

//void QueuePop(Queue* pq)
//{
//  assert(pq);
//  assert(pq->head);
//  QueueNode* next = pq->head->next;
//  free(pq->head);
//  pq->head = next;
//}

void QueuePop(Queue* pq)
{
  assert(pq);
  assert(pq->head && pq->tail);
  QueueNode* next = pq->head->next;
  free(pq->head);
  pq->head = next;
  // 要一起为空
  if(next == NULL)
    pq->tail == NULL:
}

bool QueueEmpty(Queue* pq)
{
  assert(pq);
  return pq->head == NULL;
}

size_t QueueSize(Queue* pq)
{
  // 这个接口是最慢了
  // 如果不想遍历 可以使用 一个计数
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
  assert(pq->head && pq->tail);

  return pq->head->data;
}

QDataType QueueBack(Queue* pq)
{
  assert(pq);
  assert(pq->head && pq->tail);
  return pq->tail->data;
}
