#include "Stack.h"

void StackInit(Stack* ps)
{
  assert(ps);
  ps->a = NULL;
  ps->capacity = 0;
  ps->top = 0;
}

void StackDestory(Stack* ps)
{
  assert(ps);
  free(ps->a);
  ps->a = NULL;
  ps->capacity = 0;
  // 这个 选择 -1 还是 0
  ps->top = 0;
}

void StackPush(Stack* ps, StackDataType x)
{
  assert(ps);
  if(ps->capacity == ps->top)
  {
    int newCapacity = ps->capacity == 0 ? 4 : 2*ps->capacity;
    StackDataType* ret = (StackDataType*)realloc(ps->a, sizeof(StackDataType)*newCapacity);
    assert(ret);
    ps->a = ret;
    ps->capacity = newCapacity;
  }
  ps->a[ps->top++] = x;
}

void StackPop(Stack* ps)
{
  assert(ps);
  assert(ps->top > 0);
  ps->top--;
}

bool StackEmpty(Stack* ps)
{
  assert(ps);
  return ps->top == 0;
}

int StackSize(Stack* ps)
{
  assert(ps);
  return ps->top;
}

StackDataType StackTop(Stack* ps)
{
  assert(ps);
  assert(ps > 0);
  // 这里-1 和 0 就可以体现出来了
  return ps->a[ps->top-1];
}
