#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int

typedef struct QueueNode
{
    ElemType data;
    struct QueueNode *next;
}QueueNode;

typedef struct LinkQueue
{
    QueueNode *front;
    QueueNode *tail;
}LinkQueue;

void InitQueue(LinkQueue *queue);
void ShowQueue(LinkQueue *queue);
int Length(LinkQueue *queue);

void EnQueue(LinkQueue *queue, ElemType x);
void DeQueue(LinkQueue *queue);
void GetHead(LinkQueue *queue, ElemType *x);

void Clear(LinkQueue *queue);
void Destroy(LinkQueue *queue);

#endif // _LINKQUEUE_H_