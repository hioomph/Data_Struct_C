#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

struct BinTreeNode;
#define ElemType_q BinTreeNode*

typedef struct QueueNode
{
    ElemType_q data;
    struct QueueNode *next;
}QueueNode;

typedef struct LinkQueue
{
    QueueNode *front;
    QueueNode *tail;
}LinkQueue;

void InitQueue(LinkQueue *queue);
bool QueueIsEmpty(LinkQueue *Q);

void EnQueue(LinkQueue *queue, ElemType_q x);
void DeQueue(LinkQueue *queue);
void GetHead(LinkQueue *queue, ElemType_q *x);

void Clear(LinkQueue *queue);
void Destroy(LinkQueue *queue);

////////////////////////////////////////////////////////

// 初始化
void InitQueue(LinkQueue *queue)
{
    QueueNode *s = (QueueNode*)malloc(sizeof(QueueNode));
    assert(s != NULL);
    queue->front = queue->tail = s;
    queue->tail->next = NULL;
    s->next = NULL;
}

// 判空
bool QueueIsEmpty(LinkQueue *Q)
{
    return Q->front == Q->tail;
}

// 入队（链队列的入队-尾插）
void EnQueue(LinkQueue *queue, ElemType_q x)
{
    QueueNode *s = (QueueNode*)malloc(sizeof(QueueNode));
    assert(s != NULL);
    s->data = x;
    s->next = NULL;

    queue->tail->next = s;
    queue->tail = s;    
}

// 出队（链队列的出队-头删）
void DeQueue(LinkQueue *queue)
{
    // 队列为空，直接返回
    if(queue->front == queue->tail)
        return;

    QueueNode *p = queue->front->next;
    queue->front->next = p->next;
    if(p->next == NULL)
    {
        queue->tail = queue->front;
    }
    free(p);
}

// 获取队头元素
void GetHead(LinkQueue *queue, ElemType_q *x)
{
    // 队列为空，直接返回
    if(queue->front == queue->tail)
        return;

    QueueNode *p = queue->front->next;
    *x = p->data;  // 不写成 queue->front->next->data，一般不写超过两个指向
}

// 清空队列
void Clear(LinkQueue *queue)
{
    // 队列为空，直接返回
    if(queue->front == queue->tail)
        return;

    QueueNode *p = queue->front->next;
    while(p != NULL)
    {
        queue->front->next = p->next;
        free(p);
        p = queue->front->next;
    }

    queue->tail = queue->front;
}

// 释放队列
void Destroy(LinkQueue *queue)
{
    Clear(queue);
    free(queue->front);
    queue->front = queue->tail = NULL;
}

#endif // _LINKQUEUE_H_