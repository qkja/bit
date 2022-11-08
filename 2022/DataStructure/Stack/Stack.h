#ifndef __STACK_H__ 
#define __STACK_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#endif 

typedef int StackDataType;

typedef struct Stack
{
	StackDataType* a;
	int top;		// 栈顶的位置
	int capacity;	// 容量
}Stack;

void StackInit(Stack* ps);
void StackDestory(Stack* ps);
void StackPush(Stack* ps, StackDataType x);
void StackPop(Stack* ps);
bool StackEmpty(Stack* ps);
int StackSize(Stack* ps);
StackDataType StackTop(Stack* ps);
