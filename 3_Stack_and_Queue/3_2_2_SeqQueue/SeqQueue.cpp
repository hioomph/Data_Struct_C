#include"SeqQueue.h"

// 初始化
void InitQueue(Queue *queue)
{
    queue->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    assert(queue->base != NULL);

    queue->front = queue->rear = 0;
}

// 遍历队列
void ShowQueue(Queue *queue)
{
    printf("Front:>");

    // 单队列
    // for(int i=0; i<queue->rear; ++i)
    // for(int i=queue->front; i<queue->rear; ++i)
    // {
    //     printf("%d ", queue->base[i]);
    // }

    // 循环队列
    for(int i=queue->front; i!=queue->rear; ) 
    {
        printf("%d ", queue->base[i]);
        i = (i+1)%MAXSIZE;
    }

    printf("<:Tail.\n");
}

// 队列长度
int Length(Queue *queue)
{
    int len = 0;
    for(int i=queue->front; i<queue->rear; ++i)
    {
        len++;
    }
    return len;
}

// 入队
void EnQueue(Queue *queue, ElemType x)
{
    // 单队列
    // if(queue->rear >= MAXSIZE)  // 包含等号是因为下标从0开始
    //     return;
    // queue->base[queue->rear++] = x;

    // 循环队列
    if((queue->rear+1) % MAXSIZE == queue->front)
        return;
    queue->base[queue->rear] = x;
    queue->rear = (queue->rear+1)%MAXSIZE;
}

// 出队
void DeQueue(Queue *queue)
{
    if(queue->front == queue->rear)
        return;

    // 单队列
    // queue->front++;

    // 循环队列
    queue->front = (queue->front+1)%MAXSIZE;
}

// 获取队列头元素
void GetHead(Queue *queue, ElemType *x)
{
    *x = queue->base[queue->front];
}

// 清空队列
void Clear(Queue *queue)
{
    queue->front = queue->rear = 0;
}

// 销毁队列
void Destroy(Queue *queue)
{
    Clear(queue);
    // 释放空间
    free(queue->base);
    queue->base = NULL;
}