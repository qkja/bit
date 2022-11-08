#include "Stack.h"

void TestStack()
{
  Stack s;
  StackInit(&s);
  StackPush(&s, 1);
  StackPush(&s, 2);
  StackPush(&s, 3);
  StackPush(&s, 4);
  StackPush(&s, 5);
  
  while(!StackEmpty(&s))
  {
    printf("%d ", StackTop(&s));
    StackPop(&s);
  }
  printf("\n");
  StackDestory(&s);
}

int main()
{
  TestStack();
  return 0;
}
