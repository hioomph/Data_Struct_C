#ifndef _STACK_H_
#define _STACK_H_


#include<stdio.h>
#include<assert.h>
#include<malloc.h>

struct AVLNode;

#define ElemType AVLNode*

typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
}StackNode;

typedef StackNode* Stack;

void InitStack(Stack *s); // 此处的s实际上为二级指针
void Show(Stack *s);

void Push(Stack *s, ElemType x);
void Pop(Stack *s);
ElemType GetTop(Stack *s);
bool IsEmpty(Stack *s);

void Clear(Stack *s);
void Destroy(Stack *s);

#endif // _STACK_H_