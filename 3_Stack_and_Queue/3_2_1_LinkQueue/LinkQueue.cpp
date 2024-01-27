#include"LinkQueue.h"

// 初始化
void InitQueue(LinkQueue *queue)
{
    QueueNode *s = (QueueNode*)malloc(sizeof(QueueNode));
    assert(s != NULL);
    queue->front = queue->tail = s;
    queue->tail->next = NULL;
    s->next = NULL;
}

// 遍历队列
void ShowQueue(LinkQueue *queue)
{
    QueueNode *p = queue->front->next;
    printf("Front:>");
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("<:Tail.\n");
}

// 队列长度
int Length(LinkQueue *queue)
{
    int len = 0;

    QueueNode *p = queue->front->next;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    
    return len;
}

// 判空
bool EmptyQueue(LinkQueue *queue)
{
    return queue->front == queue->tail;
}

// 入队（链队列的入队-尾插）
void EnQueue(LinkQueue *queue, ElemType x)
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
void GetHead(LinkQueue *queue, ElemType *x)
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