#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

struct BinTreeNode;
#define EType BinTreeNode*

#define STACK_INIT_SIZE 8
#define STACK_INC_SIZE 3

typedef struct SeqStack
{
    EType *base;
    int      capacity;
    int      top;
}SeqStack;

bool Inc(SeqStack *s);

void InitStack(SeqStack *s);
void Show(SeqStack *s);
bool IsFull(SeqStack *s);
bool IsEmpty(SeqStack *s);
int Length(SeqStack *s);

void Push(SeqStack *s, EType x);
void Pop(SeqStack *s);
bool GetTop(SeqStack *s, EType *v);

void Clear(SeqStack *s);
void Destroy(SeqStack *s);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 栈空间增加
bool Inc(SeqStack *s)
{
    EType *newbase = (EType *)realloc(s->base, sizeof(EType)*(s->capacity +STACK_INC_SIZE));
    if(newbase == NULL)
    {
        printf("内存不足，无法申请空间！\n");
        return false;
    }

    s->base = newbase;
    s->capacity += STACK_INC_SIZE;
    return true;
}

// 初始化
void InitStack(SeqStack *s)
{
    s->base = (EType *)malloc(sizeof(EType) * STACK_INIT_SIZE);
    assert(s->base != NULL);
    s->capacity = STACK_INIT_SIZE;
    s->top = 0;
}

// 判满
bool IsFull(SeqStack *s)
{
    return s->top >= s->capacity;
}

// 判空
bool IsEmpty(SeqStack *s)
{
    return s->top == 0;
}

// 栈长度
int Length(SeqStack *s)
{
    return s->top;
}

// 入栈
void Push(SeqStack *s, EType x)
{
    // 由于为顺序栈，因此一定要对栈是否满做出判断
    if(IsFull(s) && !Inc(s))
        return;
    
    // 顺序栈：1）先存值；2）top+1
    s->base[s->top++] = x;
}

// 出栈
void Pop(SeqStack *s)
{
    // 判空
    if(IsEmpty(s))
    {
        printf("栈空间已空，不能出栈！\n");
        return;
    }
    // 顺序栈：1)top-1；2）取栈顶元素
    // 实际操作时：GetTop函数实现上述功能 s->base[s->top-1]，但此时并未真正完成top-1，而是交给Pop来完成
    s->top--;
}

// 获取栈顶元素
bool GetTop(SeqStack *s, EType *v)
{
    if(IsEmpty(s))
    {
        printf("栈空间已空，不能取栈顶元素！\n");
        return false;
    }

    *v = s->base[s->top-1]; 
    // 错误写法： *v = s->base[--s->top]; 
    // 错误原因：此处仅考虑获取栈顶元素，若--s->top,则对其进行了出栈操作
    return true;
}

// 清空栈
void Clear(SeqStack *s)
{
    s->top = 0;
}

// 摧毁栈
void Destroy(SeqStack *s)
{
    free(s->base);
    s->base = NULL;
    s->capacity = s->top = 0;
}
#endif // _SEQSTACK_H_