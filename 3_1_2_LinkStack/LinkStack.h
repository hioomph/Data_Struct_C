#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

#include<stdio.h>
#include<assert.h>
#include<malloc.h>

#define ElemType int

typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
}StackNode;

typedef StackNode* LinkStack;

void InitStack(LinkStack *s); // 此处的s实际上为二级指针
void Show(LinkStack *s);

void Push(LinkStack *s, ElemType x);
void Pop(LinkStack *s);
bool GetTop(LinkStack *s, ElemType *v);

void Clear(LinkStack *s);
void Destroy(LinkStack *s);


#endif // _LINKSTACK_H_