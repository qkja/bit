#include "Queue.h"

void TestQueuePush()
{
  Queue q;
  QueueInit(&q);
  QueuePush(&q, 1);
  QueuePush(&q, 2);
  QueuePush(&q, 3);
  QueuePush(&q, 4);
  while(!QueueEmpty(&q))
  {
    int ret = QueueFront(&q);
    printf("%d ",ret);
    QueuePop(&q);
  }
  printf("\n");
  QueueDestory(&q);
}

int main()
{
  TestQueuePush();
  return 0;
}
