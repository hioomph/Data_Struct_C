#ifndef _SEQQUEUE_H_
#define _SEQQUEUE_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define ElemType int
#define MAXSIZE 8

typedef struct Queue
{
    ElemType *base;
    int      front;
    int      rear;
}Queue;

void InitQueue(Queue *queue);
void ShowQueue(Queue *queue);
int Length(Queue *queue);

void EnQueue(Queue *queue, ElemType x);
void DeQueue(Queue *queue);
void GetHead(Queue *queue, ElemType *x);

void Clear(Queue *queue);
void Destroy(Queue *queue);

#endif // _SEQQUEUE_H_